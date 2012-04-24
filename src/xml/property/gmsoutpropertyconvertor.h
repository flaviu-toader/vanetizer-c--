#ifndef GMSOUTPROPERTYCONVERTOR_H
#define GMSOUTPROPERTYCONVERTOR_H

#include <../../home/flaviu/projects/vanetizer-c--/src/xml/property/abstractpropertyconvertor.h>


class GmsOutPropertyConvertor : public AbstractPropertyConvertor
{

public:
    static const char* const TREENODE_NAME;
    virtual Wt::WStandardItem* treeNode(const pugi::xml_node& root);
    virtual void appendXml(pugi::xml_node& root, Wt::WStandardItem* treeNode);
};

#endif // GMSOUTPROPERTYCONVERTOR_H
