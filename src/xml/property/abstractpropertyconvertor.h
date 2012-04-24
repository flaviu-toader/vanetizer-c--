
#ifndef ABSTRACTPROPERTYCONVERTOR_H_
#define ABSTRACTPROPERTYCONVERTOR_H_

#include <vector>
#include <string>
namespace Wt
{
    class WStandardItem;
}

namespace pugi
{
    class xml_node;
}

class AbstractPropertyConvertor
{
public:
    //! Converts the WStandardItem from the property tree into a vector of xml nodes.
    virtual void appendXml(pugi::xml_node& root, Wt::WStandardItem* treeNode) = 0;

    //! Converts the vector of xml nodes into a WStandardItem tree node.
    virtual Wt::WStandardItem* treeNode(const pugi::xml_node& root) = 0;
protected:
    virtual std::vector<Wt::WStandardItem *> propertyRow(const std::string& propertyId, const std::string& propertyName, const std::string& propertyValue);
};

#endif // ABSTRACTPROPERTY_H_

