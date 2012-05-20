#ifndef DBOCONFIGURATION_H
#define DBOCONFIGURATION_H

#include <Wt/WDateTime>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

class ConfigEntryEntity;

namespace dbo = Wt::Dbo;

// In keeping with the Wt::Dbo way of doing things as seen in tutorials and blog posts, 
//  and for the sake of brevity, all data is in public fields, and the persist implementation is in the header file.
class ConfigurationEntity
{
public:
    //! Name of the DB table mapped to this class.
    static const char* const TABLENAME;
    
    //! The configuration's creation date.
    Wt::WDateTime creationDate;
    
    //! The configuration's name.
    Wt::WString name;
    
    //! The configuration entries for this configuration.
    dbo::collection< dbo::ptr< ConfigEntryEntity > > children;
    
    //! Wt::Dbo persist method.
    template< class Action >
    void persist(Action& a)
    {
        // normal fields
        dbo::field(a, creationDate, "creation_date");
        dbo::field(a, name, "name");
        
        // 1 to N relations
        dbo::hasMany(a, children, dbo::ManyToOne);
    }
};

const char* const ConfigurationEntity::TABLENAME = "Configurations";

#endif // DBOCONFIGURATION_H
