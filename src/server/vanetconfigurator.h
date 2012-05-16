#ifndef VANETCONFIGURATOR_H
#define VANETCONFIGURATOR_H

#include <pugixml/pugixml.hpp>

#include "xml/xmlhelper.h"

//! Configuration responsible class.
/*! 
 * This implementation contains the business validation logic. 
 * It creates the configurations for VanetMobiSim and GloMoSim runners from client-side node structure.
 */
class VanetConfigurator
{
public:
    VanetConfigurator(const Node& modelNode);
    
private:
    
    pugi::xml_document doc_;
};

#endif // VANETCONFIGURATOR_H
