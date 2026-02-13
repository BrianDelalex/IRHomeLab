#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

# include <signal.h>

# include <functional>
# include <memory>
# include <list>

namespace Com::Signals
{
    struct SignalHandlerData
    {
        int signal_number;
        std::function<void(int, int)> handler_function;
    };

    struct Signal 
    {
        int sig;
        int sig_int;
        bool processed;
    };

    class SignalHandler
    {
        public:
            SignalHandler() = default;

            void Loop(void);

            void RegisterSignal(const SignalHandlerData &data);
        private:
            bool m_running{true};
            std::list<SignalHandlerData> m_handlers;
    };

    SignalHandler *get_signal_handler_instance(void);
} //  namespace Com::Signals
 
#endif //!SIGNAL_HANDLER_HPP