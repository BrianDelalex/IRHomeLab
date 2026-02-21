#ifndef SPOTIFY_PLAYER_PANEL_HPP_
# define SPOTIFY_PLAYER_PANEL_HPP_

# include <wx/wx.h>

# include "GUI/Components/ImagePanel.hpp"
# include "Core/States/IState.hpp"

namespace GUI::Views::Components
{

class SpotifyPlayerPanel : public wxPanel
{
    public:
        SpotifyPlayerPanel(wxWindow *parent, const wxSize &size);

        void UpdateState(Core::States::IState *state);

    private:
        void CreatePanel(void);

        GUI::Components::ImagePanel *m_image_panel;
};

} //  namespace GUI::Views::Components

#endif //!SPOTIFY_PLAYER_PANEL_HPP_