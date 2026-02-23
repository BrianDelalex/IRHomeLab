#ifndef APP_HPP
# define APP_HPP

# include <wx/wx.h>

# include <memory>

# include "GUI/Frames/MainFrame.hpp"

# include "WidgetsID.hpp"

class App : public wxApp
{
    public:
        virtual bool OnInit(void) override;

    private:
        void ChangeViewCallback(WidgetsID widget_id);
        void UpdateStateCallback(std::shared_ptr<Core::States::IState>state, WidgetsID widget_id);

        GUI::Frames::MainFrame *frame;
};

wxDECLARE_APP(App);

#endif //!APP_HPP