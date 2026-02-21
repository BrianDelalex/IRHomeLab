# include "GUI/Events/PageEvent.hpp"

namespace GUI::Events
{

    wxDEFINE_EVENT(EVT_CHANGE_PAGE, PageEvent);

    PageEvent::PageEvent(int event_id, WidgetsID widget_id, wxEventType eventType) :
        wxEvent(event_id, eventType),
        widget_id(widget_id)
    {
    }

    wxEvent* PageEvent::Clone() const
    {
        return new PageEvent(*this);
    }

} //  namespace GUI::Events