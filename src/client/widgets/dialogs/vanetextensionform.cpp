#include <boost/concept_check.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WStandardItem>

#include "vanetextensionform.h"
#include "logger.h"
#include "client/widgets/dialogs/vanetgmsoutpropertyform.h"
#include "client/widgets/dialogs/vanettimesimulationpropertyform.h"
#include "client/widgets/dialogs/vanetspatialmodelpropertyform.h"
#include "client/widgets/dialogs/vanettrafficlightpropertyform.h"
#include "client/widgets/dialogs/vanetspmodeldump.h"

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
    // These commented extensions are not yet implemented.
//     extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.mobilitytrace"));
//     extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.gdfwriter"));
//     extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.gdfreader"));
//     extensionComboBox_->addItem(tr("vanet.property.form.extension.combo.tigerreader"));

    extensionComboBox_->activated().connect(this, &VanetExtensionForm::extensionComboChanged);
    extLabel->setBuddy(extensionComboBox_);

    ++row;
    formTable->elementAt(row, 0)->setColumnSpan(2);
    formTable->elementAt(row, 0)->setPadding(10);
    extensionFormContainer_ = new WContainerWidget(formTable->elementAt(row, 0));
    
    preselectedExtensionItem_ = 0;
    extensionComboChanged(0);
}


void VanetExtensionForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    form_->setPreselectedValues(values);
}

void VanetExtensionForm::setPreselectedExtension(WStandardItem* rootItem)
{
    int currentIndex = (int)boost::any_cast<VanetProperty>(rootItem->data()) - 6;
    Logger::entry("info") << "Current index for extensions: " << currentIndex;
    extensionComboBox_->setCurrentIndex(currentIndex);
    preselectedExtensionItem_ = rootItem;
    extensionComboChanged(currentIndex);
}

bool VanetExtensionForm::validate(std::vector< std::string >& messages)
{
    return form_->validate(messages);
}

Wt::WStandardItem* VanetExtensionForm::treeNode()
{
    return form_->treeNode();
}

void VanetExtensionForm::extensionComboChanged(int itemIndex)
{
    Logger::entry("info") << "Extension itemIndex = " << itemIndex;
    extensionFormContainer_->clear();
    switch(itemIndex)
    {
        case 0:
            form_ = new VanetGmsOutPropertyForm(extensionFormContainer_);
            break;
        case 1:
            form_ = new VanetTimeSimulationPropertyForm(extensionFormContainer_);
            break;
        case 2:
            form_ = new VanetSpatialModelPropertyForm(extensionFormContainer_);
            break;
        case 3:
            form_ = new VanetTrafficLightPropertyForm(extensionFormContainer_);
            break;
        case 4:
            form_ = new VanetSpModelDump(extensionFormContainer_);
            break;
        default:
            extensionFormContainer_->clear();
            
    }
    if (preselectedExtensionItem_ != 0 && form_ != 0)
    {
        form_->setPreselectedValues(getValuesMap());
    }
    if (form_)
    {
        extensionFormContainer_->addWidget(form_);
    }
}

std::map< std::string, boost::any > VanetExtensionForm::getValuesMap()
{
    std::map< std::string, boost::any > values;
    Logger::entry("info") << "The row count of this preselected item is: " << preselectedExtensionItem_->rowCount();
    for (int row = 0; row < preselectedExtensionItem_->rowCount(); row++)
    {
        WString key = preselectedExtensionItem_->child(row, 2)->text();
        WString value = preselectedExtensionItem_->child(row, 1)->text();
        values.insert(std::make_pair< std::string, boost::any >(key.toUTF8(), value.toUTF8()));
        Logger::entry("info") << "Added preselected key for extension: " << key << " and value: " << value;
    }

    return values;
}

