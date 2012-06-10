#include "persistencemanager.h"

#include <Wt/WDateTime>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>

#include "server/database/configurationentity.h"
#include "server/database/configentryentity.h"
#include "logger.h"

PersistenceManager* PersistenceManager::instance_ = 0;

PersistenceManager::PersistenceManager() :
    connection_("vanetizer.db")
{
    Logger::entry("info") << "Initializing database session";
    session_.setConnection(connection_);
    
    session_.mapClass< ConfigurationEntity >(ConfigurationEntity::TABLENAME);
    session_.mapClass< ConfigEntryEntity >(ConfigEntryEntity::TABLENAME);
    
    try {
        session_.createTables();
    } catch (const dbo::Exception& e) {
        Logger::entry("info") << "Problem creating tables. Probably they're already created. Exception: " << e.what();
    }
}

PersistenceManager* PersistenceManager::instance()
{
    if (!instance_)
        instance_ = new PersistenceManager();
    return instance_;
}

Wt::Dbo::QueryModel< dbo::ptr< ConfigurationEntity > >* PersistenceManager::allConfigurations()
{
    dbo::QueryModel< dbo::ptr< ConfigurationEntity > >* model = new dbo::QueryModel< dbo::ptr< ConfigurationEntity > >();
    model->setQuery(session_.find< ConfigurationEntity >());
    model->addColumn("creation_date", Wt::WString::tr("vanet.configuration.dialog.creationdate"));
    model->addColumn("name", Wt::WString::tr("vanet.configuration.dialog.name"));
    model->addColumn("id");
    model->addColumn("graph");
    return model;
}

Wt::WStandardItemModel* PersistenceManager::allEntries(long long configId)
{
    Wt::WStandardItemModel* model = new Wt::WStandardItemModel(0, 3);
    model->setHeaderData(0, Wt::Horizontal, Wt::WString::tr("mappropertyeditor.header.propertyname").toUTF8());
    model->setHeaderData(1, Wt::Horizontal, Wt::WString::tr("mappropertyeditor.header.propertyvalue").toUTF8());
    
//     dbo::Transaction transaction(session_);
//     
//     dbo::ptr< ConfigurationEntity > cfgPtr = session_.load< ConfigurationEntity >(configId);    
//     
//     transaction.commit();
    
    Wt::WStandardItem* rootItem = 0;
    Wt::WStandardItem* item = 0;
    dbo::Transaction tx(session_);
    
    dbo::collection< dbo::ptr< ConfigEntryEntity > > children = 
        session_.find< ConfigEntryEntity >().where("config_id_id = ?").bind(configId).resultList();
    
    for (dbo::collection< dbo::ptr< ConfigEntryEntity > >::const_iterator it = children.begin(); it != children.end(); ++it)
    {
//         const ConfigEntryEntity* cfgEntry = it;
        if (!(*it)->propertyValue.is_initialized() &&
            (*it)->propertyType.is_initialized() &&
            !(*it)->nodeId.is_initialized()
        )
        {
            rootItem = new Wt::WStandardItem((*it)->propertyName);
            rootItem->setData((VanetProperty) (*it)->propertyType.get());
            model->appendRow(rootItem);
        } 
        else
        {
            if (rootItem)
            {
                std::vector< Wt::WStandardItem* > propertyRow;
                item = new Wt::WStandardItem((*it)->propertyName);
                propertyRow.push_back(item);
                item = new Wt::WStandardItem((*it)->propertyValue.get_value_or(std::string("")));
                propertyRow.push_back(item);
                item = new Wt::WStandardItem((*it)->nodeId.get_value_or(std::string("")));
                propertyRow.push_back(item);
                rootItem->appendRow(propertyRow);
            }
        }
    }
    tx.commit();
    return model;
}

long long PersistenceManager::createConfiguration(const std::string& name, const std::string& imageData)
{
    Logger::entry("info") << "Creating new configuration " << name;
    dbo::Transaction transaction(session_);
    
    ConfigurationEntity* cfg = new ConfigurationEntity;
    cfg->name = name;
    cfg->graph = imageData;
    cfg->creationDate = Wt::WDateTime::fromPosixTime(boost::posix_time::second_clock::local_time());
    dbo::ptr< ConfigurationEntity > cfgPtr = session_.add(cfg);
    transaction.commit();
    long long id = cfgPtr.id();
    
    return id;
}

long long PersistenceManager::addConfigurationEntry(long long configId, ConfigEntryEntity& cfgEntry)
{
    Logger::entry("info") << "Adding a new configuration entry: " << cfgEntry.propertyName;
    dbo::Transaction transaction(session_);
    
    dbo::ptr< ConfigurationEntity > parentConfiguration = session_.load< ConfigurationEntity >(configId);
    cfgEntry.configuration = parentConfiguration;
    dbo::ptr< ConfigEntryEntity > cfgEntryPtr = session_.add(&cfgEntry);
    
    transaction.commit();
    long long id = cfgEntryPtr.id();
    
    return id;
}

void PersistenceManager::deleteConfiguration(long long int configId)
{
    Logger::entry("info") << "Removing configuration with id " << configId;
    
    dbo::Transaction transaction(session_);
    dbo::ptr< ConfigurationEntity > configEntity = session_.load< ConfigurationEntity >(configId);
    configEntity.remove();
    transaction.commit();
}

void PersistenceManager::clearConfiguration(long long int configId)
{
    Logger::entry("info") << "Clearing entries for configuration with id " << configId;
    
    dbo::Transaction transaction(session_);
    
    dbo::collection< dbo::ptr< ConfigEntryEntity > > children = 
        session_.find< ConfigEntryEntity >().where("config_id_id = ?").bind(configId).resultList();
        
    for (dbo::collection< dbo::ptr< ConfigEntryEntity > >::const_iterator it = children.begin(); it != children.end(); ++it)
    {
        (*it).remove();
    }
    transaction.commit();
}

void PersistenceManager::updateImageData(long long int configId, const std::string& imageData)
{
    Logger::entry("info") << "Updating image data for the configuration with id " << configId;
    dbo::Transaction transaction(session_);
    dbo::ptr< ConfigurationEntity > config = session_.load< ConfigurationEntity >(configId);
    config.modify()->graph = imageData;
    transaction.commit();
}

