
#include <vector>
#include <utility>
#include <string>
#include <numeric>
#include <boost/cast.hpp>

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

using namespace Wt;
using namespace std;

PropertyDialog::PropertyDialog(WStandardItemModel *model) :
    model(model)
{   
    WTable *table = new WTable(this->contents());
    int row = 0;

    mainComboBox = new WComboBox(table->elementAt(row, 0));
    mainComboBox->addItem(tr("constant.none"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.area"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.step"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.seed"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.extension"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.node"));
    mainComboBox->addItem(tr("propertydialog.vanet.combobox.nodegroup"));
    
    mainComboBox->activated().connect(this, &PropertyDialog::comboChanged);
    
    ++row;
    formContainer = new WContainerWidget(table->elementAt(row, 0));

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

    show();
}

void PropertyDialog::submit(DialogCode result)
{
    if (result == WDialog::Accepted)
    {
        AbstractPropertyForm *form = dynamic_cast<AbstractPropertyForm *>(formContainer->children().at(0));
        vector<string> messages;
        if (!form->validate())
        {
            messages = form->feedbackMessages();
            WMessageBox::show(tr("application.error"), accumulate(messages.begin(), messages.end(), string("")), Ok);
            delete this;
            return;
        }
        WStandardItem *newItem = form->treeNode();
        if(itemIsNew(newItem))
        {
            model->appendRow(newItem);
        } 
        else
        {
            WString msg = tr("propertydialog.error.propertyexists");
            messages.push_back(msg.arg(newItem->text()).toUTF8());
        }
        if (!messages.empty()) 
        {
            WMessageBox::show(tr("application.error"), accumulate(messages.begin(), messages.end(), string("")), Ok);
        }
    }
    delete this;
}

//! Performs a check on the root node of the treenode if it has the same string as another item in the tree.
bool PropertyDialog::itemIsNew(WStandardItem *item)
{
    for (int i = 0; i < model->rowCount(); i++) 
    {
        if (model->item(i)->text() == item->text())
        {
            return false;
        }
    }
    return true;
}


void PropertyDialog::comboChanged(int itemIndex)
{
    switch (itemIndex)
    {
        case 1:
            formContainer->addWidget(new VanetAreaPropertyForm(model, formContainer));
            break;
        default:
            formContainer->clear();
    }
}
