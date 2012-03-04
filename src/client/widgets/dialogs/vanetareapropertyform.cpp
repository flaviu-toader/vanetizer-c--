
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <Wt/WStandardItem>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WStandardItemModel>
#include <Wt/WCssDecorationStyle>
#include <Wt/WDialog>

#include "vanetareapropertyform.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace Wt;

VanetAreaPropertyForm::VanetAreaPropertyForm(WStandardItemModel *model, WContainerWidget* parent): 
    model(model),
    fWidth(350), 
    fHeight(300),
    dimxLabel(tr("mappropertyeditor.group.general.dimx").toUTF8()),
    dimyLabel(tr("mappropertyeditor.group.general.dimy").toUTF8())
{
    WTable *formTable = new WTable(this);
    int row = 0;

    ++row;
    WLabel *xLabel = new WLabel(formTable->elementAt(row, 0));
    xLabel->setText(WString::fromUTF8(dimxLabel));
    dimx = new WSpinBox(formTable->elementAt(row, 1));
    dimx->setMinimum(0);
    dimx->setMaximum(90000);
    xLabel->setBuddy(dimx);

    ++row;
    WLabel *yLabel = new WLabel(formTable->elementAt(row, 0));
    yLabel->setText(WString::fromUTF8(dimyLabel));
    dimy = new WSpinBox(formTable->elementAt(row, 1));
    dimy->setMinimum(0);
    dimy->setMaximum(90000);
    yLabel->setBuddy(dimy);

}

WLength VanetAreaPropertyForm::formWidth() 
{
    return fWidth;
}

WLength VanetAreaPropertyForm::formHeight() 
{
    return fHeight;
}

bool VanetAreaPropertyForm::validate()
{
    bool valid = true;
    if (dimx->value() < 100 || dimy->value() < 100) 
    {
        messages.push_back(tr("vanet.property.form.area.error.dims").toUTF8());
        valid = false;
    }
    return valid;
}

std::vector<std::string> VanetAreaPropertyForm::feedbackMessages() 
{
    return messages;
}

WStandardItem *VanetAreaPropertyForm::treeNode() 
{
    WStandardItem *result = new WStandardItem(tr("mappropertyeditor.group.general").toUTF8());

    result->appendRow(propertyRow(std::string("dimx"), tr("mappropertyeditor.group.general.dimx").toUTF8(), boost::lexical_cast<std::string>(dimx->value())));
    result->appendRow(propertyRow(std::string("dimy"), tr("mappropertyeditor.group.general.dimy").toUTF8(), boost::lexical_cast<std::string>(dimy->value())));

    return result;
}

std::vector<WStandardItem *> VanetAreaPropertyForm::propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue)
{
    std::vector<WStandardItem *> propertyItems;
    WStandardItem *item;

    // tree column 0: property name
    item = new WStandardItem(propertyName);
    propertyItems.push_back(item);

    // tree column 1: property value
    item = new WStandardItem(propertyValue);
    propertyItems.push_back(item);
    
    // tree column 2: property id (hidden column)
    item = new WStandardItem(propertyId);
    propertyItems.push_back(item);

    return propertyItems;
}
