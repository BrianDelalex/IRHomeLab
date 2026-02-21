# include "GUI/App.hpp"

# include <iostream>

# include "GUI/Events/PageEvent.hpp"

# include "Core/ApplicationCore.hpp"

wxIMPLEMENT_APP(App);
bool App::OnInit(void)
{
    frame = new GUI::Frames::MainFrame(nullptr, wxID_ANY, wxSize(1920, 1080));
    frame->Show();

    auto app_core = Core::get_application_core_instance();

    app_core->RegisterPageChangeCallback(std::bind_front(&App::ChangeViewCallback, this));

    return true;
}

void App::ChangeViewCallback(WidgetsID view_id)
{
    std::cout << __FUNCTION__ << " [INFO]: Changing view to " << view_id << std::endl;
    auto *event = new  GUI::Events::PageEvent(wxID_ANY, view_id);

    frame->GetEventHandler()->QueueEvent(event);
}