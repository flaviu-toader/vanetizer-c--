#ifndef CONFIGENTRYDAO_H
#define CONFIGENTRYDAO_H

#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>

#include "client/widgets/dialogs/abstractpropertyform.h"

class ConfigEntryEntity;
class ConfigurationEntity;

namespace dbo = Wt::Dbo;

class ConfigEntryEntity
{
public:
    //! Name of the DB table mapped to this class.
    static const char* const TABLENAME;
    
    //! Pointer to the Configuration this entry belongs to.
    dbo::ptr< ConfigurationEntity > configuration;
    
    //! Property Name to be displayed in the tree.
    std::string propertyName;
    
    //! Property Value to be displayed in the tree.
    boost::optional< std::string > propertyValue;
    
    //! VanetProperty enum type. Defines the root nodes' types.
    boost::optional< VanetProperty > propertyType;
    
    //! Id of the node. Use to generate the xmls.
    boost::optional< std::string > nodeId;
    
    template< class Action >
    void persist(Action& a)
    {
        // normal types
        dbo::field(a, propertyName, "property_name");
        dbo::field(a, propertyValue, "property_value");
        dbo::field(a, propertyType, "property_type");
        dbo::field(a, nodeId, "node_id");
        
        // N to 1 relations
        dbo::belongsTo(a, configuration, "config_id", dbo::OnDeleteCascade);
    }
};

#endif // CONFIGENTRYDAO_H
