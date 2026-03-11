# include "Debug/RemoteControllerMockFrame.hpp"

# ifdef DEBUG

# include <fcntl.h>
# include <unistd.h>

# include <array>
# include <iostream>
# include <string>

# include "irdriver_api.h"

namespace GUI::Debug
{
    static const std::string IRDRIVER_DEVICE_PATH = "/dev/irdriver";

    static const std::array<std::pair<std::string, IRButton>, 21> BUTTON_LAYOUT = {{
        {"VOL-",  BTN_VOL_MINUS},
        {"PLAY",  BTN_PLAY},
        {"VOL+",  BTN_VOL_PLUS},
        {"SETUP", BTN_SETUP},
        {"PREV",  BTN_PREVIOUS},
        {"STOP",  BTN_STOP},
        {"CH-",   BTN_CHNL_MINU},
        {"ENTER", BTN_ENTER},
        {"CH+",   BTN_CHNL_PLUS},
        {"0",     BTN_ZERO},
        {"NEXT",  BTN_NEXT},
        {"BACK",  BTN_BACK},
        {"1",     BTN_ONE},
        {"2",     BTN_TWO},
        {"3",     BTN_THREE},
        {"4",     BTN_FOUR},
        {"5",     BTN_FIVE},
        {"6",     BTN_SIX},
        {"7",     BTN_SEVEN},
        {"8",     BTN_EIGHT},
        {"9",     BTN_NINE},
    }};

    RemoteControllerMockFrame::RemoteControllerMockFrame() :
        wxFrame(nullptr, wxID_ANY, "Remote Controller Mock", wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP)
    {
        m_fd = open(IRDRIVER_DEVICE_PATH.c_str(), O_WRONLY);
        if (m_fd == -1)
            std::cerr << __FUNCTION__ << " [ERROR]: Failed to open " << IRDRIVER_DEVICE_PATH << std::endl;
        CreateButtons();
    }

    void RemoteControllerMockFrame::CreateButtons()
    {
        wxGridSizer *sizer = new wxGridSizer(7, 3, 5, 5);

        for (const auto &[label, button] : BUTTON_LAYOUT)
        {
            wxButton *btn = new wxButton(this, wxID_HIGHEST + static_cast<int>(button), label);
            btn->Bind(wxEVT_BUTTON, &RemoteControllerMockFrame::OnButtonClicked, this);
            sizer->Add(btn, 1, wxEXPAND);
        }

        this->SetSizerAndFit(sizer);
    }

    void RemoteControllerMockFrame::OnButtonClicked(wxCommandEvent &event)
    {
        if (m_fd == -1)
        {
            std::cerr << __FUNCTION__ << " [ERROR]: IR driver not open" << std::endl;
            return;
        }

        std::string input = std::to_string(event.GetId() - wxID_HIGHEST);
        if (write(m_fd, input.data(), input.size()) == -1)
            std::cerr << __FUNCTION__ << " [ERROR]: Failed to write to IR driver" << std::endl;
    }

} //  namespace GUI::Debug

# endif // DEBUG
