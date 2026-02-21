#ifndef APP_HPP
# define APP_HPP

# include <wx/wx.h>

# include "GUI/Frames/MainFrame.hpp"

# include "WidgetsID.hpp"

class App : public wxApp
{
    public:
        virtual bool OnInit(void) override;

        void ChangeViewCallback(WidgetsID view_id);

    private:
        GUI::Frames::MainFrame *frame;
};

wxDECLARE_APP(App);

#endif //!APP_HPP