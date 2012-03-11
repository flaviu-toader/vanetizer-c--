
#include <iostream>
#include <map>
#include <boost/assign.hpp>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WTreeView>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WPanel>
#include <Wt/WFlags>
#include <Wt/WModelIndex>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WPushButton>
#include <Wt/WTable>

#include "mappropertyeditor.h"
#include "logger.h"
#include "client/widgets/dialogs/propertydialog.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace Wt;

MapPropertyEditor::MapPropertyEditor(WStandardItemModel *model) : model(model)
{    
    WTable *mainTable = new WTable(this);
    new WText(tr("mappropertyeditor.title"), mainTable->elementAt(0,0));

    // create the view.
    WPanel *panel = new WPanel(mainTable->elementAt(1,0));
    //panel->resize(WLength::Auto, WLength::Auto);
    panel->resize(600, 335);
    panel->setCentralWidget(treeView = new WTreeView());

    if(!WApplication::instance()->environment().ajax()) 
    {
        treeView->resize(WLength::Auto, 380);
    }

    treeView->setAlternatingRowColors(true);
    treeView->setRowHeight(25);
    treeView->setModel(model);
    treeView->setColumnWidth(0, WLength(285));
    treeView->setColumnAlignment(0, AlignLeft);
    treeView->setColumnWidth(1, WLength(285));
    treeView->setColumnAlignment(1, AlignLeft);
    treeView->setColumnHidden(2, true);
    treeView->setSortingEnabled(false);

    treeView->setExpanded(model->index(0, 0), true);
    treeView->setExpanded(model->index(0, 0, model->index(0, 0)), true);
    
    treeView->doubleClicked().connect(this, &MapPropertyEditor::itemDoubleClicked);

    WTable *buttonTable = new WTable(mainTable->elementAt(2, 0));
    mainTable->elementAt(2, 0)->setContentAlignment(AlignCenter);

    WPushButton *addProperty = new WPushButton(tr("mappropertyeditor.button.addproperty"), buttonTable->elementAt(0, 0));
    addProperty->resize(120, 30);
    addProperty->clicked().connect(this, &MapPropertyEditor::showPropertyDialog);

    WPushButton *removeProperty = new WPushButton(tr("mappropertyeditor.button.removeproperty"), buttonTable->elementAt(0, 1));
    removeProperty->resize(120, 30);

    WPushButton *validate = new WPushButton(tr("mappropertyeditor.button.validate"), buttonTable->elementAt(0, 2));
    validate->resize(120, 30);

}

void MapPropertyEditor::showPropertyDialog()
{
    pd = new PropertyDialog(model);
    pd->show();
}


WStandardItemModel* MapPropertyEditor::createModel(WObject *parent) 
{
    WStandardItemModel *result = new WStandardItemModel(0, 2, parent);

    result->setHeaderData(0, Horizontal, tr("mappropertyeditor.header.propertyname").toUTF8());
    result->setHeaderData(1, Horizontal, tr("mappropertyeditor.header.propertyvalue").toUTF8());

    return result;
}

WStandardItem *MapPropertyEditor::groupItem(const std::string& groupName)
{
    WStandardItem *result = new WStandardItem(groupName);
    result->setColumnCount(2);
    return result;
}

std::vector<WStandardItem *> MapPropertyEditor::propertyItem(const std::string& name, const boost::any& data)
{
    std::vector<WStandardItem *> result;
    WStandardItem *item;

    item = new WStandardItem(name);
    result.push_back(item);

    item = new WStandardItem;
    item->setData(data, DisplayRole);
    result.push_back(item);

    return result;
}

void MapPropertyEditor::itemDoubleClicked(const WModelIndex& clickedItem)
{
    if (clickedItem.parent() == treeView->rootIndex()) 
    {
        WStandardItem *item = model->item(clickedItem.row(), clickedItem.column());
        pd = new PropertyDialog(model);
        pd->setPreselectedProperty(item);
        pd->show();
    }
}


