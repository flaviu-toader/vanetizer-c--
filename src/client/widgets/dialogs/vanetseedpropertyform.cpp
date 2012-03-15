#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WLineEdit>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WLengthValidator>

#include "logger.h"
#include "vanetseedpropertyform.h"

using namespace Wt;

VanetSeedPropertyForm::VanetSeedPropertyForm(WStandardItemModel* model, WContainerWidget* parent):
    model_(model),
    seedLabel_(tr("mappropertyeditor.group.seed.label").toUTF8())
{
    WTable *formTable = new WTable(this);
    int row = 0;
    
    WLabel * sLabel = new WLabel(formTable->elementAt(row, 0));
    sLabel->setText(WString::fromUTF8(seedLabel_));
    seed_ = new WLineEdit(formTable->elementAt(row, 1));
    WLengthValidator *validator = new WLengthValidator(0, 16);
    validator->setMandatory(true);
    seed_->setValidator(validator);
    sLabel->setBuddy(seed_);
    
}


void VanetSeedPropertyForm::setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values)
{
    try
    {
        WString val = boost::any_cast<WString>(values.at(0));
        Logger::entry("info") << "Received preselected seed value: " << val.toUTF8() ;
    }
    catch (std::out_of_range)
    {
        Logger::entry("fatal") << "Fatal error. Parameter index for VanetSeedPropertyForm::setPreselectedValues is out of range!";
    }
}

std::vector< std::string, std::allocator< std::string > > VanetSeedPropertyForm::feedbackMessages()
{

}

bool VanetSeedPropertyForm::validate()
{
    if (seed_->validate() == WValidator::Invalid) 
    {
        messages_.push_back(tr("vanet.property.form.seed.error.seedsize").toUTF8());
        return false;
    }
    return true;
}

Wt::WStandardItem* VanetSeedPropertyForm::treeNode()
{
    WStandardItem * result = new WStandardItem(tr("mappropertyeditor.group.seed").toUTF8());
    result->setData(VanetSeed);
    result->appendRow(propertyRow(std::string("seed"), tr("mappropertyeditor.group.seed.label").toUTF8(), seed_->valueText().toUTF8()));
    return result;
}

