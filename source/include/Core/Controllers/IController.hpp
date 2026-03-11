#ifndef ICONTROLLER_HPP_
# define ICONTROLLER_HPP_

# include <functional>

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

            void RegisterStateChangeCallback(const StateChangeCallback& state_change_callback)
            {
                m_state_change_callback = state_change_callback;
            }

            void UpdateState(const std::shared_ptr<States::IState> &state);

        protected:
            WidgetsID m_id;
        private:
            StateChangeCallback m_state_change_callback;
    };
} //  namespace Core::Controllers

#endif //!ICONTROLLER_HPP_
