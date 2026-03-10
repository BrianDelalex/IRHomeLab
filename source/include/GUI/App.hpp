#ifndef APP_HPP
# define APP_HPP

# include <wx/wx.h>

# include <memory>

# include "GUI/Frames/MainFrame.hpp"

# include "WidgetsID.hpp"

# ifdef DEBUG
# include "Debug/RemoteControllerMockFrame.hpp"
# endif

class App : public wxApp
{
    public:
        virtual bool OnInit(void) override;

    private:
        void ChangeViewCallback(WidgetsID widget_id);
        void UpdateStateCallback(std::shared_ptr<Core::States::IState>state, WidgetsID widget_id);
        void CheckConfig(void);

        GUI::Frames::MainFrame *frame;
# ifdef DEBUG
        GUI::Debug::RemoteControllerMockFrame *m_mock_frame;
# endif
};

wxDECLARE_APP(App);

#endif //!APP_HPP
