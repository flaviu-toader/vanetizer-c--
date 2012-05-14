#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WLengthValidator>
#include <Wt/WStandardItem>

#include "vanetspmodeldump.h"

using namespace Wt;
using namespace std;

VanetSpModelDump::VanetSpModelDump(Wt::WContainerWidget* parent)
{
    WTable* t = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("vanet.property.form.spmodeldump.output"), t->elementAt(row, 0));
    output_ = new WLineEdit(t->elementAt(row, 1));
    WLengthValidator* validator = new WLengthValidator(5, 15);
    validator->setMandatory(true);
    output_->setValidator(validator);
}


void VanetSpModelDump::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    setPreselectedLineValue("output=", values, output_);
}

Wt::WStandardItem* VanetSpModelDump::treeNode(list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.spmodeldump"));
    result->setData(VanetSpatialModelDump);
    
    Node extNode("extension");
    Attribute classAttr("class", "de.uni_stuttgart.informatik.canu.spatialmodel.extensions.DumpSpatialModel");
    extNode.addAttribute(classAttr);
    Attribute outAttr("output", output_->valueText().toUTF8());
    extNode.addAttribute(outAttr);
    result->appendRow(propertyRow(string("output="), tr("mappropertyeditor.group.spmodeldump.output").toUTF8(), output_->valueText().toUTF8()));
    
    nodes.push_back(extNode);
    return result;
}

bool VanetSpModelDump::validate(std::vector< std::string >& messages)
{
    if (output_->validate() == WValidator::Invalid) 
    {
        messages.push_back(tr("vanet.property.form.spmodeldump.error.output").toUTF8());
        return false;
    }
    return true;
}

