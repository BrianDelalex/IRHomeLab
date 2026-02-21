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

    void ApplicationCore::RegisterPageChangeCallback(std::function<void(WidgetsID)> callback)
    {
        m_page_change_callback = callback;
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
        if (ioctl(fd, CMD_REGISTER, getpid()) == -1) {
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
        if (sig_int < 0 || sig_int > IRButton::BTN_NINE)
        {
            std::cerr << __FUNCTION__ << " [WARNING]: Received invalid button code " << sig_int << std::endl;
            return;
        }
        if (sig_int >= IRButton::BTN_ZERO)
        {
            WidgetsID widget_id = static_cast<WidgetsID>(sig_int - (int)IRButton::BTN_ZERO + 1);
            if (widget_id >= WidgetsID::UNDEFINED)
            {
                std::cerr << __FUNCTION__ << " [WARNING]: Received button code " << sig_int << " which maps to invalid widget_id " << widget_id << std::endl;
                return;
            }
            m_selected_widget = widget_id;
            if (m_page_change_callback)
            {
                m_page_change_callback(widget_id);
            }
            else
            {
                std::cerr << __FUNCTION__ << " [WARNING]: No page change callback registered, cannot change page to " << widget_id << std::endl;
            }
        }
    }

} //  namespace Core