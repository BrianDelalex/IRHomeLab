# include "Config/AppConfig.hpp"

# include <fstream>
# include <iostream>

namespace Config
{
    static const std::string CONFIG_DIR_NAME = "IRHomeLab";
    static const std::string CONFIG_FILE_NAME = "config.json";

    AppConfig& AppConfig::GetInstance()
    {
        static AppConfig instance;
        return instance;
    }

    AppConfig::AppConfig()
    {
        const char *xdg = std::getenv("XDG_CONFIG_HOME");
        std::filesystem::path config_dir = std::string(xdg ? xdg : std::string(std::getenv("HOME")) + "/.config") + "/" + CONFIG_DIR_NAME;

        std::filesystem::create_directories(config_dir);
        m_config_path = config_dir / CONFIG_FILE_NAME;

        Load();
    }

    void AppConfig::Load()
    {
        if (!std::filesystem::exists(m_config_path))
        {
            m_config = nlohmann::json::object();
            return;
        }

        std::ifstream file(m_config_path);
        if (!file.is_open())
        {
            std::cerr << __FUNCTION__ << " [ERROR]: Failed to open " << m_config_path << std::endl;
            m_config = nlohmann::json::object();
            return;
        }

        try
        {
            m_config = nlohmann::json::parse(file);
        }
        catch (const nlohmann::json::parse_error &e)
        {
            std::cerr << __FUNCTION__ << " [ERROR]: Failed to parse config: " << e.what() << std::endl;
            m_config = nlohmann::json::object();
        }
    }

    void AppConfig::Save()
    {
        std::ofstream file(m_config_path);
        if (!file.is_open())
        {
            std::cerr << __FUNCTION__ << " [ERROR]: Failed to open " << m_config_path << std::endl;
            return;
        }

        file << m_config.dump(4);
    }

} //  namespace Config
