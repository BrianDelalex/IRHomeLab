# include "Core/ApplicationCore.hpp"

# include <thread> 
# include <exception>
# include <iostream>
# include <filesystem>

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>

# include "irdriver.hpp"
# include "Com/Signals/SignalHandler.hpp"

namespace Core
{
    static std::unique_ptr<ApplicationCore> APPLICATION_CORE_INSTANCE = std::make_unique<ApplicationCore>();

    ApplicationCore *get_application_core_instance()
    {
        return APPLICATION_CORE_INSTANCE.get();
    }

    ApplicationCore::ApplicationCore()
    {
        SetupSignalHandlers();
        RegisterToIrDriver();
    }
    
    void ApplicationCore::SetupSignalHandlers()
    {
        Com::Signals::SignalHandler *sig_handler = Com::Signals::get_signal_handler_instance();

        Com::Signals::SignalHandlerData data_sigio;
        data_sigio.signal_number = SIGIO;
        data_sigio.handler_function = std::bind(&ApplicationCore::SignalCallback, this, std::placeholders::_1, std::placeholders::_2);
        sig_handler->RegisterSignal(data_sigio);

        m_thread_signal_handler_loop = std::make_unique<std::thread>(&Com::Signals::SignalHandler::Loop, sig_handler);
    }

    void ApplicationCore::RegisterToIrDriver()
    {
        int fd = open(IRDRIVER_DEVICE_PATH.c_str(), O_WRONLY);
        if (fd == -1) {
            throw std::filesystem::filesystem_error("Failed to open " + IRDRIVER_DEVICE_PATH, std::error_code(errno, std::generic_category()));
        }
        if (ioctl(fd, 1, getpid()) == -1) {
            throw std::system_error(errno, std::generic_category(), "Failed to register process with IR driver");
        }
    }

    void ApplicationCore::SignalCallback(int sig, int sig_int)
    {
        std::cout << __FUNCTION__ << " [INFO]: Received signal " << sig << " with sig_int " << sig_int << std::endl;
        switch (sig)
        {
            case SIGIO:
                SIGIOHandler(sig_int);
                break;
            default:
                std::cerr << __FUNCTION__ << " [WARNING]: Received unhandled signal " << sig << std::endl;
                break;
        }
    }

    void ApplicationCore::SIGIOHandler(int sig_int)
    {
        std::cout << __FUNCTION__ << " [INFO]: Handling SIGIO with sig_int " << sig_int << std::endl;
    }

} //  namespace Core