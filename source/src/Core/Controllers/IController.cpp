# include "Core/Controllers/IController.hpp"

# include <iostream>

namespace Core::Controllers
{
    void IController::UpdateState(const std::shared_ptr<States::IState> &state)
    {
        if (!m_state_change_callback)
        {
            std::cerr << __PRETTY_FUNCTION__ << ": [ERROR] state_change_callback is not set !" << std::endl;
            return;
        }
        m_state_change_callback(state, m_id);
    }
}  //  namespace Core::Controllers
