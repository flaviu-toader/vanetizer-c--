#ifndef AREAPROPERTYCONVERTOR_H_
#define AREAPROPERTYCONVERTOR_H_

#include <vector>
#include "abstractpropertyconvertor.h"

class AreaPropertyConvertor : public AbstractPropertyConvertor
{
public:
    static const char* const TREENODE_NAME;
    virtual void appendXml(pugi::xml_node& root, Wt::WStandardItem* treeNode);
    virtual Wt::WStandardItem* treeNode(const pugi::xml_node& root);
};

#endif // AREAPROPERTYCONVERTOR_H_
