#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WStandardItem>
#include <Wt/WLineEdit>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WLengthValidator>

#include "logger.h"
#include "vanetseedpropertyform.h"

using namespace Wt;

VanetSeedPropertyForm::VanetSeedPropertyForm(WContainerWidget* parent)
{
    WTable *formTable = new WTable(this);
    int row = 0;
    
    WLabel * sLabel = new WLabel(formTable->elementAt(row, 0));
    sLabel->setText(WString::fromUTF8(tr("mappropertyeditor.group.seed.label").toUTF8()));
    seed_ = new WLineEdit(formTable->elementAt(row, 1));
    WLengthValidator *validator = new WLengthValidator(1, 16);
    validator->setMandatory(true);
    seed_->setValidator(validator);
    sLabel->setBuddy(seed_);
    
}


void VanetSeedPropertyForm::setPreselectedValues(const std::map< std::string,  boost::any >& values)
{
    setPreselectedLineValue("seed", values, seed_);
}

bool VanetSeedPropertyForm::validate(std::vector< std::string >& messages)
{
    if (seed_->validate() == WLengthValidator::Invalid ||
        seed_->validate() == WLengthValidator::InvalidEmpty
    ) 
    {
        messages.push_back(tr("vanet.property.form.seed.error.seedsize").toUTF8());
        return false;
    }
    return true;
}

Wt::WStandardItem* VanetSeedPropertyForm::treeNode(std::list< Node >& nodes)
{
    WStandardItem * result = new WStandardItem(tr("mappropertyeditor.group.seed").toUTF8());
    result->setData(VanetSeed);
    
    Node seedNode("seed");
    seedNode.value(seed_->valueText().toUTF8());
    result->appendRow(propertyRow(std::string("seed"), tr("mappropertyeditor.group.seed.label").toUTF8(), seed_->valueText().toUTF8()));
    nodes.push_back(seedNode);
    return result;
}

