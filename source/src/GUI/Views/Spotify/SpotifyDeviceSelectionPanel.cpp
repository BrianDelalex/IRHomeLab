# include "GUI/Views/Spotify/SpotifyDeviceSelectionPanel.hpp"

namespace GUI::Views::Components
{

    SpotifyDeviceSelectionPanel::SpotifyDeviceSelectionPanel(wxWindow *parent) :
        wxPanel(parent, wxID_ANY, wxPoint(0, 0), parent->GetClientSize())
    {
        SetBackgroundColour(wxColour(20, 20, 20));

        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        sizer->AddStretchSpacer(1);

        m_title = new wxStaticText(this, wxID_ANY, "Select a device", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
        m_title->SetForegroundColour(wxColour(255, 255, 255));
        m_title->SetFont(wxFontInfo(13).Bold());
        sizer->Add(m_title, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 12);

        // Green separator below title
        wxPanel *line = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 2));
        line->SetBackgroundColour(wxColour(30, 215, 96));
        sizer->Add(line, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 16);

        m_list_panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxBORDER_NONE);
        m_list_panel->SetBackgroundColour(wxColour(20, 20, 20));
        m_list_panel->SetScrollRate(0, 10);
        sizer->Add(m_list_panel, 1, wxEXPAND | wxLEFT | wxRIGHT, 20);

        sizer->AddStretchSpacer(1);

        SetSizer(sizer);
        Hide();
    }

    void SpotifyDeviceSelectionPanel::UpdateDevices(const std::vector<std::string> &devices, uint8_t selected_index)
    {
        m_list_panel->DestroyChildren();

        wxBoxSizer *list_sizer = new wxBoxSizer(wxVERTICAL);

        const wxColour bg_selected(30, 215, 96);
        const wxColour bg_normal(40, 40, 40);
        const wxColour fg_selected(0, 0, 0);
        const wxColour fg_normal(255, 255, 255);

        for (std::size_t i = 0; i < devices.size(); ++i)
        {
            const bool selected = (i == static_cast<std::size_t>(selected_index));

            wxPanel *row = new wxPanel(m_list_panel, wxID_ANY);
            row->SetBackgroundColour(selected ? bg_selected : bg_normal);

            wxStaticText *label = new wxStaticText(row, wxID_ANY, wxString::FromUTF8(devices[i]), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
            label->SetForegroundColour(selected ? fg_selected : fg_normal);
            label->SetFont(wxFontInfo(11));

            wxBoxSizer *row_sizer = new wxBoxSizer(wxHORIZONTAL);
            row_sizer->Add(label, 1, wxALL | wxALIGN_CENTER_VERTICAL, 10);
            row->SetSizer(row_sizer);

            list_sizer->Add(row, 0, wxEXPAND | wxBOTTOM, 4);
        }

        m_list_panel->SetSizer(list_sizer);
        m_list_panel->FitInside();
        m_list_panel->Layout();
    }

} //  namespace GUI::Views::Components
