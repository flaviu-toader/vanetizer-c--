
#include <vector>
#include <utility>
#include <string>
#include <numeric>
#include <map>
#include <iostream>
#include <boost/cast.hpp>
#include <boost/assign.hpp>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WComboBox>
#include <Wt/WDialog>
#include <Wt/WTable>
#include <Wt/WComboBox>
#include <Wt/WPushButton>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WMessageBox>

#include "propertydialog.h"
#include "client/widgets/dialogs/vanetareapropertyform.h"
#include "client/widgets/dialogs/vanetsteppropertyform.h"
#include "client/widgets/dialogs/vanetseedpropertyform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

PropertyDialog::PropertyDialog(WStandardItemModel *model) :
    model_(model)
{   
    WTable *table = new WTable(this->contents());
    int row = 0;

    mainComboBox_ = new WComboBox(table->elementAt(row, 0));
    mainComboBox_->addItem(tr("constant.none"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.area"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.step"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.seed"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.extension"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.node"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.nodegroup"));
    
    mainComboBox_->activated().connect(this, &PropertyDialog::comboChanged);
    
    ++row;
    formContainer_ = new WContainerWidget(table->elementAt(row, 0));

    ++row;
    table->elementAt(row, 0)->setContentAlignment(AlignCenter);
    WPushButton *b;
    WContainerWidget *buttons = new WContainerWidget(table->elementAt(row, 0));
    buttons->addWidget(b = new WPushButton(tr("button.save")));
    b->clicked().connect(this, &WDialog::accept);
    contents()->enterPressed().connect(this, &WDialog::accept);
    buttons->addWidget(b = new WPushButton(tr("button.cancel")));
    b->clicked().connect(this, &WDialog::reject);

    finished().connect(this, &PropertyDialog::submit);

    preselectedItem_ = 0;
}

void PropertyDialog::setPreselectedProperty(WStandardItem *rootItem)
{
    VanetProperty currentIndex = boost::any_cast<VanetProperty>(rootItem->data());
    mainComboBox_->setCurrentIndex(currentIndex);
    preselectedItem_ = rootItem;
    comboChanged(currentIndex);
}


void PropertyDialog::submit(DialogCode result)
{
    if (result == WDialog::Accepted)
    {
        AbstractPropertyForm *form = dynamic_cast<AbstractPropertyForm *>(formContainer_->children().at(0));
        vector<string> messages;
        if (!form->validate())
        {
            messages = form->feedbackMessages();
            WMessageBox::show(tr("application.error"), accumulate(messages.begin(), messages.end(), string("")), Ok);
            delete this;
            return;
        }
        WStandardItem *newItem = form->treeNode();
        // check if we are dealing really with a new item
        if(itemIsNew(newItem) && preselectedItem_ == 0)
        {
            model_->appendRow(newItem);
        } 
        else
        {
            // in case we are editing an existing item, replace it in the model
            if (preselectedItem_ != 0)
            {
                // this code segfaults for some reason when the updated item is not the last one...
//                 int oldRow = model_->indexFromItem(preselectedItem_).row();
//                 Logger::entry("info") << "Double clicked item is at " << oldRow;
//                 model_->removeRows(oldRow, 1, model_->indexFromItem(preselectedItem_->parent()));
//                 model_->insertRow(oldRow, newItem);
                WModelIndex ix = model_->indexFromItem(preselectedItem_);
                model_->itemFromIndex(ix)->removeRows(0, preselectedItem_->rowCount());
                for (int i = 0; i < newItem->rowCount(); i++) 
                {
                    std::vector<WStandardItem *> row;
                    for (int j = 0; j < newItem->columnCount(); j++) 
                    {
                        row.push_back(newItem->child(i, j));
                    }
                    model_->itemFromIndex(ix)->appendRow(row);;
                }
            } 
            else 
            {
                WString msg = tr("propertydialog.error.propertyexists");
                messages.push_back(msg.arg(newItem->text()).toUTF8());
            }
        }
        if (!messages.empty()) 
        {
            WMessageBox::show(tr("application.error"), accumulate(messages.begin(), messages.end(), string("")), Ok);
        }
    }
    delete this;
}

//! Performs a check on the each node of the treenode if it has the same data as another item in the tree. The data 
bool PropertyDialog::itemIsNew(WStandardItem *item)
{
    // if preselectedItem is not null, it means we are editing an existing property
    if (preselectedItem_ != 0)
    {
        return true;
    }
    VanetProperty itemProp = boost::any_cast<VanetProperty>(item->data());
    for (int i = 0; i < model_->rowCount(); i++) 
    {
        VanetProperty currentProp = boost::any_cast<VanetProperty>(model_->item(i)->data());
        if (currentProp == itemProp)
        {
            return false;
        }
    }
    return true;
}


void PropertyDialog::comboChanged(int itemIndex)
{
    Logger::entry("info") << "itemIndex = " << itemIndex;
    AbstractPropertyForm *form;
    switch (itemIndex)
    {
        case 1:
            formContainer_->clear();
            form = new VanetAreaPropertyForm(model_, formContainer_);
            if (preselectedItem_ != 0) 
            {
//                 WModelIndex ix = model_->indexFromItem(preselectedItem_);
                vector<boost::any> values;
                Logger::entry("info") << "Adding preselected value for X: " << preselectedItem_->child(0, 1)->text();
                Logger::entry("info") << "Adding preselected value for Y: " << preselectedItem_->child(1, 1)->text();
                values.push_back(boost::lexical_cast<int>(preselectedItem_->child(0, 1)->text()));
                values.push_back(boost::lexical_cast<int>(preselectedItem_->child(1, 1)->text()));
                form->setPreselectedValues(values);
            }
            formContainer_->addWidget(form);
            break;
        case 2:
            formContainer_->clear();
            form = new VanetStepPropertyForm(model_, formContainer_);
            if (preselectedItem_ != 0) 
            {
//                 WModelIndex ix = model_->indexFromItem(preselectedItem_);
                WString preselectedValue = preselectedItem_->child(0, 1)->text();
                vector<boost::any> values;
                Logger::entry("info") << "Adding preselected step value: " << preselectedValue;
                stringstream ss(preselectedValue.toUTF8());
                double val;
                ss.precision(3);
                ss >> fixed >> val;
                values.push_back(val);
                form->setPreselectedValues(values);
            }
            formContainer_->addWidget(form);
            break;
        case 3:
            formContainer_->clear();
            form = new VanetSeedPropertyForm(model_, formContainer_);
            if (preselectedItem_ != 0)
            {
//                 WModelIndex ix = model_->indexFromItem(preselectedItem_);
                WString preselectedValue = preselectedItem_->child(0, 1)->text();
                vector<boost::any> values;
                Logger::entry("info") << "Adding preselected seed value: " << preselectedValue;
                values.push_back(preselectedValue);
                form->setPreselectedValues(values);
            }
            formContainer_->addWidget(form);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            // cases from 6 to 14 are only one item in the mainComboBox_: Vanet Extension.
            break;
        default:
            formContainer_->clear();
    }
}
