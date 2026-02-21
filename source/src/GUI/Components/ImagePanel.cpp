# include "GUI/Components/ImagePanel.hpp"

namespace GUI::Components
{

    ImagePanel::ImagePanel(wxWindow *parent, const wxSize &size) :
        wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
    {
        Bind(wxEVT_PAINT, &ImagePanel::OnPaint, this);
        SetBackgroundColour(*wxRED);
    }

    void ImagePanel::SetImage(std::shared_ptr<wxImage> image)
    {
        m_image = image;
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
        int dc_width = dc.GetSize().GetWidth();
        int dc_height = dc.GetSize().GetHeight();
        int image_width = 300;
        int image_height = 300;
        if (!m_image)
        {
            dc.SetBrush(*wxBLUE_BRUSH);
            dc.DrawRectangle(dc_width / 2 - image_width / 2, dc_height / 2 - image_height / 2, image_width, image_height);
            return;
        }
        dc.DrawBitmap((wxBitmap) *m_image, image_width, image_height);
    }

} //  namespace GUI::Components