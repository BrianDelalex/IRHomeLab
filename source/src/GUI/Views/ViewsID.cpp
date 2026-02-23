# include "GUI/Views/ViewsID.hpp"


namespace GUI::Views
{
    int widgetsid_to_viewid(WidgetsID id)
    {
        return (int)wxID_HIGHEST + (int)id;
    }
} //  namespace GUI::Views