
#include <iostream>
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

#include "mappropertyeditor.h"
#include "logger.h"

using namespace Wt;

MapPropertyEditor::MapPropertyEditor(WStandardItemModel *model) : model(model)
{
    new WText(tr("mappropertyeditor.title"), this);

    // create the view.
    WPanel *panel = new WPanel(this);
    //panel->resize(WLength::Auto, WLength::Auto);
    panel->resize(600, 400);
    panel->setCentralWidget(treeView = new WTreeView());

    if(!WApplication::instance()->environment().ajax()) 
    {
        treeView->resize(WLength::Auto, 380);
    }

    treeView->setAlternatingRowColors(true);
    treeView->setRowHeight(25);
    treeView->setModel(model);
    treeView->setColumnWidth(0, WLength(285));
    treeView->setColumnAlignment(0, AlignCenter);
    treeView->setColumnWidth(1, WLength(285));
    treeView->setColumnAlignment(1, AlignCenter);

    treeView->setExpanded(model->index(0, 0), true);
    treeView->setExpanded(model->index(0, 0, model->index(0, 0)), true);
}

WStandardItemModel* MapPropertyEditor::createModel(WObject *parent) 
{
    WStandardItemModel *result = new WStandardItemModel(0, 2, parent);

    result->setHeaderData(0, Horizontal, tr("mappropertyeditor.header.propertyname").toUTF8());
    result->setHeaderData(1, Horizontal, tr("mappropertyeditor.header.propertyvalue").toUTF8());

    result->appendRow(groupItem(tr("mappropertyeditor.group.general").toUTF8()));
    result->appendRow(propertyItem(tr("mappropertyeditor.group.general.dimx").toUTF8(), 0, EditRole));
    result->appendRow(propertyItem(tr("mappropertyeditor.group.general.dimy").toUTF8(), 0, EditRole));

    return result;
}

WStandardItem *MapPropertyEditor::groupItem(const std::string& groupName)
{
    WStandardItem *result = new WStandardItem(groupName);
    result->setColumnCount(2);
    return result;
}

std::vector<WStandardItem *> MapPropertyEditor::propertyItem(const std::string& name, const boost::any& data, int role)
{
    std::vector<WStandardItem *> result;
    WStandardItem *item;

    item = new WStandardItem(name);
    result.push_back(item);

    item = new WStandardItem;
    item->setData(data, role);
    item->setFlags(WFlags<ItemFlag>(ItemIsEditable));
    item->set
    result.push_back(item);

    return result;
}

