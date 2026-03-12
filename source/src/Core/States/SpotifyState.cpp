# include "Core/States/SpotifyState.hpp"

# include <memory>

namespace Core::States
{
    SpotifyState::SpotifyState() :
        IState()
    {
    }

    std::shared_ptr<IState> SpotifyState::Clone() const
    {
        return std::make_shared<SpotifyState>(*this);
    }
}  //  Core::States
