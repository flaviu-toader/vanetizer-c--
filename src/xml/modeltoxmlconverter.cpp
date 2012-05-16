#include <string>
#include <list>
#include <boost/any.hpp>
#include <pugixml/pugixml.hpp>

#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>

#include "modeltoxmlconverter.h"
#include "logger.h"
#include "client/widgets/dialogs/abstractpropertyform.h"
#include "xml/property/abstractpropertyconvertor.h"
#include "xml/property/areapropertyconvertor.h"
#include "xml/xmlhelper.h"

using namespace Wt;
using namespace std;
using namespace pugi;

ModelToXmlConverter::ModelToXmlConverter(Node model) :
    model_(model)
{
    root_ = doc_.append_child(model_.name().c_str());
}

void ModelToXmlConverter::convertXml()
{
//     list< Node > children = model_.children();
//     list< Node >::iterator it = children.begin();
//     for (; it != children.end(); ++it)
//     {
//         xml_node newNode = root_.append_child(it->name().c_str());
//         if (newNode.empty()) 
//         {
//             Logger::entry("info") << "Error when adding new xml node " << it->name() << ". Skipping node.";
//             continue;
//         }
//         list< Attribute > attributes = it->attributes();
//         list< Attribute >::iterator attrIt = attributes.begin();
//         for (; attrIt != attributes.end(); ++attrIt)
//         {
//             xml_attribute attr = newNode.append_attribute(attrIt->name().c_str());
//             if (attr.empty())
//             {
//                 Logger::entry("info") << "Error when adding new attribute " << attrIt->name() << " to node " << it->name() << ". Skipping attribute.";
//                 continue;
//             }
//             attr.set_value(attrIt->value().c_str());
//         }
//         if (it->children().size() != 0)
//         {
//             
//         }
//     }

    buildXml(model_, root_);
    
    doc_.save_file("test.xml");
}

void ModelToXmlConverter::buildXml(const Node& node, xml_node& xnode)
{
    Logger::entry("info") << "Appending first child " << node.name();

    if (node.children().empty())
    {
        appendNode(node, xnode);
        return;
    }
    list< Node > children = node.children();
    list< Node >::iterator it = children.begin();
    for (; it != children.end(); ++it)
    {
        xml_node newNode = appendNode(*it, xnode);
        
        if (!it->children().empty())
        {
            Logger::entry("info") << "Node " << it->name() << " has children. Appending to the children...";
            buildXml(*it, newNode);
        } 
        else 
        {
            Logger::entry("info") << "Node " << it->name() << " has no children! Boooo!";
        }
    }
    
}

xml_node ModelToXmlConverter::appendNode(const Node& node, xml_node& xnode)
{
    Logger::entry("info") << "Appending child " << node.name();
    xml_node newNode = xnode.append_child(node.name().c_str());
    if (node.hasValue())
    {
        newNode.append_child(node_pcdata).set_value(node.value().c_str());
    }
    if (newNode.empty())
    {
        Logger::entry("info") << "Error when adding new xml node " << node.name() << ". Skipping node.";
        return newNode;
    }
    list< Attribute > attributes = node.attributes();
    list< Attribute >::iterator attrIt = attributes.begin();
    for (; attrIt != attributes.end(); ++attrIt)
    {
        xml_attribute attr = newNode.append_attribute(attrIt->name().c_str());
        if (attr.empty())
        {
            Logger::entry("info") << "Error when adding new attribute " << attrIt->name() << " to node " << node.name() << ". Skipping attribute.";
            continue;
        }
        attr.set_value(attrIt->value().c_str());
    }
    return newNode;
}
