# include "Com/Signals/SignalHandler.hpp"

# include <thread>
# include <ranges>
# include <iostream>
# include <atomic>
# include <format>

namespace Com::Signals
{
    std::atomic<Signal> signal_received;
    static std::unique_ptr<SignalHandler> SIGNAL_HANDLER_INSTANCE = std::make_unique<SignalHandler>();

    SignalHandler *get_signal_handler_instance()
    {
        return SIGNAL_HANDLER_INSTANCE.get();
    }

    
    static void signal_handler(int sig, siginfo_t *si, void *u)
    {
        Signal signal;
        signal.sig = sig;
        signal.sig_int = si->si_int;
        signal.processed = false;

        signal_received = signal;
    }

    void SignalHandler::RegisterSignal(const SignalHandlerData &data)
    {
        struct sigaction sa;
        sa.sa_sigaction = signal_handler;
        sa.sa_flags = SA_SIGINFO;

        if (sigaction(data.signal_number, &sa, nullptr) == -1)
        {
            std::cerr << __FUNCTION__ << " [ERROR]: Error in function sigaction for signal " << data.signal_number << std::endl;
            throw std::system_error(std::error_code(errno, std::generic_category()), std::format("Failed to register signal handler for signal {}", data.signal_number));
        }
        m_handlers.push_back(data);
    }

    void SignalHandler::Loop()
    {
        Signal default_sig;
        default_sig.processed = true;
        while (m_running)
        {
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(10ms);

            Signal signal = signal_received.load();
            signal_received.store(default_sig);
            if (!signal.processed) 
            {
                auto handler_finder = [this, &signal](const SignalHandlerData &data) 
                    {
                        return data.signal_number == signal.sig;
                    };
                if (auto hdl = std::ranges::find_if(m_handlers, handler_finder); hdl != m_handlers.end())
                {
                    hdl->handler_function(signal.sig, signal.sig_int);
                }
            }
        }
    }
} //  namespace Com::Signals