#ifndef REMOTE_CONTROLLER_MOCK_FRAME_HPP_
# define REMOTE_CONTROLLER_MOCK_FRAME_HPP_

# ifdef DEBUG

# include <wx/wx.h>

namespace GUI::Debug
{
    class RemoteControllerMockFrame : public wxFrame
    {
        public:
            RemoteControllerMockFrame();

        private:
            void CreateButtons(void);
            void OnButtonClicked(wxCommandEvent &event);

            int m_fd {-1};
    };
} //  namespace GUI::Debug

# endif // DEBUG

#endif //!REMOTE_CONTROLLER_MOCK_FRAME_HPP_
