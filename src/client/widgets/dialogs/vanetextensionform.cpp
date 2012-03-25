
#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>

#include "vanetextensionform.h"

using namespace Wt;

VanetExtensionForm::VanetExtensionForm(Wt::WContainerWidget* parent)
{
    WTable* formTable = new WTable(this);
    int row = 0;
    
    WLabel* extLabel = new WLabel(formTable->elementAt(row, 0));
    extLabel->setText(WString::fromUTF8(tr("vanet.property.form.extension.combo.label").toUTF8()));

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
    extLabel->setBuddy(extensionComboBox_);

    ++row;
    formTable->elementAt(row, 0)->setColumnSpan(2);
    extensionFormContainer_ = new WContainerWidget(formTable->elementAt(row, 0));
}


void VanetExtensionForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{

}

bool VanetExtensionForm::validate()
{

}

Wt::WStandardItem* VanetExtensionForm::treeNode()
{

}

void VanetExtensionForm::comboChanged(int itemIndex)
{

}
