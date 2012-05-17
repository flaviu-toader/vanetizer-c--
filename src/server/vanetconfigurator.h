#ifndef VANETCONFIGURATOR_H
#define VANETCONFIGURATOR_H

#include <vector>
#include <pugixml/pugixml.hpp>

#include "xml/xmlhelper.h"
#include "server/runners/gmsconfiguration.h"
#include "server/runners/vmsconfiguration.h"

namespace Wt
{
    class WString;
}

//! Configuration responsible class.
/*! 
 * This implementation contains the business validation logic. 
 * It creates the configurations for VanetMobiSim and GloMoSim runners from client-side node structure.
 */
class VanetConfigurator
{
public:
    VanetConfigurator(const Node& modelNode);
    
    void save();
    
    //! Performs the business validations. If these validations fail, it will fill the validationMessages parameter with all the error messages.
    bool validate(std::vector< Wt::WString >& validationMessages);
private:
    
    pugi::xml_document doc_;
    VmsConfiguration vanetMobiSimCfg_;
    GmsConfiguration gloMoSimCfg_;
};

#endif // VANETCONFIGURATOR_H
