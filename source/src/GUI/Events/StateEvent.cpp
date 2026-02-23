# include "GUI/Events/StateEvent.hpp"

namespace GUI::Events
{

    wxDEFINE_EVENT(EVT_STATE_CHANGED, StateEvent);

    StateEvent::StateEvent(int id, std::shared_ptr<Core::States::IState>state, wxEventType eventType) :
        wxEvent(id, eventType),
        state(state)
    {
    }

    wxEvent* StateEvent::Clone() const
    {
        return new StateEvent(*this);
    }

} //  namespace GUI::Events