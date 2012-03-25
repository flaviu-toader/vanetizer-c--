#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WSpinBox>
#include <Wt/WStandardItem>

#include "vanettrafficlightpropertyform.h"

using namespace Wt;
using namespace std;

VanetTrafficLightPropertyForm::VanetTrafficLightPropertyForm(Wt::WContainerWidget* parent)
{
    WTable* form = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("vanet.property.form.trlight.step"), form->elementAt(row, 0));
    step_ = new WSpinBox(form->elementAt(row, 1));
    step_->setMaximum(180000);
    step_->setMinimum(100);
    step_->setValue(10000);
    step_->validator()->setMandatory(true);
    l->setBuddy(step_);
}

bool VanetTrafficLightPropertyForm::validate()
{
    if(step_->validate() == WValidator::Invalid) 
    {
        messages_.push_back(tr("vanet.property.form.trlight.error.step").toUTF8());
        return false;
    }
    return true;
}

void VanetTrafficLightPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    step_->setValue(boost::any_cast<int>(*(values.find("step="))));
}

Wt::WStandardItem* VanetTrafficLightPropertyForm::treeNode()
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.trlight"));
    result->setData(VanetTrafficLights);
    
    result->appendRow(propertyRow(string("step="), tr("mappropertyeditor.group.trlight.step").toUTF8(), boost::lexical_cast<string>(step_->value())));
    
    return result;
}

