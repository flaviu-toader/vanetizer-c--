
#ifndef ABSTRACTPROPERTYCONVERTOR_H_
#define ABSTRACTPROPERTYCONVERTOR_H_

#include <vector>
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
    virtual std::vector< pugi::xml_node > toXml(Wt::WStandardItem* treeNode) = 0;

    //! Converts the vector of xml nodes into a WStandardItem tree node.
    virtual Wt::WStandardItem* fromXml(std::vector< pugi::xml_node > nodes) = 0;
};

#endif // ABSTRACTPROPERTY_H_

