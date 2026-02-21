#ifndef PAGE_EVENT_HPP_
# define PAGE_EVENT_HPP_

# include <wx/wx.h>

# include "WidgetsID.hpp"

namespace GUI::Events
{
    class PageEvent;
    wxDECLARE_EVENT(EVT_CHANGE_PAGE, PageEvent);

    class PageEvent : public wxEvent
    {
    public:
        PageEvent(int event_id, WidgetsID widget_id, wxEventType eventType = EVT_CHANGE_PAGE);

    
        // Inherited via wxEvent
        virtual wxEvent* Clone() const override;

        WidgetsID widget_id;
    };
} //  namespace GUI::Events

#endif //!PAGE_EVENT_HPP_