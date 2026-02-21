#ifndef MAIN_FRAME_HPP_
# define MAIN_FRAME_HPP_

# include <wx/wx.h>

# include "GUI/Pages/PageHandler.hpp"

namespace GUI::Frames
{

    class MainFrame : public wxFrame
    {
        public:
            MainFrame(wxWindow* parent, wxWindowID id, const wxSize& size);

        private:
            void BindEventHandlers(void);

            GUI::Pages::PageHandler *m_page_handler;
    };

} //  namespace GUI::Frames

#endif //!MAIN_FRAME_HPP_