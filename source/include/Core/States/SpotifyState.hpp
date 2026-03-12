#ifndef SPOTIFY_STATE_HPP
# define SPOTIFY_STATE_HPP

# include <string>
# include <vector>

# include "Core/States/IState.hpp"

namespace Core::Controllers
{
    class SpotifyController;
}

namespace Core::States
{
    enum class SpotifySubStates : uint8_t
    {
        DEFAULT,
        DEVICE_SELECTION,
    };

    struct SpotifyDeviceSelectionState
    {
        std::vector<std::string> m_available_devices;
        uint8_t m_device_selector;
    };

    class SpotifyState : public IState
    {
        friend class Core::Controllers::SpotifyController;
        public:
            SpotifyState();

            std::shared_ptr<IState> Clone() const override;

            bool IsPlaying() const
            {
                return m_playing;
            }

            std::vector<uint8_t> GetCover() const
            {
                return m_cover;
            }

            std::string GetActiveDevice() const
            {
                return m_active_device;
            }

            std::string GetSong() const
            {
                return m_song;
            }

            std::string GetArtist() const
            {
                return m_artist;
            }

            std::string GetAlbum() const
            {
                return m_album;
            }

            std::string GetPlaylist() const
            {
                return m_playlist;
            }

            SpotifySubStates GetSubState() const
            {
                return m_sub_state;
            }

            SpotifyDeviceSelectionState GetSpotifyDeviceSelectionState() const
            {
                return m_device_selection_state;
            }
        private:
            bool m_playing {false};
            std::vector<uint8_t> m_cover;
            std::string m_active_device;
            std::string m_song;
            std::string m_artist;
            std::string m_album;
            std::string m_playlist;
            SpotifySubStates m_sub_state {SpotifySubStates::DEFAULT};
            SpotifyDeviceSelectionState m_device_selection_state;
    };
} // namespace Core::States


#endif //!SPOTIFY_STATE_HPP
