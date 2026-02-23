# include "GUI/Connector.hpp"

# include <memory>


static std::unique_ptr<Connector> CONNECTOR_INSTANCE = std::make_unique<Connector>();

Connector *get_connector_instance()
{
    return CONNECTOR_INSTANCE.get();
}

Connector::Connector() :
 wxEvtHandler()
{}