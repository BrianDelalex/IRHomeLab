#ifndef VIEWS_ID_HPP_
# define VIEWS_ID_HPP_

# include <wx/defs.h>

# include "WidgetsID.hpp"

namespace GUI::Views
{

    consteval int consteval_widgetsid_to_viewid(WidgetsID id)
    {
        return (int)wxID_HIGHEST + (int)id;
    }

    int widgetsid_to_viewid(WidgetsID id);

    enum ViewsID
    {
        SPOTIFY_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::SPOTIFY_ID),
        DUMMY1_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY1_ID),
        DUMMY2_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY2_ID),
        DUMMY3_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY3_ID),
        DUMMY4_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY4_ID),
        DUMMY5_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY5_ID),
        DUMMY6_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY6_ID),
        DUMMY7_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY7_ID),
        DUMMY8_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY8_ID),
        DUMMY9_VIEW_ID = consteval_widgetsid_to_viewid(WidgetsID::DUMMY9_ID),
    };

} //  namespace GUI::Views

#endif //!VIEWS_ID_HPP_