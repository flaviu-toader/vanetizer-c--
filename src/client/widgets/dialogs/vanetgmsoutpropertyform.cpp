#include <map>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WLengthValidator>
#include <Wt/WDoubleSpinBox>
#include <Wt/WStandardItem>
#include <Wt/WContainerWidget>

#include "vanetgmsoutpropertyform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

VanetGmsOutPropertyForm::VanetGmsOutPropertyForm(Wt::WContainerWidget* parent)
{
    WTable* mainTable = new WTable(this);
    int row = 0;
    
    WLabel* outputLbl = new WLabel(WString::fromUTF8(tr("vanet.property.form.gmsout.output").toUTF8()), mainTable->elementAt(row, 0));
    outputFileName_ = new WLineEdit(mainTable->elementAt(row, 1));
    outputLbl->setBuddy(outputFileName_);
    WLengthValidator* validator = new WLengthValidator(5, 24);
    validator->setMandatory(true);
    outputFileName_->setValidator(validator);
    
    ++row;
    WLabel* stepLbl = new WLabel(WString::fromUTF8(tr("vanet.property.form.gmsout.step").toUTF8()), mainTable->elementAt(row, 0));
    step_ = new WDoubleSpinBox(mainTable->elementAt(row, 1));
    stepLbl->setBuddy(step_);
    step_->setMaximum(10.0);
    step_->setValue(1.0);
    step_->setMinimum(0.1);
    step_->setDecimals(1);
}

void VanetGmsOutPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    map<string, boost::any>::const_iterator it;
    it = values.find("output=");
    if (it != values.end())
    {
        string filename = boost::any_cast<string>(it->second);
        Logger::entry("info") << "Setting preselected output value to " << filename;
        outputFileName_->setValueText(filename);
    }
    it = values.find("step");
    if (it != values.end())
    {
        double step = boost::lexical_cast< double >(boost::any_cast< string >(it->second));
        Logger::entry("info") << "Setting preselected step value to " << step;
        step_->setValue(step);
    }
}

bool VanetGmsOutPropertyForm::validate()
{
    if (outputFileName_->validate() == WValidator::Valid)
    {
        return true;
    }
    messages_.push_back(tr("vanet.property.form.gmsout.error.badfilename").toUTF8());
    return false;
}

Wt::WStandardItem* VanetGmsOutPropertyForm::treeNode()
{
    WStandardItem* result = new WStandardItem();
    result->setData(VanetGlomosimOutput);
    result->setText(tr("mappropertyeditor.group.gmsout"));
    
    result->appendRow(propertyRow(string("output="), tr("mappropertyeditor.group.gmsout.output").toUTF8(), outputFileName_->valueText().toUTF8()));
    stringstream ss;
    ss.precision(1);
    ss << std::fixed << step_->value();
    result->appendRow(propertyRow(string("step"), tr("mappropertyeditor.group.gmsout.step").toUTF8(), ss.str()));
    
    return result;
}

