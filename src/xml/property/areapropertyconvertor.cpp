#include <vector>
#include <string>
#include <pugixml/pugixml.hpp>

#include <Wt/WStandardItem>
#include <Wt/WString>

#include "areapropertyconvertor.h"
#include "abstractpropertyconvertor.h"
#include "logger.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace std;
using namespace Wt;

const char* const AreaPropertyConvertor::TREENODE_NAME = tr("mappropertyeditor.group.general").toUTF8().c_str();

vector< pugi::xml_node > toXml(WStandardItem* treeNode)
{
    // check if we're looking at the right node...
    if (treeNode->data() == VanetArea) 
    {
        for (int i = 0; i < treeNode->rowCount(); i++)
        {
        }
    }
}

