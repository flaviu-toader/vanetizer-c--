#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <Wt/Dbo/Session>
#include <Wt/Dbo/QueryModel>

class ConfigurationEntity;
class ConfigEntryEntity;

namespace Wt
{
    class WStandardItem;
    class WStandardItemModel;
}

namespace dbo = Wt::Dbo;

//! Big management class that handles all operations with the database. Yes, it's a singleton.
class PersistenceManager
{
public:
    static PersistenceManager* instance();
    
    //! Get the list of saved configurations as a QueryModel to set directly in the list view.
    Wt::Dbo::QueryModel< Wt::Dbo::ptr< ConfigurationEntity > >* allConfigurations();
    
    //! Get the entries for given configuration.
    Wt::WStandardItemModel* allEntries(long long configId);
    
    //! Create new configuration.
    long long createConfiguration(const std::string& name);
    
    //! Add entry to configuration.
    long long addConfigurationEntry(long long int configId, ConfigEntryEntity& cfgEntry);
    
private:
    PersistenceManager();
    
    static PersistenceManager* instance_;
    dbo::Session session_;
    
};

#endif // PERSISTENCEMANAGER_H
