#ifndef ICONTROLLER_HPP_
# define ICONTROLLER_HPP_

# include <iostream>

# include "irdriver_api.h"
# include "Core/States/IState.hpp"
# include "WidgetsID.hpp"


namespace Core::Controllers
{

    using StateChangeCallback = std::function<void(std::shared_ptr<States::IState>, WidgetsID)>;
    class IController
    {
        public:
            IController(WidgetsID id) : 
                m_id(id)
            {}
            virtual ~IController() = default;

            virtual void CommandHandler(const IRButton& button) = 0;

            void RegisterStateChangeCallback(StateChangeCallback& state_change_callback)
            {
                m_state_change_callback = state_change_callback;
            }

            void UpdateState(const std::shared_ptr<States::IState> &state)
            {
                if (!m_state_change_callback)
                {
                    std::cerr << __PRETTY_FUNCTION__ << ": [ERROR] state_change_callback is not set !" << std::endl;
                    return;
                }
                m_state_change_callback(state, m_id);
            }

        protected:
            WidgetsID m_id;
        private:
            StateChangeCallback m_state_change_callback;
    };
} //  namespace Core::Controllers

#endif //!ICONTROLLER_HPP_