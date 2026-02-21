# include "GUI/Views/Spotify/SpotifyPlayerPanel.hpp"

namespace GUI::Views::Components
{

    SpotifyPlayerPanel::SpotifyPlayerPanel(wxWindow *parent, const wxSize &size) :
        wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
    {
        SetSize(parent->GetSize());
        CreatePanel();
    }
        
    void SpotifyPlayerPanel::CreatePanel()
    {
        wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

        SetBackgroundColour(*wxBLACK);
        wxSize image_panel_size(GetSize().GetWidth() / 3, GetSize().GetHeight());
        m_image_panel = new GUI::Components::ImagePanel(this, image_panel_size);
        main_sizer->Add(m_image_panel, 0, wxALL | wxALIGN_CENTER, 10);

        this->SetSizer(main_sizer);
    }

    void SpotifyPlayerPanel::UpdateState(Core::States::IState *state)
    {
        SetBackgroundColour(*wxWHITE);
    }

} //  namespace GUI::Views::Components