# include "GUI/Views/Spotify/SpotifyView.hpp"

# include "GUI/Events/StateEvent.hpp"

namespace GUI::Views
{

    SpotifyView::SpotifyView(wxWindow *parent, const wxSize &size, ViewsID view_id) :
        IView(parent, size, view_id)
    {
        CreateView();
    }

    void SpotifyView::CreateView()
    {
        wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

        const wxColour background(30, 30, 30);

        m_left_panel = new wxPanel(this, wxID_ANY);
        m_left_panel->SetBackgroundColour(background);
        sizer->Add(m_left_panel, 1, wxEXPAND);

        m_player = new GUI::Views::Components::SpotifyPlayerPanel(this, wxDefaultSize);
        sizer->Add(m_player, 1, wxEXPAND);

        m_right_panel = new wxPanel(this, wxID_ANY);
        m_right_panel->SetBackgroundColour(background);
        sizer->Add(m_right_panel, 1, wxEXPAND);

        this->SetSizer(sizer);
    }

    void SpotifyView::UpdateView(std::shared_ptr<Core::States::IState>state)
    {
        std::cout << __FUNCTION__ << " [INFO]: Updating Spotify view" << std::endl;
        m_player->UpdateState(state);
    }
} //  namespace GUI::Views
