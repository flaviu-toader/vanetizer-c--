#include <string>
#include <boost/lexical_cast.hpp>

#include <Wt/WString>

#include "vanetconfigurator.h"
#include "xml/modeltoxmlconverter.h"
#include "logger.h"

using namespace std;
using namespace pugi;

VanetConfigurator::VanetConfigurator()
{
    isValid_ = false;
}

void VanetConfigurator::modelNode(const Node& modelNode)
{
    ModelToXmlConverter converter(modelNode);
    string xml = converter.convert();
    doc_.load(xml.c_str());
}


bool VanetConfigurator::validate(vector< Wt::WString >& validationMessages)
{
    isValid_ = true;
    doc_.save_file("full.xml");
    xml_node root = doc_.child("universe");
    // check for spatial model
    xml_node n = root.find_child_by_attribute("class", "de.uni_stuttgart.informatik.canu.spatialmodel.core.SpatialModel");
    if (!n)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nospatialmodel"));
        isValid_ = false;
    }
    
    // check for routing protocol
    xml_node routingNode = root.find_node(routingNodePredicate());
    if (!routingNode)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.noroutingprotocol"));
        isValid_ = false;
    }
    
    // check for GloMoSim output 
    n = root.find_child_by_attribute("extension", "class", "de.uni_stuttgart.informatik.canu.mobisim.extensions.GlomosimOutput");
    if (!n)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nogmsout"));
        isValid_ = false;
    }
    
    // check for nodes or nodegroups
    n = root.find_child(nodesPredicate());
    if (!n)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nonodes"));
        isValid_ = false;
    }
    
    // check for time simulation node.
    // TODO: document about this validation rule!
    n = root.find_child_by_attribute("extension", "class", "de.uni_stuttgart.informatik.canu.mobisim.simulations.TimeSimulation");
    if (!n)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.notimesim"));
        isValid_ = false;
    }
    
    // check for simulation area definition.
    // TODO: document about this validation rule!
    n = root.find_child(dimxPredicate());
    if (!n)
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nodimx"));
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nodimy"));
        isValid_ = false;
    }
    
    // check if number of nodes corresponds to selected routing protocol
    // TODO: document me!
    n = root.find_child(nodeCountPredicate());
    if (routingNode && n)
    {
        try {
            int count = boost::lexical_cast<int>(string(n.text().as_string()));
            if(routingNode.value() == Wt::WString::tr("vanet.property.form.routing.combo.wrp").toUTF8()
                && count > 99
            )
            {
                validationMessages.push_back(Wt::WString::tr("business.validation.error.badcount"));
                isValid_ = false;
            }
        } catch (boost::bad_lexical_cast const&) {
            Logger::entry("error") << "Bad lexical cast to int of string " << n.value();
        }
    }
    return isValid_;
}

void VanetConfigurator::save()
{
    if (!isValid_) 
   {
        Logger::entry("error") << "The configuration is invalid. Cannot save!";
        return;
    }
    fillConfiguration();
    gloMoSimCfg_.toFile();
//     doc_.save_file("scenario.xml");
}

void VanetConfigurator::fillConfiguration()
{
    xml_node root = doc_.child("universe");
    xml_node n = root.find_child(routingNodePredicate());
    if (n)
    {
        gloMoSimCfg_.protocol(string(n.text().as_string()));
        root.remove_child(n);
    }
    
    n = root.find_child_by_attribute("extension", "class", "de.uni_stuttgart.informatik.canu.mobisim.simulations.TimeSimulation");
    if (n) gloMoSimCfg_.simulationTime(string(n.attribute("param").value()));

    n = root.find_child(dimxPredicate());
    if (n) gloMoSimCfg_.dimx(string(n.text().as_string()));
    
    n = root.find_child(dimyPredicate());
    if (n) gloMoSimCfg_.dimy(string(n.text().as_string()));
    
    n = root.find_child(nodeCountPredicate());
    if (n)
    {
        gloMoSimCfg_.nodeCount(string(n.text().as_string()));
        root.remove_child(n);
    }
    doc_.save_file("scenario.xml");
}

