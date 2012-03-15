
#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>

#include "vanetextensionform.h"

using namespace Wt;

VanetExtensionForm::VanetExtensionForm(Wt::WStandardItemModel* model, Wt::WContainerWidget* parent):
    model_(model),
    comboLabel_(tr("vanet.property.form.extension.combo.label").toUTF8())
{
    WTable* formTable = new WTable(this);
    int row = 0;
    
    WLabel* extLabel = new WLabel(formTable->elementAt(row, 0));
    extLabel->setText(WString::fromUTF8(comboLabel_));

    extensionComboBox_ = new WComboBox(formTable->elementAt(row, 1));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.glomosimoutput"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.timesimulation"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.spatialmodel"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.trafficlights"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.smdump"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.mobilitytrace"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.gdfwriter"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.gdfreader"));
    extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.tigerreader"));

    extensionComboBox_->activated().connect(this, &VanetExtensionForm::comboChanged);

    ++row;
    formTabel->elementAt(row, 0)->setColumnSpan(2);
    extensionFormContainer_ = new WContainerWidget(formTable->elementAt(row, 0));
}


void VanetExtensionForm::setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values)
{

}

std::vector< std::string, std::allocator< std::string > > VanetExtensionForm::feedbackMessages()
{

}

bool VanetExtensionForm::validate()
{

}

Wt::WStandardItem* VanetExtensionForm::treeNode()
{

}

