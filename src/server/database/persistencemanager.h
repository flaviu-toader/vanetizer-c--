#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <Wt/Dbo/Session>
#include <Wt/Dbo/QueryModel>
#include <Wt/Dbo/backend/Sqlite3>

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
    long long createConfiguration(const std::string& name, const std::string& imageData);
    
    //! Add entry to configuration.
    long long addConfigurationEntry(long long int configId, ConfigEntryEntity& cfgEntry);
    
    //! Remove a configuration and all its entries.
    void deleteConfiguration(long long configId);
    
    //! Remove a configuration's entries.
    void clearConfiguration(long long configId);
    
    void updateImageData(long long configId, const std::string& imageData);
    
    //! Get the image data for the given configuration id.
    std::string imageData(long long configId);
    
private:
    PersistenceManager();
    
    static PersistenceManager* instance_;
    dbo::backend::Sqlite3 connection_;
    dbo::Session session_;
    
};

#endif // PERSISTENCEMANAGER_H
