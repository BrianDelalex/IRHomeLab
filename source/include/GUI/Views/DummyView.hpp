#ifndef DUMMY_VIEW_HPP_
# define DUMMY_VIEW_HPP_

# include "GUI/Views/IView.hpp"

# include "Core/Controllers/DummyController.hpp"

namespace GUI::Views
{
    class DummyView : public GUI::Views::IView
    {
        public:
            DummyView(wxWindow *parent, const wxSize &size, ViewsID view_id, const wxColour &colour, const wxString &name) : IView(parent, size, view_id)
            {
                SetBackgroundColour(colour);
                wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
                wxStaticText *label = new wxStaticText(this, wxID_ANY, name, wxDefaultPosition, wxSize(500, 100), wxALIGN_CENTER);
                sizer->Add(label, 0, wxEXPAND | wxALL, 10);

                m_txt_volume = new wxStaticText(this, wxID_ANY, "Volume: 0", wxDefaultPosition, wxSize(500, 100), wxTEXT_ALIGNMENT_CENTER);
                sizer->Add(m_txt_volume, 0, wxEXPAND | wxALL, 10);

                m_txt_play_pause = new wxStaticText(this, wxID_ANY, "Paused", wxDefaultPosition, wxSize(500, 100), wxTEXT_ALIGNMENT_CENTER);
                sizer->Add(m_txt_play_pause, 0, wxEXPAND | wxALL, 10);

                this->SetSizer(sizer);
                this->Fit();
            }

        protected:
            void CreateView(void) override {}
            void UpdateView(std::shared_ptr<Core::States::IState>state) override
            {
                Core::States::DummyState* dummy_state = dynamic_cast<Core::States::DummyState *>(state.get());
                if (!dummy_state) {
                    std::cerr << __PRETTY_FUNCTION__ << ": [ERROR] the received state cannot be casted to DummyState!" << std::endl;
                    return;
                }
                m_txt_volume->SetLabelText(wxString::Format("Volume: %d", dummy_state->GetVolume()));
                m_txt_play_pause->SetLabelText(dummy_state->IsPlaying() ? "Playing" : "Paused");
            }

        private:
            wxStaticText *m_txt_volume;
            wxStaticText *m_txt_play_pause;
    };

} //  namespace GUI::Views
#endif //!DUMMY_VIEW_HPP_
