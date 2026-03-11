# include "GUI/App.hpp"

# include <iostream>

# include "GUI/Events/PageEvent.hpp"
# include "GUI/Views/ViewsID.hpp"
# include "GUI/Connector.hpp"

# include "Core/ApplicationCore.hpp"
# include "Config/AppConfig.hpp"

wxIMPLEMENT_APP(App);
bool App::OnInit(void)
{
    frame = new GUI::Frames::MainFrame(nullptr, wxID_ANY, wxSize(1920, 1080));
    frame->Show();
    CheckConfig();

# ifdef DEBUG
    m_mock_frame = new GUI::Debug::RemoteControllerMockFrame();
    m_mock_frame->Show();
    wxPoint main_pos = frame->GetPosition();
    wxSize main_size = frame->GetSize();
    wxSize mock_size = m_mock_frame->GetSize();
    m_mock_frame->SetPosition(wxPoint(main_pos.x + main_size.GetWidth() - mock_size.GetWidth(), main_pos.y));
# endif

    auto& app_core = Core::ApplicationCore::GetInstance();
    try
    {
        app_core.Init();
    } catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << __FUNCTION__ << ": [EXCEPTION] caught: " << e.what() << std::endl;
        wxMessageBox("IRHomeLab has failed to connect to irdriver. Make sure that the driver is running/installed!", "Initialization error", wxOK);
        return false;
    }
    app_core.RegisterPageChangeCallback(std::bind_front(&App::ChangeViewCallback, this));
    app_core.RegisterUpdateStateCallback(std::bind_front(&App::UpdateStateCallback, this));

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

void App::CheckConfig()
{
    auto& config = Config::AppConfig::GetInstance();

    if (!config.Contains("spotify_client"))
    {
        std::cerr << "Invalid Spotify setup. (prompting user...)" << std::endl;
        wxTextEntryDialog client_id_dialog(nullptr, "Enter your Spotify Client ID:", "Spotify Setup");
        if (client_id_dialog.ShowModal() != wxID_OK)
        {
            return;
        }

        wxTextEntryDialog client_secret_dialog(nullptr, "Enter your spotify Client Secret:", "Spotify Setup");
        if (client_secret_dialog.ShowModal() != wxID_OK)
        {
            return;
        }
        config.Set("spotify_client/client_id", client_id_dialog.GetValue().ToStdString());
        config.Set("spotify_client/client_secret", client_secret_dialog.GetValue().ToStdString());
        config.Save();
    }
}
