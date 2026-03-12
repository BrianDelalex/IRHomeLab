#ifndef SPOTIFY_PLAYER_PANEL_HPP_
# define SPOTIFY_PLAYER_PANEL_HPP_

# include <wx/wx.h>

# include "GUI/Components/ImagePanel.hpp"
# include "GUI/Views/Spotify/SpotifyDeviceSelectionPanel.hpp"
# include "Core/States/IState.hpp"

namespace GUI::Views::Components
{

class SpotifyPlayerPanel : public wxPanel
{
    public:
        SpotifyPlayerPanel(wxWindow *parent, const wxSize &size);

        void UpdateState(std::shared_ptr<Core::States::IState>state);

    private:
        void CreatePanel(void);
        static void TintWhite(wxImage &image);

        GUI::Components::ImagePanel          *m_image_panel;
        SpotifyDeviceSelectionPanel          *m_device_panel {nullptr};
        wxStaticBitmap *m_spotify_logo;
        wxBitmapButton *m_play_resume_btn;
        std::unique_ptr<wxImage> m_image_play;
        std::unique_ptr<wxImage> m_image_pause;
        bool m_playing {false};

        wxStaticText *m_text_song;
        wxStaticText *m_text_artist;
        wxStaticText *m_text_album;
        wxStaticText *m_text_playlist;
        wxStaticText *m_text_device;
};

} //  namespace GUI::Views::Components

#endif //!SPOTIFY_PLAYER_PANEL_HPP_
