#include <string>
#include <pugixml/pugixml.hpp>

#include <Wt/WStandardItem>
#include <Wt/WString>
#include <boost/concept_check.hpp>

#include "areapropertyconvertor.h"
#include "abstractpropertyconvertor.h"
#include "logger.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace std;
using namespace Wt;

const char* const AreaPropertyConvertor::TREENODE_NAME = "mappropertyeditor.group.general";

void AreaPropertyConvertor::appendXml(pugi::xml_node& root, WStandardItem* treeNode)
{
    // check if we're looking at the right node...
    if (boost::any_cast<VanetProperty>(treeNode->data()) == VanetArea) 
    {
        for (int i = 0; i < treeNode->rowCount(); i++)
        {
            // for the area property we currently have only 2 possible nodes: dimx and dimy
            string nodename = treeNode->child(i, 2)->text().toUTF8();
            string nodevalue = treeNode->child(i, 1)->text().toUTF8();
            
            pugi::xml_node newNode = root.append_child(nodename.c_str());
            newNode.append_child(pugi::node_pcdata).set_value(nodevalue.c_str());
        }
    }
}

WStandardItem* AreaPropertyConvertor::treeNode(const pugi::xml_node& root)
{
    WStandardItem* result = new WStandardItem(WString::tr(TREENODE_NAME));
    
    string dimxval;
    string dimyval;
    for(pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
    {
        pugi::xml_node currentNode = *it;
        if (currentNode.name() == "dimx") 
        {
            dimxval = string(currentNode.value());
            continue;
        }
        if (currentNode.name() == "dimy")
        {
            dimyval = string(currentNode.value());
            continue;
        }
        if (!dimxval.empty() && !dimyval.empty())
            break;
    }
    if (!dimxval.empty())
        result->appendRow(propertyRow("dimx", WString::tr("mappropertyeditor.group.general.dimx").toUTF8(), dimxval));
    if (!dimyval.empty())
        result->appendRow(propertyRow("dimy", WString::tr("mappropertyeditor.group.general.dimy").toUTF8(), dimyval));
    
    return result;
}

