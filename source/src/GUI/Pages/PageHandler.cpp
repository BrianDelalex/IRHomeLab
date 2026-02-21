# include "GUI/Pages/PageHandler.hpp"

# include "GUI/Views/Spotify/SpotifyView.hpp"
# include "GUI/Views/DummyView.hpp"
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
        auto *spotifyView = new GUI::Views::SpotifyView(this, GetSize());
        InsertPage(WidgetsID::SPOTIFY_ID - 1, spotifyView, "spotify", true);
        wxColour dummy_colors[] = {*wxRED, *wxBLUE, *wxCYAN, *wxYELLOW, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY, *wxLIGHT_GREY};
        for (int i = 2; i < 10; i++)
        {   
            wxString name = wxString::Format("dummy%d", i);
            auto *dummyView = new GUI::Views::DummyView(this, GetSize(), dummy_colors[i - 2], name);
            InsertPage(i - 1, dummyView, name, false);
        }
    }

    void PageHandler::BindEventHandlers()
    {
    }

    void PageHandler::OnChangePageEvent(GUI::Events::PageEvent &event)
    {
        std::cout << __FUNCTION__ << " [INFO]: event received change page to " << event.widget_id << std::endl;
        if (GetPageCount() < event.widget_id)
        {
            std::cerr << __FUNCTION__ << " [WARNING]: Received page change event with invalid widget_id " << event.widget_id << std::endl;
            return;
        }
        SetSelection(event.widget_id - 1);
    }
} //  namespace GUI::Pages