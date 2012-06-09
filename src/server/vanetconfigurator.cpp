#include <string>
#include <boost/lexical_cast.hpp>

#include <Wt/WString>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>

#include "vanetconfigurator.h"
#include "server/database/persistencemanager.h"
#include "server/database/configentryentity.h"
#include "server/database/configurationentity.h"
#include "xml/modeltoxmlconverter.h"
#include "logger.h"

using namespace std;
using namespace pugi;

const char* const VanetConfigurator::RANDOM_MAP = "__random__";

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
    // TODO: Remove this return after done testing!
    return isValid_;
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

long long VanetConfigurator::save(Wt::WStandardItemModel* model, const string& configurationName, const string& imageData)
{
    if (!isValid_) 
    {
        Logger::entry("error") << "The configuration is invalid. Cannot save!";
        return 0;
    }
    
    return persistModel(model, createConfiguration(configurationName, imageData));
//     fillConfiguration();
//     gloMoSimCfg_.toFile();
//     doc_.save_file("scenario.xml");
}

void VanetConfigurator::update(Wt::WStandardItemModel* model, long long int configId, const string& imageData)
{
    if (!isValid_)
    {
        Logger::entry("error") << "The configuration is invalid. Cannot update!";
        return;
    }
    PersistenceManager::instance()->clearConfiguration(configId);
    PersistenceManager::instance()->updateImageData(configId, imageData);
    persistModel(model, configId);
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

long long int VanetConfigurator::createConfiguration(const string& configurationName, const string& imageData)
{
    long long configurationId = 0;
    try {
        configurationId = PersistenceManager::instance()->createConfiguration(configurationName, imageData);
    } catch(const Wt::Dbo::Exception& e) {
        Logger::entry("error") << "Error creating configuration! Exception: " << e.what();
        return configurationId;
    } catch(...) {
        Logger::entry("error") << "Unknown exception occured while creating configuration!";
        return configurationId;
    }
    return configurationId;
}


long long VanetConfigurator::persistModel(Wt::WStandardItemModel* model, long long int configurationId)
{
    Logger::entry("info") << "Model has " << model->rowCount() << " rows";
    for (int ri = 0; ri < model->rowCount(); ri++)
    {
        ConfigEntryEntity* cfgEntry = new ConfigEntryEntity();
        cfgEntry->propertyName = model->item(ri)->text().toUTF8();
        cfgEntry->propertyType = boost::any_cast<VanetProperty>(model->item(ri)->data());
        PersistenceManager::instance()->addConfigurationEntry(configurationId, *cfgEntry);
        Wt::WStandardItem* currentRoot = model->item(ri);
        for (int row = 0; row < currentRoot->rowCount(); row++)
        {
            cfgEntry = new ConfigEntryEntity();
            for (int column = 0; column < currentRoot->columnCount(); column++)
            {
                string value = currentRoot->child(row, column)->text().toUTF8();
                switch (column)
                {
                    case 0:
                        cfgEntry->propertyName = value;
                        break;
                    case 1:
                        cfgEntry->propertyValue = value;
                        break;
                    case 2:
                        cfgEntry->nodeId = value;
                        break;
                    default:
                        Logger::entry("error") << "VanetConfigurator::persistModel *** Column out of bounds!";
                }
                
            }
            PersistenceManager::instance()->addConfigurationEntry(configurationId, *cfgEntry);
        }
    }
    return configurationId;
}
