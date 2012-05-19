
#include <vector>
#include <list>
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
#include "client/widgets/dialogs/vanetextensionform.h"
#include "client/widgets/dialogs/vanetnodegroupform.h"
#include "client/widgets/dialogs/vanetnodeform.h"
#include "client/widgets/dialogs/vanetroutingprotocolpropertyform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

PropertyDialog::PropertyDialog(WStandardItemModel *model, Node& root) :
    model_(model)
{
    root_ = &root;
    WTable *table = new WTable(this->contents());
    int row = 0;

    mainComboBox_ = new WComboBox(table->elementAt(row, 0));
    mainComboBox_->addItem(tr("constant.none"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.area"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.step"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.seed"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.node"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.nodegroup"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.glomosim"));
    mainComboBox_->addItem(tr("propertydialog.vanet.combobox.extension"));

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
    
    setClosable(true);
    setTitleBarEnabled(true);
    setWindowTitle(tr("mappropertyeditor.title"));

    preselectedItem_ = 0;
}

void PropertyDialog::setPreselectedProperty(WStandardItem *rootItem)
{
    VanetProperty currentIndex = boost::any_cast<VanetProperty>(rootItem->data());
    if ((int) currentIndex > 7)
    {
        currentIndex = VanetGlomosimOutput;
    }
    mainComboBox_->setCurrentIndex(currentIndex);
    mainComboBox_->setDisabled(true);
    preselectedItem_ = rootItem;
    comboChanged(currentIndex);
}


void PropertyDialog::submit(DialogCode result)
{
    if (result == WDialog::Accepted)
    {
        AbstractPropertyForm *form = dynamic_cast<AbstractPropertyForm *>(formContainer_->children().at(0));
        vector<string> messages;
        if (!form->validate(messages))
        {
            WMessageBox::show(tr("application.error"), accumulate(messages.begin(), messages.end(), string("")), Ok);
            show();
            return;
        }
        list< Node > nodes;
        WStandardItem *newItem = form->treeNode(nodes);
        // check if we are dealing really with a new item
        if(itemIsNew(newItem) && preselectedItem_ == 0)
        {
            model_->appendRow(newItem);
            root_->addChildren(nodes);
        }
        else
        {
            // in case we are editing an existing item, replace it in the model
            if (preselectedItem_ != 0)
            {
                list< Node >::iterator it;
                for (int i = 0; i < preselectedItem_->rowCount(); i++)
                {
                    WStandardItem* currentItem = preselectedItem_->child(i, 2);
                    if (currentItem != 0) 
                    {
                        string currentName = currentItem->text().toUTF8();
                        if(currentName.find("=") == string::npos) 
                        {
                            it = root_->removeChild(currentName);
                        }
                    }
                }
                root_->addChildren(nodes, it);
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
        if (itemProp == VanetNodeGroup || 
            itemProp == VanetNode)
        {
            if (model_->item(i)->text() == item->text()) 
            {
                return false;
            }
            return true;
        }
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
    AbstractPropertyForm* form = 0;
    formContainer_->clear();
    switch (itemIndex)
    {
    case 1:
        form = new VanetAreaPropertyForm;
        break;
    case 2:
        form = new VanetStepPropertyForm;
        break;
    case 3:
        form = new VanetSeedPropertyForm;
        break;
    case 4:
        form = new VanetNodeForm;
        break;
    case 5:
        form = new VanetNodeGroupForm;
        break;
    case 6:
        form = new VanetRoutingProtocolPropertyForm;
        break;
    case 7:
        form = new VanetExtensionForm;
        break;
    default:
        formContainer_->clear();
    }

    if (preselectedItem_ != 0 && form != 0)
    {
        form->setPreselectedValues(getValuesMap());
    }
    
    if (form != 0)
    {
        formContainer_->addWidget(form);
    }
}

map< string, boost::any > PropertyDialog::getValuesMap()
{
    std::map< std::string, boost::any > values;
    Logger::entry("info") << "The row count of this preselected item is: " << preselectedItem_->rowCount();
    for (int row = 0; row < preselectedItem_->rowCount(); row++)
    {
        Logger::entry("info") << "Column count: " << preselectedItem_->child(row, 0)->columnCount();
        // for now we only support one possible level of subgroups
        if (preselectedItem_->child(row, 0)->columnCount() == 3) 
        {
            Logger::entry("info") << "Found a subgroup";
            WStandardItem* subgroup = preselectedItem_->child(row, 0);
            for (int r = 0; r < subgroup->rowCount(); r++)
            {
                WString k = subgroup->child(r, 2)->text();
                WString v = subgroup->child(r, 1)->text();
                values.insert(make_pair< string, boost::any >(k.toUTF8(), v.toUTF8()));
                Logger::entry("info") << "\tAdded preselected key for property: " << k << " and value: " << v;
            }
            continue;
        } 
        WString key = preselectedItem_->child(row, 2)->text();
        WString value = preselectedItem_->child(row, 1)->text();
        values.insert(std::make_pair< std::string, boost::any >(key.toUTF8(), value.toUTF8()));
        Logger::entry("info") << "Added preselected key for property: " << key << " and value: " << value;
    }

    return values;
}
