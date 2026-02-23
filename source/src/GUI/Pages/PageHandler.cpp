# include "GUI/Pages/PageHandler.hpp"

# include "GUI/Views/Spotify/SpotifyView.hpp"
# include "GUI/Views/DummyView.hpp"
# include "GUI/Connector.hpp"
# include "WidgetsID.hpp"

namespace GUI::Pages
{

    PageHandler::PageHandler(wxWindow *parent, const wxSize &size) :
        wxSimplebook(parent, wxID_ANY, wxDefaultPosition, size)
    {
        CreateViews();
        BindEventHandlers();
    }

    void PageHandler::CreateViews()
    {
        // Spotify view
        auto *spotifyView = new GUI::Views::SpotifyView(this, GetSize(), GUI::Views::SPOTIFY_VIEW_ID);
        InsertPage(WidgetsID::SPOTIFY_ID, spotifyView, "spotify", true);
        wxColour dummy_colors[] = {*wxRED, *wxBLUE, *wxCYAN, *wxYELLOW, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY};
        for (int i = 1; i < 10; i++)
        {   
            wxString name = wxString::Format("dummy%d", i);
            auto *dummyView = new GUI::Views::DummyView(this, GetSize(), (GUI::Views::ViewsID)(GUI::Views::DUMMY1_VIEW_ID + i - 1), dummy_colors[i - 1], name);
            InsertPage(i, dummyView, name, false);
        }
    }

    void PageHandler::BindEventHandlers()
    {
        Connector *connector = get_connector_instance();
        connector->Bind(GUI::Events::EVT_CHANGE_PAGE, &GUI::Pages::PageHandler::OnChangePageEvent, this);
    }

    void PageHandler::OnChangePageEvent(GUI::Events::PageEvent &event)
    {
        std::cout << __FUNCTION__ << " [INFO]: event received change page to " << event.widget_id << std::endl;
        if (GetPageCount() < event.widget_id)
        {
            std::cerr << __FUNCTION__ << " [WARNING]: Received page change event with invalid widget_id " << event.widget_id << std::endl;
            return;
        }
        SetSelection(event.widget_id);
    }
} //  namespace GUI::Pages