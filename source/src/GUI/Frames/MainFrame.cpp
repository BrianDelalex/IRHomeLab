# include "GUI/Frames/MainFrame.hpp"

# include "GUI/Pages/PageHandler.hpp"

# include "GUI/Events/PageEvent.hpp"

namespace GUI::Frames
{
    MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxSize& size) :
        wxFrame(parent, id, wxEmptyString, wxDefaultPosition, size)
    {
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        m_page_handler = new GUI::Pages::PageHandler(this, GetSize());
        mainSizer->Add(m_page_handler, 1, wxEXPAND);

        this->SetSizer(mainSizer);
        this->Layout();
        mainSizer->Fit(this);

        BindEventHandlers();
    }

    void MainFrame::BindEventHandlers()
    {
        Bind(GUI::Events::EVT_CHANGE_PAGE, &GUI::Pages::PageHandler::OnChangePageEvent, m_page_handler);
    }


} //  namespace GUI::Frames