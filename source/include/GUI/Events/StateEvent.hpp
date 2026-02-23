#ifndef STATE_EVENT_HPP_
# define STATE_EVENT_HPP_

# include <wx/event.h>

# include <memory>

# include "Core/States/IState.hpp"

namespace GUI::Events
{
    class StateEvent;
    wxDECLARE_EVENT(EVT_STATE_CHANGED, StateEvent);

    class StateEvent : public wxEvent
    {
    public:
        StateEvent(int id, std::shared_ptr<Core::States::IState> state, wxEventType eventType = EVT_STATE_CHANGED);

    
        // Inherited via wxEvent
        virtual wxEvent* Clone() const override;

        std::shared_ptr<Core::States::IState> state;
    };
} //  namespace GUI::Events

#endif //!STATE_EVENT_HPP_