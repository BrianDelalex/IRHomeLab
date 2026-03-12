# include "GUI/Views/Spotify/SpotifyPlayerPanel.hpp"

# include <wx/mstream.h>
# include <wx/image.h>

# include "GUI/icons/play.hpp"
# include "GUI/icons/pause.hpp"
# include "GUI/icons/spotify.hpp"
# include "Core/States/SpotifyState.hpp"

namespace GUI::Views::Components
{

    void SpotifyPlayerPanel::TintWhite(wxImage &image)
    {
        unsigned char *data  = image.GetData();
        unsigned char *alpha = image.HasAlpha() ? image.GetAlpha() : nullptr;

        const int pixel_count = image.GetWidth() * image.GetHeight();
        for (int i = 0; i < pixel_count; ++i)
        {
            const unsigned char a = alpha ? alpha[i] : 255;
            data[i * 3 + 0] = a; // R
            data[i * 3 + 1] = a; // G
            data[i * 3 + 2] = a; // B
        }
    }

    SpotifyPlayerPanel::SpotifyPlayerPanel(wxWindow *parent, const wxSize &size) :
        wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
    {
        SetSize(parent->GetSize());
        CreatePanel();
    }

    void SpotifyPlayerPanel::CreatePanel()
    {
        wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

        {
            wxMemoryInputStream stream(GUI::Icons::play_png, GUI::Icons::play_png_len);
            m_image_play = std::make_unique<wxImage>(stream, wxBITMAP_TYPE_PNG);
            if (!m_image_play->IsOk())
            {
                std::cerr << __PRETTY_FUNCTION__ << ": [ERROR] Failed to load play icon." << std::endl;
                wxTheApp->Exit();
                return;
            }
            m_image_play->Rescale(48, 48, wxIMAGE_QUALITY_HIGH);
            TintWhite(*m_image_play);
        }
        {
            wxMemoryInputStream stream(GUI::Icons::pause_png, GUI::Icons::pause_png_len);
            m_image_pause = std::make_unique<wxImage>(stream, wxBITMAP_TYPE_PNG);
            if (!m_image_pause->IsOk())
            {
                std::cerr << __PRETTY_FUNCTION__ << ": [ERROR] Failed to load pause icon." << std::endl;
                wxTheApp->Exit();
                return;
            }
            m_image_pause->Rescale(48, 48, wxIMAGE_QUALITY_HIGH);
            TintWhite(*m_image_pause);
        }

        const wxColour spotify_green(30, 215, 96);
        const wxColour white(255, 255, 255);
        const wxColour light_grey(180, 180, 180);

        SetBackgroundColour(wxColour(30, 30, 30));

        main_sizer->AddStretchSpacer(1);

        // Spotify logo (white, scaled up)
        {
            wxMemoryInputStream stream(GUI::Icons::spotify_png, GUI::Icons::spotify_png_len);
            wxImage spotify_image(stream, wxBITMAP_TYPE_PNG);
            if (spotify_image.IsOk())
            {
                spotify_image.Rescale(64, 64, wxIMAGE_QUALITY_HIGH);
                TintWhite(spotify_image);

                m_spotify_logo = new wxStaticBitmap(this, wxID_ANY, wxBitmap(spotify_image));
                main_sizer->Add(m_spotify_logo, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);
            }
        }

        // Spotify green line below logo
        wxPanel *top_line = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2));
        top_line->SetBackgroundColour(spotify_green);
        main_sizer->Add(top_line, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 12);

        // Cover art
        wxSize image_panel_size(300, 300);
        m_image_panel = new GUI::Components::ImagePanel(this, image_panel_size);
        main_sizer->Add(m_image_panel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 12);

        // Song title
        m_text_song = new wxStaticText(this, wxID_ANY, "---", wxDefaultPosition, wxSize(260, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_ELLIPSIZE_END);
        m_text_song->SetForegroundColour(white);
        m_text_song->SetFont(wxFontInfo(14).Bold());
        main_sizer->Add(m_text_song, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);

        // Artist
        m_text_artist = new wxStaticText(this, wxID_ANY, "---", wxDefaultPosition, wxSize(260, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_ELLIPSIZE_END);
        m_text_artist->SetForegroundColour(light_grey);
        m_text_artist->SetFont(wxFontInfo(11));
        main_sizer->Add(m_text_artist, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);

        // Album
        m_text_album = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(260, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_ELLIPSIZE_END);
        m_text_album->SetForegroundColour(light_grey);
        m_text_album->SetFont(wxFontInfo(9));
        main_sizer->Add(m_text_album, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);

        // Playlist (optional, Spotify green)
        m_text_playlist = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(260, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_ELLIPSIZE_END);
        m_text_playlist->SetForegroundColour(spotify_green);
        m_text_playlist->SetFont(wxFontInfo(9));
        main_sizer->Add(m_text_playlist, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);

        // Spotify green separator
        wxPanel *separator = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2));
        separator->SetBackgroundColour(spotify_green);
        main_sizer->Add(separator, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 12);

        // Play/pause button
        wxBitmap bmp(*m_image_pause);
        m_play_resume_btn = new wxBitmapButton(this, wxID_ANY, bmp, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        m_play_resume_btn->SetBackgroundColour(wxColour(30, 30, 30));
        main_sizer->Add(m_play_resume_btn, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 12);

        // Active device
        m_text_device = new wxStaticText(this, wxID_ANY, "No device selected", wxDefaultPosition, wxSize(260, -1), wxALIGN_CENTRE_HORIZONTAL | wxST_ELLIPSIZE_END);
        m_text_device->SetForegroundColour(light_grey);
        m_text_device->SetFont(wxFontInfo(9));
        main_sizer->Add(m_text_device, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 6);

        main_sizer->AddStretchSpacer(1);

        this->SetSizer(main_sizer);

        // Overlay — not in the sizer, floats on top of panel content
        m_device_panel = new SpotifyDeviceSelectionPanel(this);

        Bind(wxEVT_SIZE, [this](wxSizeEvent &e) {
            if (m_device_panel)
                m_device_panel->SetSize(GetClientSize());
            e.Skip();
        });
    }

    void SpotifyPlayerPanel::UpdateState(std::shared_ptr<Core::States::IState>state)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        auto *spotify_state = dynamic_cast<Core::States::SpotifyState*>(state.get());
        if (!spotify_state)
        {
            std::cerr << __PRETTY_FUNCTION__ << "Failed to cast IState to SpotifyState" << std::endl;
            return;
        }

        if (spotify_state->IsPlaying() != m_playing)
        {
            m_playing = spotify_state->IsPlaying();
            m_play_resume_btn->SetBitmap(wxBitmap(m_playing ? *m_image_play : *m_image_pause));
        }

        m_text_song->SetLabel(spotify_state->GetSong().empty() ? "---" : spotify_state->GetSong());
        m_text_artist->SetLabel(spotify_state->GetArtist().empty() ? "---" : spotify_state->GetArtist());
        m_text_album->SetLabel(spotify_state->GetAlbum());

        const auto playlist = spotify_state->GetPlaylist();
        m_text_playlist->SetLabel(playlist.empty() ? "" : "\u25B6 " + playlist);

        const auto device = spotify_state->GetActiveDevice();
        m_text_device->SetLabel(device.empty() ? "" : "Playing on: " + device);

        Layout();

        if (spotify_state->GetSubState() == Core::States::SpotifySubStates::DEVICE_SELECTION)
        {
            const auto &sel = spotify_state->GetSpotifyDeviceSelectionState();
            m_device_panel->UpdateDevices(sel.m_available_devices, sel.m_device_selector);
            m_device_panel->SetSize(GetClientSize());
            m_device_panel->Raise();
            m_device_panel->Show();
            m_device_panel->Refresh();
            m_device_panel->Update();
            return;
        }

        m_device_panel->Hide();
        Refresh();
        Update();

        auto cover = spotify_state->GetCover();
        if (!cover.empty())
        {
            wxMemoryInputStream stream(cover.data(), cover.size());
            wxImage image;
            if (image.LoadFile(stream, wxBITMAP_TYPE_ANY))
            {
                m_image_panel->SetImage(image);
            }
        }
    }

} //  namespace GUI::Views::Components
