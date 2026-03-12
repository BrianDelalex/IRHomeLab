#ifndef SPOTIFY_DEVICE_SELECTION_PANEL_HPP_
# define SPOTIFY_DEVICE_SELECTION_PANEL_HPP_

# include <wx/wx.h>
# include <wx/scrolwin.h>

# include <string>
# include <vector>

namespace GUI::Views::Components
{

class SpotifyDeviceSelectionPanel : public wxPanel
{
    public:
        SpotifyDeviceSelectionPanel(wxWindow *parent);

        void UpdateDevices(const std::vector<std::string> &devices, uint8_t selected_index);

    private:
        wxStaticText    *m_title;
        wxScrolledWindow *m_list_panel;
};

} //  namespace GUI::Views::Components

#endif //!SPOTIFY_DEVICE_SELECTION_PANEL_HPP_
