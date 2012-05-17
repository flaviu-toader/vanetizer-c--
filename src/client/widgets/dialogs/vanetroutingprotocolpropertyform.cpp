#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WStandardItem>

#include "vanetroutingprotocolpropertyform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

VanetRoutingProtocolPropertyForm::VanetRoutingProtocolPropertyForm(WContainerWidget* parent)
{
    WTable* mainTable = new WTable(this);
    int row = 0;
    
    WLabel* routingLbl = new WLabel(tr("vanet.property.form.routing.combo"), mainTable->elementAt(row, 0));
    routingCombo_ = new WComboBox(mainTable->elementAt(row, 1));
    routingCombo_->addItem(tr("vanet.property.form.routing.combo.aodv"));
    routingCombo_->addItem(tr("vanet.property.form.routing.combo.bf"));
    routingCombo_->addItem(tr("vanet.property.form.routing.combo.dsr"));
    routingCombo_->addItem(tr("vanet.property.form.routing.combo.lar"));
    routingCombo_->addItem(tr("vanet.property.form.routing.combo.wrp"));
    routingLbl->setBuddy(routingCombo_);
    routingCombo_->setCurrentIndex(0);
}


void VanetRoutingProtocolPropertyForm::setPreselectedValues(const map< string, boost::any >& values)
{
    map< string, boost::any >::const_iterator it;
    it = values.find("routingprotocol");
    if (it != values.end())
    {
        int currentIndex = getIndexForText(boost::any_cast<string>(it->second));
        routingCombo_->setCurrentIndex(currentIndex);
    }
}

bool VanetRoutingProtocolPropertyForm::validate(vector< string >& messages)
{
    return true;
}

WStandardItem* VanetRoutingProtocolPropertyForm::treeNode(list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.glomosim"));
    
    Node routing("routingprotocol");
    stringstream ss;
    ss << routingCombo_->currentIndex();
    routing.value(ss.str());
    result->appendRow(propertyRow(string("routingprotocol"), tr("mappropertyeditor.group.glomosim.routingprotocol").toUTF8(), routingCombo_->currentText().toUTF8()));
    nodes.push_back(routing);
    return result;
}

int VanetRoutingProtocolPropertyForm::getIndexForText(const string& text)
{
    if (text == tr("vanet.property.form.routing.combo.aodv").toUTF8())
        return 0;
    if (text == tr("vanet.property.form.routing.combo.bf").toUTF8())
        return 1;
    if (text == tr("vanet.property.form.routing.combo.dsr").toUTF8())
        return 2;
    if (text == tr("vanet.property.form.routing.combo.lar").toUTF8())
        return 3;
    if (text == tr("vanet.property.form.routing.combo.wrp").toUTF8())
        return 4;
    return 0;
}

