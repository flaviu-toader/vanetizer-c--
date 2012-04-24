#include <string>
#include <pugixml/pugixml.hpp>

#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>

#include "modeltoxmlconverter.h"
#include "logger.h"
#include "client/widgets/dialogs/abstractpropertyform.h"
#include "xml/property/abstractpropertyconvertor.h"
#include "xml/property/areapropertyconvertor.h"

using namespace Wt;
using namespace std;

ModelToXmlConverter::ModelToXmlConverter(WStandardItemModel* model) :
    model_(model)
{
    root_ = doc_.append_child("universe");
    convertXml();
}

void ModelToXmlConverter::convertXml()
{
    for (int i = 0; i < model_->rowCount(); i++)
    {
        WStandardItem* currentItem = model_->item(i);
        int itemType = currentItem->data();
        AbstractPropertyConvertor* convertor;
        switch(itemType)
        {
            case VanetArea:
                convertor = new AreaPropertyConvertor;
                break;
        }
        convertor->appendXml(root_, currentItem);
    }
}
