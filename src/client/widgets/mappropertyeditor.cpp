
#include <iostream>
#include <map>
#include <set>
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
#include <Wt/WAbstractItemView>

#include "mappropertyeditor.h"
#include "logger.h"
#include "client/mapmakerpage.h"
#include "client/widgets/dialogs/propertydialog.h"
#include "client/widgets/dialogs/abstractpropertyform.h"
#include "xml/modeltoxmlconverter.h"

using namespace Wt;

MapPropertyEditor::MapPropertyEditor(MapMakerPage* mapmaker, WStandardItemModel *model) : 
    model_(model),
    mapmaker_(mapmaker),
    root_(Node("universe"))
{
    selectedItem_ = 0;
    WTable *mainTable = new WTable(this);
    new WText(tr("mappropertyeditor.title"), mainTable->elementAt(0,0));

    // create the view.
    WPanel *panel = new WPanel(mainTable->elementAt(1,0));
    //panel->resize(WLength::Auto, WLength::Auto);
    panel->resize(600, 335);
    panel->setCentralWidget(treeView_ = new WTreeView());

    if(!WApplication::instance()->environment().ajax()) 
    {
        treeView_->resize(WLength::Auto, 380);
    }

    treeView_->setAlternatingRowColors(true);
    treeView_->setRowHeight(25);
    treeView_->setModel(model);
    treeView_->setColumnWidth(0, WLength(285));
    treeView_->setColumnAlignment(0, AlignLeft);
    treeView_->setColumnWidth(1, WLength(285));
    treeView_->setColumnAlignment(1, AlignLeft);
    treeView_->setColumnHidden(2, true);
    treeView_->setSortingEnabled(false);
    treeView_->setSelectionMode(SingleSelection);
    treeView_->setSelectable(true);
    treeView_->setSelectionBehavior(SelectRows);

    treeView_->setExpanded(model->index(0, 0), true);
    treeView_->setExpanded(model->index(0, 0, model->index(0, 0)), true);
    
    treeView_->doubleClicked().connect(this, &MapPropertyEditor::itemDoubleClicked);
    treeView_->clicked().connect(this, &MapPropertyEditor::itemClicked);

    WTable *buttonTable = new WTable(mainTable->elementAt(2, 0));
    mainTable->elementAt(2, 0)->setContentAlignment(AlignCenter);

    addProperty_ = new WPushButton(tr("mappropertyeditor.button.addproperty"), buttonTable->elementAt(0, 0));
    addProperty_->resize(120, 30);
    addProperty_->clicked().connect(this, &MapPropertyEditor::showPropertyDialog);

    removeProperty_ = new WPushButton(tr("mappropertyeditor.button.removeproperty"), buttonTable->elementAt(0, 1));
    removeProperty_->resize(120, 30);
    removeProperty_->setDisabled(true);
    removeProperty_->clicked().connect(this, &MapPropertyEditor::removeSelectedProperty);

    validate_ = new WPushButton(tr("mappropertyeditor.button.validate"), buttonTable->elementAt(0, 2));
    validate_->resize(120, 30);
    validate_->clicked().connect(this, &MapPropertyEditor::validateClicked);
    
    save_ = new WPushButton(tr("button.save"), buttonTable->elementAt(0, 3));
    save_->resize(120, 30);
    save_->setDisabled(true);
}

void MapPropertyEditor::removeSelectedProperty()
{
    if (selectedItem_ != 0) 
    {
        WModelIndex ix = model_->indexFromItem(selectedItem_);
        if (ix.parent() == treeView_->rootIndex()) 
        {
            model_->itemFromIndex(ix)->removeRows(0, selectedItem_->rowCount());
            model_->removeRow(ix.row());
        }
    }
}

void MapPropertyEditor::showPropertyDialog()
{
    pd_ = new PropertyDialog(model_, root_);
    pd_->show();
}


WStandardItemModel* MapPropertyEditor::createModel(WObject *parent) 
{
    WStandardItemModel *result = new WStandardItemModel(0, 2, parent);

    result->setHeaderData(0, Horizontal, tr("mappropertyeditor.header.propertyname").toUTF8());
    result->setHeaderData(1, Horizontal, tr("mappropertyeditor.header.propertyvalue").toUTF8());

    return result;
}

void MapPropertyEditor::itemDoubleClicked(const WModelIndex& clickedItem)
{
    if (clickedItem.parent() == treeView_->rootIndex()) 
    {
        WStandardItem *item = model_->item(clickedItem.row(), clickedItem.column());
        pd_ = new PropertyDialog(model_, root_);
        pd_->setPreselectedProperty(item);
        pd_->show();
    }
}

void MapPropertyEditor::itemClicked(const WModelIndex& clickedItem)
{
    if (clickedItem.parent() == treeView_->rootIndex())
    {
        selectedItem_ = model_->item(clickedItem.row(), clickedItem.column());
        removeProperty_->setDisabled(false);
    }
    else
    {
        removeProperty_->setDisabled(true);
    }
}

void MapPropertyEditor::validateClicked()
{
    ModelToXmlConverter modelToXml(root_);
    modelToXml.convertXml();
}
