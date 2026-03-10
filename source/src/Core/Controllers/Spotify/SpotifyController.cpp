# include "Core/Controllers/Spotify/SpotifyController.hpp"

# include <httplib.h>
# include <nlohmann/json.hpp>

# include <chrono>
# include <cstdio>
# include <ctime>
# include <iostream>
# include <string>

# include "Config/AppConfig.hpp"

namespace Core::Controllers
{

    namespace
    {
        static std::string base64_encode(const std::string &input)
        {
            static const char *table =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

            std::string result;
            result.reserve(((input.size() + 2) / 3) * 4);

            for (size_t i = 0; i < input.size(); i += 3)
            {
                unsigned char b0 = static_cast<unsigned char>(input[i]);
                unsigned char b1 = (i + 1 < input.size()) ? static_cast<unsigned char>(input[i + 1]) : 0;
                unsigned char b2 = (i + 2 < input.size()) ? static_cast<unsigned char>(input[i + 2]) : 0;

                result += table[b0 >> 2];
                result += table[((b0 & 0x3) << 4) | (b1 >> 4)];
                result += (i + 1 < input.size()) ? table[((b1 & 0xF) << 2) | (b2 >> 6)] : '=';
                result += (i + 2 < input.size()) ? table[b2 & 0x3F] : '=';
            }
            return result;
        }

        static std::string url_encode(const std::string &s)
        {
            std::string result;
            for (unsigned char c : s)
            {
                if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
                    result += static_cast<char>(c);
                else
                {
                    char buf[4];
                    std::snprintf(buf, sizeof(buf), "%%%02X", c);
                    result += buf;
                }
            }
            return result;
        }
    }  //  anonymous namespace

    SpotifyController::SpotifyController(WidgetsID id) :
        IController(id)
    {
        auto config = Config::get_app_config_instance();
        if (!config->Contains("spotify/access_token"))
        {
            m_login_thread = std::thread(&SpotifyController::Login, this);
        }
    }

    SpotifyController::~SpotifyController()
    {
        if (m_login_thread.joinable())
            m_login_thread.detach();
    }

    void SpotifyController::CommandHandler(const IRButton &btn)
    {

    }

    void SpotifyController::Login()
    try
    {
        auto config = Config::get_app_config_instance();

        if (!config->Contains("spotify_client/client_id") || !config->Contains("spotify_client/client_secret"))
        {
            std::cerr << "SpotifyController::Login [ERROR]: Spotify client credentials not configured" << std::endl;
            return;
        }

        std::string client_id     = config->Get<std::string>("spotify_client/client_id");
        std::string client_secret = config->Get<std::string>("spotify_client/client_secret");
        std::string redirect_uri  = "http://127.0.0.1:3000/";
        std::string scope         = "user-read-private user-read-email user-modify-playback-state "
                                    "user-read-playback-state app-remote-control streaming "
                                    "user-read-recently-played";

        std::string auth_url = std::string("https://accounts.spotify.com/authorize")
                               + "?client_id="       + url_encode(client_id)
                               + "&response_type=code"
                               + "&redirect_uri="    + url_encode(redirect_uri)
                               + "&scope="           + url_encode(scope);

        int ret = system(("xdg-open \"" + auth_url + "\" &").c_str());
        std::cerr << "xdg-open returned: " << ret << std::endl;

        httplib::Server svr;
        std::string auth_code;

        svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
            auth_code = req.get_param_value("code");
            res.set_content("Authorization successful! You can close this tab.", "text/plain");
            svr.stop();
        });

        svr.listen("127.0.0.1", 3000);

        if (auth_code.empty())
        {
            std::cerr << "SpotifyController::Login [ERROR]: No authorization code received" << std::endl;
            return;
        }

        httplib::SSLClient cli("accounts.spotify.com");
        httplib::Params params = {
            {"grant_type",   "authorization_code"},
            {"code",         auth_code},
            {"redirect_uri", redirect_uri}
        };
        httplib::Headers headers = {
            {"Authorization", "Basic " + base64_encode(client_id + ":" + client_secret)}
        };

        auto res = cli.Post("/api/token", headers, params);

        if (res && res->status == 200)
        {
            auto token_data = nlohmann::json::parse(res->body);
            token_data["expires_at"] = std::time(nullptr) + token_data["expires_in"].get<int>();
            config->SetSection("spotify", token_data);
            config->Save();
            std::cout << "SpotifyController::Login [INFO]: Access token saved" << std::endl;
        }
        else
        {
            std::cerr << "SpotifyController::Login [ERROR]: Token exchange failed";
            if (res)
                std::cerr << " (HTTP " << res->status << "): " << res->body;
            std::cerr << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "SpotifyController::Login [ERROR]: " << e.what() << std::endl;
    }

    void SpotifyController::RefreshToken()
    {
        auto config = Config::get_app_config_instance();

        if (!config->Contains("spotify_client/client_id") || !config->Contains("spotify_client/client_secret"))
        {
            std::cerr << "SpotifyController::RefreshToken [ERROR]: Spotify client credentials not configured" << std::endl;
            return;
        }

        if (!config->Contains("spotify/refresh_token"))
        {
            std::cerr << "SpotifyController::RefreshToken [ERROR]: No refresh token in configuration" << std::endl;
            return;
        }

        if (config->Contains("spotify/expires_at"))
        {
            std::time_t expires_at = config->Get<std::time_t>("spotify/expires_at");
            if (std::time(nullptr) < expires_at - 60)
                return;
        }

        std::string client_id     = config->Get<std::string>("spotify_client/client_id");
        std::string client_secret = config->Get<std::string>("spotify_client/client_secret");
        std::string refresh_token = config->Get<std::string>("spotify/refresh_token");

        httplib::SSLClient cli("accounts.spotify.com");
        httplib::Params params = {
            {"grant_type",    "refresh_token"},
            {"refresh_token", refresh_token}
        };
        httplib::Headers headers = {
            {"Authorization", "Basic " + base64_encode(client_id + ":" + client_secret)}
        };

        auto res = cli.Post("/api/token", headers, params);

        if (res && res->status == 200)
        {
            auto token_data = nlohmann::json::parse(res->body);
            if (!token_data.contains("refresh_token"))
                token_data["refresh_token"] = refresh_token;
            token_data["expires_at"] = std::time(nullptr) + token_data["expires_in"].get<int>();
            config->SetSection("spotify", token_data);
            config->Save();
            std::cout << "SpotifyController::RefreshToken [INFO]: Token refreshed" << std::endl;
        }
        else
        {
            std::cerr << "SpotifyController::RefreshToken [ERROR]: Token refresh failed";
            if (res)
                std::cerr << " (HTTP " << res->status << "): " << res->body;
            std::cerr << std::endl;
        }
    }

}  //  namespace Core::Controllers
