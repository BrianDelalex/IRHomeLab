# include "GUI/App.hpp"

# include <iostream>
# include <thread> 

# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>

#include "Com/Signals/SignalHandler.hpp"

void test_signal_handler(int sig, int sig_int)
{
    std::cout << "Signal received: " << sig << ", with int: " << sig_int << std::endl;
}

wxIMPLEMENT_APP(App);
bool App::OnInit(void)
{
    Com::Signals::SignalHandler *sig_handler = Com::Signals::get_signal_handler_instance();

    Com::Signals::SignalHandlerData data_sigio;
    data_sigio.signal_number = SIGIO;
    data_sigio.handler_function = std::bind(&test_signal_handler, std::placeholders::_1, std::placeholders::_2);
    sig_handler->RegisterSignal(data_sigio);

    std::thread *sig_thread = new std::thread(&Com::Signals::SignalHandler::Loop, sig_handler);
    std::cout << "Test print" << std::endl;
    int fd = open("/dev/irdriver", O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error: open failed. " << strerror(errno) << std::endl;
        return false;
    }
    if (ioctl(fd, 1, getpid()) == -1) {
        std::cerr << "Error: ioctl failed. " << strerror(errno) << std::endl;
        return false;
    }


    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "IRHomeLab");
    frame->Show();
    return true;
}