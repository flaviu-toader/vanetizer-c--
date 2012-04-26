#include <map>
#include <vector>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WStandardItem>
#include <Wt/WLineEdit>
#include <Wt/WLengthValidator>

#include "vanetnodeform.h"
#include "vanetmobilitymodelform.h"

using namespace std;
using namespace Wt;

VanetNodeForm::VanetNodeForm()
{
    WTable* t = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("vanet.property.form.node.id"), t->elementAt(row, 0));
    id_ = new WLineEdit(t->elementAt(row, 1));
    WLengthValidator* lv = new WLengthValidator(1, 15);
    id_->setValidator(lv);
    l->setBuddy(id_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    l = new WLabel(tr("vanet.property.form.nodes.mobility"), t->elementAt(row, 0));
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    form_ = new VanetMobilityModelForm;
    t->elementAt(row, 0)->addWidget(form_);
}

void VanetNodeForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    map< string, boost::any>::const_iterator it; 
    map< string, boost::any> mobilityMap;
    for (it = values.begin(); it != values.end(); it++) 
    {
        if (it->first != "id=")
        {
            mobilityMap.insert(make_pair< string, boost::any >(it->first, it->second));
        }
        else
        {
            if (it->first == "id=") 
            {
                id_->setValueText(WString::fromUTF8(boost::any_cast< string >(it->second)));
            }
        }
    }
    form_->setPreselectedValues(mobilityMap);

}

bool VanetNodeForm::validate(std::vector< std::string >& messages)
{
    if (id_->validate() == WLengthValidator::Invalid ||
        id_->validate() == WLengthValidator::InvalidEmpty
    ) 
    {
        messages.push_back(tr("vanet.property.form.node.error.idlength").toUTF8());
        return false;
    }
    return form_->validate(messages);

}

Wt::WStandardItem* VanetNodeForm::treeNode(std::vector< Node >& nodes)
{
    
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.node").arg(id_->valueText()));
    result->setData(VanetNode);
    
    Node n("node");
    Attribute idAttr("id", id_->valueText().toUTF8());
    n.addAttribute(idAttr);
    Node posNode("position");
    Attribute rndAttr("random", "true");
    posNode.addAttribute(rndAttr);
    n.addChild(posNode);
    result->appendRow(propertyRow(string("id="), tr("mappropertyeditor.group.node.id").toUTF8(), id_->valueText().toUTF8()));;
    result->appendRow(form_->treeNode(nodes));
    Node extNode = nodes.back();
    nodes.pop_back();
    n.addChild(extNode);
    nodes.push_back(n);
    return result;

}


