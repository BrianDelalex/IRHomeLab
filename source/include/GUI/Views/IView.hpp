#ifndef IVIEW_HPP_
# define IVIEW_HPP_

# include <wx/wx.h>

# include "GUI/Events/StateEvent.hpp"
# include "Core/States/IState.hpp"

namespace GUI::Views
{
    class IView : public wxPanel
    {
        public:
            IView(wxWindow *parent, const wxSize &size) : wxPanel(parent, wxID_ANY, wxDefaultPosition, size) {}
            virtual ~IView() = default;

        protected:
            virtual void CreateView() = 0;
            virtual void UpdateView(Core::States::IState *state) = 0;

        private:
            // Event handlers
            void OnStateChangedEvent(GUI::Events::StateEvent &event)
            {
                UpdateView(event.state);
            }
      
    };
        
} // namespace GUI::Views

#endif //!IVIEW_HPP_