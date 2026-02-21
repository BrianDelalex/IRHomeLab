#ifndef APPLICATION_CORE_HPP
# define APPLICATION_CORE_HPP

# include <memory>
# include <thread>
# include <functional>

# include "WidgetsID.hpp"

namespace Core
{
    class ApplicationCore
    {
        public:
            ApplicationCore();

            void RegisterPageChangeCallback(std::function<void(WidgetsID)> callback);
        private:
            std::unique_ptr<std::thread> m_thread_signal_handler_loop;
            std::function<void(WidgetsID)> m_page_change_callback;
            WidgetsID m_selected_widget;

            void SetupSignalHandlers(void);
            void RegisterToIrDriver(void);

            void SignalCallback(int sig, int sig_int);
            void SIGIOHandler(int sig_int);
    };

    ApplicationCore *get_application_core_instance(void);

} //  namespace Core

#endif //!APPLICATION_CORE_HPP