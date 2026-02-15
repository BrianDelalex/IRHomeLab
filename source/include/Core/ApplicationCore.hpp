#ifndef APPLICATION_CORE_HPP
# define APPLICATION_CORE_HPP

# include <memory>
# include <thread>

namespace Core
{

    class ApplicationCore
    {
        public:
            ApplicationCore();
        private:
            std::unique_ptr<std::thread> m_thread_signal_handler_loop;

            void SetupSignalHandlers(void);
            void RegisterToIrDriver(void);

            void SignalCallback(int sig, int sig_int);
            void SIGIOHandler(int sig_int);
    };

} //  namespace Core

#endif //!APPLICATION_CORE_HPP