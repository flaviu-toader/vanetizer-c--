#include <string>
#include <vector>
#include <Wt/WStandardItem>

#include "abstractpropertyconvertor.h"

using namespace std;
using namespace Wt;

std::vector< WStandardItem* > AbstractPropertyConvertor::propertyRow(const string& propertyId, const string& propertyName, const string& propertyValue)
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

