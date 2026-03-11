# include "GUI/Views/ViewsID.hpp"


namespace GUI::Views
{
    int widgetsid_to_viewid(WidgetsID id)
    {
        return static_cast<int>(wxID_HIGHEST) + static_cast<int>(id);
    }
} //  namespace GUI::Views