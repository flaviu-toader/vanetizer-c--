#ifndef MODELTOXMLCONVERTER_H
#define MODELTOXMLCONVERTER_H

#include <pugixml/pugixml.hpp>
#include "xml/xmlhelper.h"

namespace Wt
{
    class WStandardItemModel;
}

// namespace pugi
// {
//     class xml_document;
//     class xml_node;
// }

class ModelToXmlConverter
{

public:
    ModelToXmlConverter(Node model);
    void convertXml();
private:
    void buildXml(const Node& node, pugi::xml_node& xnode);
    pugi::xml_node appendNode(const Node& node, pugi::xml_node& xnode);
    
    Node model_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
};

#endif // MODELTOXMLCONVERTER_H
