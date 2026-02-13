#ifndef APP_HPP
# define APP_HPP

# include <wx/wx.h>

class App : public wxApp
{
public:
    virtual bool OnInit(void) override;
};

wxDECLARE_APP(App);

#endif //!APP_HPP