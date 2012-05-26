#include <Wt/WTable>
#include <Wt/WTableView>
#include <Wt/WPushButton>

#include "configurationdialog.h"
#include "server/database/persistencemanager.h"

using namespace Wt;
using namespace std;

ConfigurationDialog::ConfigurationDialog()
{
    resize(WLength::Auto, WLength::Auto);
    WTable* t = new WTable(this->contents());
    int row = 0;
    
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
    configList_->setMaximumSize(370, 300);
    
    configList_->clicked().connect(this, &ConfigurationDialog::itemClicked);
    configList_->doubleClicked().connect(this, &WDialog::accept);
    
    ++row;
    WTable* buttonTable = new WTable(t->elementAt(row, 0));
    buttonTable->elementAt(0, 0)->setContentAlignment(AlignRight);
    buttonTable->elementAt(0, 0)->setColumnSpan(2);
    removeConfig_ = new WPushButton(tr("vanet.configuration.dialog.removebutton"), buttonTable->elementAt(0, 0));
    removeConfig_->setDisabled(true);
    removeConfig_->clicked().connect(this, &ConfigurationDialog::removeClicked);
    removeConfig_->resize(115, 25);
    
    buttonTable->elementAt(1, 0)->setContentAlignment(AlignCenter);
    okButton_ = new WPushButton(tr("button.ok"), buttonTable->elementAt(1, 0));
    okButton_->setDisabled(true);
    okButton_->clicked().connect(this, &WDialog::accept);
    okButton_->resize(115, 25);
    
    buttonTable->elementAt(1, 1)->setContentAlignment(AlignCenter);
    WPushButton* cancelButton = new WPushButton(tr("button.cancel"), buttonTable->elementAt(1, 1));
    cancelButton->setDisabled(true);
    cancelButton->clicked().connect(this, &WDialog::reject);
    
    
    setTitleBarEnabled(true);
    setClosable(true);
    setWindowTitle(tr("vanet.configuration.dialog.title"));
    
    selectedConfig_ = 0;
}
