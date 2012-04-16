#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WStandardItem>
#include <Wt/WLineEdit>
#include <Wt/WSpinBox>
#include <Wt/WLengthValidator>

#include "vanetnodegroupform.h"
#include "vanetmobilitymodelform.h"

using namespace Wt;
using namespace std;

VanetNodeGroupForm::VanetNodeGroupForm(WContainerWidget* parent)
{
    WTable* t = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("vanet.property.form.nodegroup.id"), t->elementAt(row, 0));
    id_ = new WLineEdit(t->elementAt(row, 1));
    WLengthValidator* lv = new WLengthValidator(1, 15);
    id_->setValidator(lv);
    l->setBuddy(id_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.nodegroup.number"), t->elementAt(row, 0));
    number_ = new WSpinBox(t->elementAt(row, 1));
    number_->setMinimum(2);
    number_->setMaximum(100);
    number_->setValue(2);
    l->setBuddy(number_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    l = new WLabel(tr("vanet.property.form.nodes.mobility"), t->elementAt(row, 0));
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    form_ = new VanetMobilityModelForm;
    t->elementAt(row, 0)->addWidget(form_);
}

void VanetNodeGroupForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    map< string, boost::any>::const_iterator it; 
    map< string, boost::any> mobilityMap;
    for (it = values.begin(); it != values.end(); it++) 
    {
        if (it->first != "id=" && it->first != "n=")
        {
            mobilityMap.insert(make_pair< string, boost::any >(it->first, it->second));
        }
        else
        {
            if (it->first == "id=") 
            {
                id_->setValueText(WString::fromUTF8(boost::any_cast< string >(it->second)));
            }
            if (it->first == "n=")
            {
                number_->setValue(boost::lexical_cast< int >(boost::any_cast< string >(it->second)));
            }
        }
    }
    form_->setPreselectedValues(mobilityMap);

}

Wt::WStandardItem* VanetNodeGroupForm::treeNode()
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.nodegroup").arg(id_->valueText()));
    result->setData(VanetNodeGroup);
    
    result->appendRow(propertyRow(string("id="), tr("mappropertyeditor.group.nodegroup.id").toUTF8(), id_->valueText().toUTF8()));;
    result->appendRow(propertyRow(string("n="), tr("mappropertyeditor.group.nodegroup.nodes").toUTF8(), boost::lexical_cast< string >(number_->value())));
    result->appendRow(form_->treeNode());
    
    return result;
}

bool VanetNodeGroupForm::validate(std::vector< std::string >& messages)
{
    if (id_->validate() == WLengthValidator::Invalid ||
        id_->validate() == WLengthValidator::InvalidEmpty
    ) 
    {
        messages.push_back(tr("vanet.property.form.nodegroup.error.idlength").toUTF8());
        return false;
    }
    return form_->validate(messages);
}

