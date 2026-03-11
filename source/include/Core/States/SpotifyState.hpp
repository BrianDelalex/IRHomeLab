#ifndef SPOTIFY_STATE_HPP
# define SPOTIFY_STATE_HPP

# include <vector>

# include "Core/States/IState.hpp"

namespace Core::States
{
    class SpotifyState : public IState
    {
        public:
            SpotifyState();

            std::shared_ptr<IState> Clone() const override;
        private:
            bool m_playing {false};
            std::vector<uint8_t> m_cover;
    };
} // namespace Core::States


#endif //!SPOTIFY_STATE_HPP
