#include "persistencemanager.h"

#include <Wt/WDateTime>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/Dbo/backend/Sqlite3>

#include "server/database/configurationentity.h"
#include "server/database/configentryentity.h"
#include "logger.h"

PersistenceManager* PersistenceManager::instance_ = 0;

PersistenceManager::PersistenceManager()
{
    Logger::entry("info") << "Initializing database session";
    dbo::backend::Sqlite3 sqlite3("vanetizer.db");
    session_.setConnection(sqlite3);
    
    session_.mapClass< ConfigurationEntity >(ConfigurationEntity::TABLENAME);
    session_.mapClass< ConfigEntryEntity >(ConfigEntryEntity::TABLENAME);
    
    session_.createTables();
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
    model->addColumn("id");
    model->addColumn("creation_date", Wt::WString::tr("vanet.configuration.dialog.creationdate"));
    model->addColumn("name", Wt::WString::tr("vanet.configuration.dialog.name"));
    return model;
}

Wt::WStandardItemModel* PersistenceManager::allEntries(long long configId)
{
    Wt::WStandardItemModel* model = new Wt::WStandardItemModel(0, 2);
    model->setHeaderData(0, Wt::Horizontal, Wt::WString::tr("mappropertyeditor.header.propertyname").toUTF8());
    model->setHeaderData(1, Wt::Horizontal, Wt::WString::tr("mappropertyeditor.header.propertyvalue").toUTF8());
    
    dbo::Transaction transaction(session_);
    
    dbo::ptr< ConfigurationEntity > cfgPtr = session_.load< ConfigurationEntity >(configId);    
    
    Wt::WStandardItem* rootItem = 0;
    Wt::WStandardItem* item = 0;
    dbo::collection< dbo::ptr< ConfigEntryEntity > >::const_iterator it;
    for (it = cfgPtr->children.begin(); it != cfgPtr->children.end(); ++it)
    {
        const ConfigEntryEntity* cfgEntry = it->get();
        if (!cfgEntry->propertyValue.is_initialized() &&
            cfgEntry->propertyType.is_initialized() &&
            !cfgEntry->nodeId.is_initialized()
        )
        {
            rootItem = new Wt::WStandardItem(cfgEntry->propertyName);
            rootItem->setData((VanetProperty) cfgEntry->propertyType);
            model->appendRow(rootItem);
        } 
        else
        {
            if (rootItem)
            {
                std::vector< Wt::WStandardItem* > propertyRow;
                item = new Wt::WStandardItem(cfgEntry->propertyName);
                propertyRow.push_back(item);
                item = new Wt::WStandardItem(cfgEntry->propertyValue);
                propertyRow.push_back(item);
                item = new Wt::WStandardItem(cfgEntry->nodeId);
                rootItem->appendRow(propertyRow);
            }
        }
    }
    transaction.commit();
    return model;
}

long long PersistenceManager::createConfiguration(const std::string& name)
{
    dbo::Transaction transaction(session_);
    
    ConfigurationEntity* cfg = new ConfigurationEntity;
    cfg->name = name;
    cfg->creationDate = Wt::WDateTime::fromPosixTime(boost::posix_time::second_clock::local_time());
    dbo::ptr< ConfigurationEntity > cfgPtr = session_.add(cfg);
    long long id = cfgPtr.id();
    
    transaction.commit();
    
    return id;
}

long long PersistenceManager::addConfigurationEntry(long long configId, ConfigEntryEntity& cfgEntry)
{
    dbo::Transaction transaction(session_);
    
    dbo::ptr< ConfigurationEntity > parentConfiguration = session_.load< ConfigurationEntity >(configId);
    cfgEntry.configuration = parentConfiguration;
    dbo::ptr< ConfigEntryEntity > cfgEntryPtr = session_.add(cfgEntry);
    long long id = cfgEntryPtr.id();
    
    transaction.commit();
    
    return id;
}
