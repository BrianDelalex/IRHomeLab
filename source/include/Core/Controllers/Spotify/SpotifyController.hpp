#ifndef SPOTIFY_CONTROLLER_HPP_
# define SPOTIFY_CONTROLLER_HPP_

# include <thread>

# include "Core/Controllers/IController.hpp"
# include "Core/States/SpotifyState.hpp"

namespace Core::Controllers
{
    class SpotifyController : public Core::Controllers::IController
    {
        public:
            SpotifyController(WidgetsID id);
            ~SpotifyController();

            void CommandHandler(const IRButton &btn);
            void CommandHandlerDefault(const IRButton &btn);
            void CommandHandlerDeviceSelection(const IRButton &btn);
        private:
            void Login(void);
            void RefreshToken(void);

            std::thread m_login_thread;
            States::SpotifyState m_state;
    };
}  //  Core::Controllers

#endif //!SPOTIFY_CONTROLLER_HPP_
