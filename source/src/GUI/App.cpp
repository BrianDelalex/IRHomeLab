# include "GUI/App.hpp"

# include <iostream>

# include "GUI/Events/PageEvent.hpp"
# include "GUI/Views/ViewsID.hpp"
# include "GUI/Connector.hpp"

# include "Core/ApplicationCore.hpp"

wxIMPLEMENT_APP(App);
bool App::OnInit(void)
{
    frame = new GUI::Frames::MainFrame(nullptr, wxID_ANY, wxSize(1920, 1080));
    frame->Show();

    auto app_core = Core::get_application_core_instance();

    app_core->RegisterPageChangeCallback(std::bind_front(&App::ChangeViewCallback, this));
    app_core->RegisterUpdateStateCallback(std::bind_front(&App::UpdateStateCallback, this));

    return true;
}

void App::ChangeViewCallback(WidgetsID widget_id)
{
    std::cout << __FUNCTION__ << " [INFO]: Changing view to " << widget_id << std::endl;
    auto *event = new  GUI::Events::PageEvent(wxID_ANY, widget_id);

    Connector *connector = get_connector_instance();
    connector->QueueEvent(event);
}

void App::UpdateStateCallback(std::shared_ptr<Core::States::IState>state, WidgetsID widget_id)
{
    std::cout << __FUNCTION__ << " [INFO]: Updating state" << std::endl;
    auto *event = new GUI::Events::StateEvent(GUI::Views::widgetsid_to_viewid(widget_id), state);

    Connector *connector = get_connector_instance();
    connector->QueueEvent(event);
}