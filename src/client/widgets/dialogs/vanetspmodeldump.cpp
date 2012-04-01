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
    map< string, boost::any >::const_iterator it;
    it = values.find("output=");
    string filename = boost::any_cast< string >(it->second);
    output_->setValueText(WString::fromUTF8(filename));
}

Wt::WStandardItem* VanetSpModelDump::treeNode()
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.spmodeldump"));
    result->setData(VanetSpatialModelDump);

    result->appendRow(propertyRow(string("output="), tr("mappropertyeditor.group.spmodeldump.output").toUTF8(), output_->valueText().toUTF8()));
    
    return result;
}

bool VanetSpModelDump::validate()
{
    if (output_->validate() == WValidator::Invalid) 
    {
        messages_.push_back(tr("vanet.property.form.spmodeldump.error.output").toUTF8());
        return false;
    }
    return true;
}

