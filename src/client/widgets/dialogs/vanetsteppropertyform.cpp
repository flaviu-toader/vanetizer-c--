#include <string>
#include <map>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WStandardItem>
#include <Wt/WDoubleSpinBox>
#include <Wt/WString>
#include <Wt/WLabel>


#include "logger.h"
#include "vanetsteppropertyform.h"

using namespace Wt;

VanetStepPropertyForm::VanetStepPropertyForm(Wt::WContainerWidget* parent)
{
    WTable *formTable = new WTable(this);
    int row = 0;
    
    WLabel *sLabel = new WLabel(formTable->elementAt(row, 0));
    sLabel->setText(WString::fromUTF8(tr("mappropertyeditor.group.step.label").toUTF8()));
    step_ = new WDoubleSpinBox(formTable->elementAt(row, 1));
    step_->setDecimals(3);
    step_->setMaximum(10.999);
    step_->setMinimum(0.001);
    sLabel->setBuddy(step_);
    
}

void VanetStepPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    double val = boost::any_cast<double>(*values.find("step"));
    Logger::entry("info") << "Received preselected step value: " << val;
    step_->setValue(val);
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

