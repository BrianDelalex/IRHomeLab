#ifndef DUMMY_VIEW_HPP_
# define DUMMY_VIEW_HPP_

# include "GUI/Views/IView.hpp"
namespace GUI::Views
{
    class DummyView : public GUI::Views::IView
    {
        public:
            DummyView(wxWindow *parent, const wxSize &size, const wxColour &colour, const wxString &name) : IView(parent, size) 
            {
                SetBackgroundColour(colour);
                wxStaticText *label = new wxStaticText(this, wxID_ANY, name, wxDefaultPosition, wxSize(500, 500), wxALIGN_CENTER);
            }

        protected:
            void CreateView(void) override {}
            void UpdateView(Core::States::IState *state) override {}
    };

} //  namespace GUI::Views
#endif //!DUMMY_VIEW_HPP_