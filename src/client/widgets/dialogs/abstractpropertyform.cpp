#include <vector>
#include <string>

#include <Wt/WStandardItem>

#include "abstractpropertyform.h"

using namespace Wt;
    
const char* const AbstractPropertyForm::LANE_CHANGING_MODEL = "polito.uomm.IDM_LC";
const char* const AbstractPropertyForm::INTERSECTION_MANAGEMENT_MODEL = "polito.uomm.IDM_IM";


std::vector<WStandardItem *> AbstractPropertyForm::propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue)
{
    std::vector<WStandardItem *> propertyItems;
    WStandardItem *item;

    // tree column 0: property name
    item = new WStandardItem(propertyName);
    propertyItems.push_back(item);

    // tree column 1: property value
    item = new WStandardItem(propertyValue);
    propertyItems.push_back(item);
    
    // tree column 2: property id (hidden column)
    item = new WStandardItem(propertyId);
    propertyItems.push_back(item);

    return propertyItems;
}


std::vector< std::string, std::allocator< std::string > > AbstractPropertyForm::feedbackMessages()
{
    return messages_;
}

bool AbstractPropertyForm::validate()
{
    return true;
}
