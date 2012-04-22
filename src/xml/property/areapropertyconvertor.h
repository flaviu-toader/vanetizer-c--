#ifndef AREAPROPERTYCONVERTOR_H_
#define AREAPROPERTYCONVERTOR_H_

#include <vector>
#include "abstractpropertyconvertor.h"

class AreaPropertyConvertor : public AbstractPropertyConvertor
{
public:
    static const char* const TREENODE_NAME;
    virtual std::vector< pugi::xml_node > toXml(Wt::WStandardItem* treeNode);
    virtual Wt::WStandardItem* fromXml(std::vector< pugi::xml_node > nodes);
};

#endif // AREAPROPERTYCONVERTOR_H_
