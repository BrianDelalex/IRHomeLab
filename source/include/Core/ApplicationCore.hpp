#ifndef APPLICATION_CORE_HPP
# define APPLICATION_CORE_HPP

# include <memory>
# include <thread>
# include <functional>

# include "WidgetsID.hpp"

# include "Core/States/IState.hpp"
# include "Core/Controllers/IController.hpp"

namespace Core
{
    static const int WIDGET_NUMBER = 9;

    class ApplicationCore
    {
        public:
            ApplicationCore();

            void RegisterPageChangeCallback(std::function<void(WidgetsID)> callback);
            void RegisterUpdateStateCallback(std::function<void(std::shared_ptr<Core::States::IState>, WidgetsID)> callback);
        private:
            std::unique_ptr<std::thread> m_thread_signal_handler_loop;
            std::function<void(WidgetsID)> m_page_change_callback;
            std::function<void(std::shared_ptr<Core::States::IState>, WidgetsID)> m_update_state_callback;
            WidgetsID m_selected_widget{WidgetsID::SPOTIFY_ID};
            std::array<std::unique_ptr<Core::Controllers::IController>, WIDGET_NUMBER> m_widget_controllers;

            void SetupSignalHandlers(void);
            void RegisterToIrDriver(void);

            void SignalCallback(int sig, int sig_int);
            void SIGIOHandler(int sig_int);
    };

    ApplicationCore *get_application_core_instance(void);

} //  namespace Core

#endif //!APPLICATION_CORE_HPP