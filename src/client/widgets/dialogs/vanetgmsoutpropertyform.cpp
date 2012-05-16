#include <map>
#include <vector>
#include <string>
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
    setPreselectedLineValue("output=", values, outputFileName_);
    setPreselectedDoubleValue("step", values, step_);
}

bool VanetGmsOutPropertyForm::validate(std::vector< std::string >& messages)
{
    if (outputFileName_->validate() == WValidator::Valid)
    {
        return true;
    }
    messages.push_back(tr("vanet.property.form.gmsout.error.badfilename").toUTF8());
    return false;
}

Wt::WStandardItem* VanetGmsOutPropertyForm::treeNode(std::list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem();
    result->setData(VanetGlomosimOutput);
    result->setText(tr("mappropertyeditor.group.gmsout"));
    
    Node extensionNode = Node("extension");
    Attribute extensionClass = Attribute("class", "de.uni_stuttgart.informatik.canu.mobisim.extensions.GlomosimOutput");
    extensionNode.addAttribute(extensionClass);
    Attribute output = Attribute("output", outputFileName_->valueText().toUTF8());
    extensionNode.addAttribute(output);
    result->appendRow(propertyRow(string("output="), tr("mappropertyeditor.group.gmsout.output").toUTF8(), outputFileName_->valueText().toUTF8()));
    
    stringstream ss;
    ss.precision(1);
    ss << std::fixed << step_->value();
    Node stepNode = Node("step");
    stepNode.value(ss.str());
    extensionNode.addChild(stepNode);
    result->appendRow(propertyRow(string("step"), tr("mappropertyeditor.group.gmsout.step").toUTF8(), ss.str()));
    nodes.push_back(extensionNode);
    return result;
}

