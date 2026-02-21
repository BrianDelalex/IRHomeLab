#ifndef PAGE_HANDLER_HPP
# define PAGE_HANDLER_HPP

# include <wx/wx.h>
# include <wx/simplebook.h>

# include "GUI/Events/PageEvent.hpp"
# include "GUI/Views/IView.hpp"

namespace GUI::Pages
{

    class PageHandler : public wxSimplebook
    {
        public:
            PageHandler(wxWindow *parent, const wxSize &size);

            void OnChangePageEvent(Events::PageEvent &event);
        private:
            void CreateViews(void);
            void BindEventHandlers(void);
    };
} // namespace GUI::Pages

#endif //!PAGE_HANDLER_HPP