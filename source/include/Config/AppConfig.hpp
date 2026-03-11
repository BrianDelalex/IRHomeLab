#ifndef APP_CONFIG_HPP_
# define APP_CONFIG_HPP_

# include <filesystem>
# include <string>

# include "nlohmann/json.hpp"

namespace Config
{
    class AppConfig
    {
        public:
            static AppConfig& GetInstance();

            AppConfig(const AppConfig&) = delete;
            AppConfig& operator=(const AppConfig&) = delete;

            template<typename T>
            T Get(const std::string &key) const
            {
                return m_config.at(nlohmann::json::json_pointer("/" + key)).get<T>();
            }

            template<typename T>
            void Set(const std::string &key, const T &value)
            {
                m_config[nlohmann::json::json_pointer("/" + key)] = value;
            }

            void SetSection(const std::string &key, const nlohmann::json &value)
            {
                m_config[key] = value;
            }

            bool Contains(const std::string &key) const
            {
                return m_config.contains(nlohmann::json::json_pointer("/" + key));
            }

            void Save(void);

        private:
            AppConfig();

            void Load(void);

            std::filesystem::path m_config_path;
            nlohmann::json m_config;
    };


} //  namespace Config

#endif //!APP_CONFIG_HPP_
