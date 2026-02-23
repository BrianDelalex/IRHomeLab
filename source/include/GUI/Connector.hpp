#ifndef CONNECTOR_HPP_
# define CONNECTOR_HPP_

# include <wx/wx.h>

class Connector : public wxEvtHandler
{
    public:
        Connector();
        ~Connector() = default;
};

Connector *get_connector_instance(void);

#endif //!CONNECTOR_HPP_