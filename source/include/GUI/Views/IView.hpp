#ifndef IVIEW_HPP_
# define IVIEW_HPP_

# include <wx/wx.h>

# include "GUI/Events/StateEvent.hpp"
# include "GUI/Views/ViewsID.hpp"
# include "Core/States/IState.hpp"
# include "GUI/Connector.hpp"

namespace GUI::Views
{
    class IView : public wxPanel
    {
        public:
            IView(wxWindow *parent, const wxSize &size, ViewsID view_id) : wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
            {
                Connector *connector = get_connector_instance();
                connector->Bind(GUI::Events::EVT_STATE_CHANGED, &IView::OnStateChangedEvent, this, view_id);
            }
            virtual ~IView() = default;

        protected:
            virtual void CreateView() = 0;
            virtual void UpdateView(std::shared_ptr<Core::States::IState>state) = 0;
        private:
            void OnStateChangedEvent(GUI::Events::StateEvent &event)
            {
                UpdateView(event.state);
            }
    };
        
} // namespace GUI::Views

#endif //!IVIEW_HPP_