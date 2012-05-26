#ifndef VANETCONFIGURATOR_H
#define VANETCONFIGURATOR_H

#include <vector>
#include <pugixml.hpp>

#include "xml/xmlhelper.h"
#include "server/runners/gmsconfiguration.h"
#include "server/runners/vmsconfiguration.h"

namespace Wt
{
    class WString;
    class WStandardItemModel;
}

//! Configuration responsible class.
/*! 
 * This implementation contains the business validation logic. 
 * It creates the configurations for VanetMobiSim and GloMoSim runners from client-side node structure.
 */
class VanetConfigurator
{
public:
    
    //! Value of the graph field on the configuration entity in case it's a randomly generated map.
    static const char* const RANDOM_MAP;
    
    VanetConfigurator();
    
    void modelNode(const Node& modelNode);
    
    void save(Wt::WStandardItemModel* model, const std::string& configurationName, const std::string& imageData);
    
    //! Performs the business validations. If these validations fail, it will fill the validationMessages parameter with all the error messages.
    bool validate(std::vector< Wt::WString >& validationMessages);
private:
    
    struct routingNodePredicate
    {
        bool operator()(pugi::xml_node node)
        {
            return std::string(node.name()) == std::string("routingprotocol");
        }
    };
    
    struct nodesPredicate
    {
        bool operator()(pugi::xml_node node)
        {
            return std::string(node.name()) == std::string("nodegroup") || 
                std::string(node.name()) == std::string("node");
        }
    };
    
    struct dimxPredicate
    {
        bool operator()(pugi::xml_node node)
        {
            return std::string(node.name()) == std::string("dimx");
        }
    };
    
    struct dimyPredicate
    {
        bool operator()(pugi::xml_node node)
        {
            return std::string(node.name()) == std::string("dimy");
        }
    };
    
    struct nodeCountPredicate
    {
        bool operator()(pugi::xml_node node)
        {
            return std::string(node.name()) == std::string("number_of_nodes");
        }
    };
    
    /*!
     * This method is responsible with creating the separate configurations for the simulators.
     * It reorders the xml for VanetMobiSim so that it is valid, removes the GloMoSim settings
     * from it and populates the Gms and Vms configuration objects.
     */
    void fillConfiguration();
    
    //! This method persists the given configuration.
    void persistModel(Wt::WStandardItemModel* model, const std::string& configurationName, const std::string& imageData);
    
    pugi::xml_document doc_;
    VmsConfiguration vanetMobiSimCfg_;
    GmsConfiguration gloMoSimCfg_;
    bool isValid_;
};

#endif // VANETCONFIGURATOR_H
