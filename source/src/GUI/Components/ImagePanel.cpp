# include "GUI/Components/ImagePanel.hpp"

namespace GUI::Components
{

    ImagePanel::ImagePanel(wxWindow *parent, const wxSize &size) :
        wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
    {
        Bind(wxEVT_PAINT, &ImagePanel::OnPaint, this);
        SetBackgroundColour(wxColour(30, 30, 30));
    }

    void ImagePanel::SetImage(const wxImage &image)
    {
        m_image = std::make_unique<wxImage>(image);
        Refresh();
    }

    void ImagePanel::OnPaint(wxPaintEvent &evt)
    {
        wxPaintDC dc(this);
        RefreshPanel(dc);
    }

    void ImagePanel::Repaint()
    {
        wxClientDC dc(this);
        RefreshPanel(dc);
    }

    void ImagePanel::RefreshPanel(wxDC &dc)
    {
        const int w = dc.GetSize().GetWidth();
        const int h = dc.GetSize().GetHeight();

        if (!m_image)
        {
            dc.SetBrush(wxBrush(wxColour(55, 55, 55)));
            dc.SetPen(wxPen(wxColour(80, 80, 80), 1));
            dc.DrawRectangle(0, 0, w, h);

            dc.SetTextForeground(wxColour(110, 110, 110));
            dc.SetFont(wxFontInfo(36));
            const wxString note = wxString::FromUTF8("\xE2\x99\xAB"); // ♫
            wxCoord tw, th;
            dc.GetTextExtent(note, &tw, &th);
            dc.DrawText(note, (w - tw) / 2, (h - th) / 2);
            return;
        }

        const wxImage scaled = m_image->Scale(w, h, wxIMAGE_QUALITY_HIGH);
        dc.DrawBitmap(wxBitmap(scaled), 0, 0);
    }

} //  namespace GUI::Components
