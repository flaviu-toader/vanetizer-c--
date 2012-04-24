#include <string>
#include <map>
#include <pugixml/pugixml.hpp>

#include <Wt/WStandardItem>
#include <Wt/WString>

#include "gmsoutpropertyconvertor.h"
#include "abstractpropertyconvertor.h"
#include "logger.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace Wt;
using namespace std;

const char* const GmsOutPropertyConvertor::TREENODE_NAME = "mappropertyeditor.group.gmsout";

Wt::WStandardItem* GmsOutPropertyConvertor::treeNode(const pugi::xml_node& root)
{
    WStandardItem* result = new WStandardItem(WString::tr(TREENODE_NAME));
    map< string, string > values;
    for(pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
    {
        string currentName = it->name();
        
    }
}

void GmsOutPropertyConvertor::appendXml(pugi::xml_node& root, Wt::WStandardItem* treeNode)
{

}

