#ifndef VIEWS_ID_HPP_
# define VIEWS_ID_HPP_

# include <wx/defs.h>

# include "WidgetsID.hpp"

namespace GUI::Views
{

    enum ViewsID
    {
        SPOTIFY_VIEW_ID = wxID_HIGHEST + WidgetsID::SPOTIFY_ID,
    };

} //  namespace GUI::Views

#endif //!VIEWS_ID_HPP_