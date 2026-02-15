# include "GUI/App.hpp"

# include <iostream>

wxIMPLEMENT_APP(App);
bool App::OnInit(void)
{
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "IRHomeLab");
    frame->Show();
    return true;
}