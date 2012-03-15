#include <string>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WDoubleSpinBox>
#include <Wt/WString>
#include <Wt/WLabel>


#include "logger.h"
#include "vanetsteppropertyform.h"

using namespace Wt;

VanetStepPropertyForm::VanetStepPropertyForm(Wt::WStandardItemModel* model, Wt::WContainerWidget* parent):
    model_(model),
    stepLabel_(tr("mappropertyeditor.group.step.label").toUTF8())
{
    WTable *formTable = new WTable(this);
    int row = 0;
    
    WLabel *sLabel = new WLabel(formTable->elementAt(row, 0));
    sLabel->setText(WString::fromUTF8(stepLabel_));
    step_ = new WDoubleSpinBox(formTable->elementAt(row, 1));
    step_->setDecimals(3);
    step_->setMaximum(10.999);
    step_->setMinimum(0.001);
    sLabel->setBuddy(step_);
    
}

void VanetStepPropertyForm::setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values)
{
    try
    {
        double val = boost::any_cast<double>(values.at(0));
        Logger::entry("info") << "Received preselected step value: " << val;
        step_->setValue(val);
    }
    catch (std::out_of_range)
    {
        Logger::entry("fatal") << "Fatal error. Parameter index for VanetStepPropertyForm::setPreselectedValues out of range!";
    }
}

std::vector< std::string, std::allocator< std::string > > VanetStepPropertyForm::feedbackMessages()
{
}

bool VanetStepPropertyForm::validate()
{
    return true;
}

Wt::WStandardItem* VanetStepPropertyForm::treeNode()
{
    WStandardItem *result = new WStandardItem(tr("mappropertyeditor.group.step").toUTF8());
    result->setData(VanetStep);
    std::stringstream ss;
    ss.precision(3);
    ss << std::fixed << step_->value();
    result->appendRow(propertyRow(std::string("step"), tr("mappropertyeditor.group.step.label").toUTF8(), ss.str()));
    
    return result;
}

