#include <map>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WTableView>
#include <Wt/WPushButton>

#include "configurationdialog.h"
#include <client/widgets/mappropertyeditor.h>
#include "server/database/persistencemanager.h"
#include <logger.h>

using namespace Wt;
using namespace std;

ConfigurationDialog::ConfigurationDialog(MapPropertyEditor* mapEditor) : WDialog()
{
    currentMpe_ = mapEditor;
    WTable* t = new WTable(this->contents());
    int row = 0;
    
    ++row;
    configList_ = new WTableView(t->elementAt(row, 0));
    configList_->setSelectionBehavior(SelectRows);
    configList_->setSelectionMode(SingleSelection);
    configList_->setRowHeight(25);
    configList_->setModel(PersistenceManager::instance()->allConfigurations());
    configList_->setColumnWidth(0, WLength(185));
    configList_->setColumnAlignment(0, AlignLeft);
    configList_->setColumnWidth(1, WLength(185));
    configList_->setColumnAlignment(1, AlignLeft);
    configList_->setColumnHidden(2, true);
    configList_->setColumnHidden(3, true);
    configList_->setAlternatingRowColors(true);
    configList_->setMaximumSize(390, 180);
    configList_->setHeight(130);
    configList_->setWidth(385);
    
    configList_->clicked().connect(this, &ConfigurationDialog::itemClicked);
    configList_->doubleClicked().connect(this, &WDialog::accept);
   
    ++row;
    WTable* buttonTable = new WTable(t->elementAt(row, 0));
    buttonTable->resize(380, WLength::Auto);
    buttonTable->elementAt(0, 0)->setContentAlignment(AlignRight);
    buttonTable->elementAt(0, 0)->setColumnSpan(2);
    buttonTable->elementAt(0, 0)->setPadding(10);
    removeButton_ = new WPushButton(tr("vanet.configuration.dialog.removebutton"), buttonTable->elementAt(0, 0));
    removeButton_->setDisabled(true);
    removeButton_->clicked().connect(this, &ConfigurationDialog::removeClicked);
    removeButton_->resize(150, 20);
    
    buttonTable->elementAt(1, 0)->setContentAlignment(AlignCenter);
    okButton_ = new WPushButton(tr("button.ok"), buttonTable->elementAt(1, 0));
    okButton_->setDisabled(true);
    okButton_->clicked().connect(this, &WDialog::accept);
    okButton_->resize(115, 25);
    
    buttonTable->elementAt(1, 1)->setContentAlignment(AlignCenter);
    WPushButton* cancelButton = new WPushButton(tr("button.cancel"), buttonTable->elementAt(1, 1));
    cancelButton->clicked().connect(this, &WDialog::reject);
    cancelButton->resize(115, 25);
    
    finished().connect(this, &ConfigurationDialog::submit);
    
    setTitleBarEnabled(true);
    setClosable(true);
    setWindowTitle(tr("vanet.configuration.dialog.title"));
    
    selectedConfig_ = 0;
    resize(WLength::Auto, WLength::Auto);
}

void ConfigurationDialog::itemClicked(const WModelIndex& clickedItem)
{
    okButton_->setDisabled(false);
    removeButton_->setDisabled(false);
    boost::any data = configList_->model()->data(clickedItem.row(), 2);
    selectedConfig_ = boost::any_cast<long long>(data);
    Logger::entry("info") << "Clicked item id: " << selectedConfig_;
}

void ConfigurationDialog::removeClicked()
{
    if (selectedConfig_ != 0) 
    {
        PersistenceManager::instance()->deleteConfiguration(selectedConfig_);
        configList_->setModel(PersistenceManager::instance()->allConfigurations());
    }
}

void ConfigurationDialog::submit(WDialog::DialogCode result)
{
    if (result == WDialog::Accepted) 
    {
        currentMpe_->setModel(PersistenceManager::instance()->allEntries(selectedConfig_));
    }
}

long long int ConfigurationDialog::selectedConfig()
{
    return selectedConfig_;
}

