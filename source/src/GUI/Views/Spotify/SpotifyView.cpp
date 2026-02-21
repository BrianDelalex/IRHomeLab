# include "GUI/Views/Spotify/SpotifyView.hpp"

# include "GUI/Events/StateEvent.hpp"
# include "GUI/Views/ViewsID.hpp"

namespace GUI::Views
{

    SpotifyView::SpotifyView(wxWindow *parent, const wxSize &size) :
        IView(parent, size)
    {
        CreateView();
        BindEventHandlers();
    }

    void SpotifyView::CreateView()
    {
        SetBackgroundColour(*wxGREEN);
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        m_player = new GUI::Views::Components::SpotifyPlayerPanel(this, GetSize());
        sizer->Add(m_player, 0, wxALL | wxEXPAND, 10);

        this->SetSizer(sizer);
    }

    void SpotifyView::UpdateView(Core::States::IState *state)
    {
        SetBackgroundColour(*wxWHITE);
        m_player->UpdateState(state);
    }

    void SpotifyView::OnStateChangedEvent(GUI::Events::StateEvent &event)
    {
        UpdateView(event.state);
    }

    void SpotifyView::BindEventHandlers()
    {
        Bind(GUI::Events::EVT_STATE_CHANGED, &SpotifyView::OnStateChangedEvent, this, GUI::Views::SPOTIFY_VIEW_ID);
    }
} //  namespace GUI::Views