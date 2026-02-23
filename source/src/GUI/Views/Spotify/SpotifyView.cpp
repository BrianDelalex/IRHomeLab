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
        SetBackgroundColour(*wxGREEN);
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        m_player = new GUI::Views::Components::SpotifyPlayerPanel(this, GetSize());
        sizer->Add(m_player, 0, wxALL | wxEXPAND, 10);

        this->SetSizer(sizer);
    }

    void SpotifyView::UpdateView(std::shared_ptr<Core::States::IState>state)
    {
        std::cout << __FUNCTION__ << " [INFO]: Updating Spotify view" << std::endl;
        SetBackgroundColour(*wxWHITE);
        m_player->UpdateState(state);
    }
} //  namespace GUI::Views