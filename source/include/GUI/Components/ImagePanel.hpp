#ifndef IMAGE_PANEL_HPP_
# define IMAGE_PANEL_HPP_

# include <wx/wx.h>

# include <memory>

namespace GUI::Components
{
    class ImagePanel : public wxPanel
    {
        public:
            ImagePanel(wxWindow *parent, const wxSize &size);

            void SetImage(const wxImage &image);
        private:
            void OnPaint(wxPaintEvent &evt);
            void Repaint(void);
            void RefreshPanel(wxDC &dc);

            std::unique_ptr<wxImage> m_image;

    };
}

#endif //!IMAGE_PANEL_HPP_
