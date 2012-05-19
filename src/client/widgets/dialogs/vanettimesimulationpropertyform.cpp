#include <map>
#include <string>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WDoubleSpinBox>
#include <Wt/WStandardItem>

#include "vanettimesimulationpropertyform.h"

using namespace Wt;
using namespace std;

VanetTimeSimulationPropertyForm::VanetTimeSimulationPropertyForm(Wt::WContainerWidget* parent)
{
    WTable* table = new WTable(this);
    int row = 0;
    
    WLabel* label = new WLabel(tr("vanet.property.form.timesim.length"), table->elementAt(row, 0));
    param_ = new WDoubleSpinBox(table->elementAt(row, 1));
    param_->setMaximum(18000.0);
    param_->setMinimum(0.1);
    param_->setDecimals(1);
    param_->setValue(3600.0);

}

bool VanetTimeSimulationPropertyForm::validate(std::vector< std::string >& messages)
{
    return true;
}


void VanetTimeSimulationPropertyForm::setPreselectedValues(const map< string, boost::any >& values)
{
    setPreselectedDoubleValue("param=", values, param_);
}

Wt::WStandardItem* VanetTimeSimulationPropertyForm::treeNode(list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.timesim"));
    result->setData(VanetTimeSimulation);
    
    Node n("extension");
    Attribute c("class", "de.uni_stuttgart.informatik.canu.mobisim.simulations.TimeSimulation");
    n.addAttribute(c);
    
    stringstream ss;
    ss.precision(1);
    ss << std::fixed << param_->value();
    Attribute p("param", ss.str());
    n.addAttribute(p);
    result->appendRow(propertyRow(string("param="), tr("mappropertyeditor.group.timesim.param").toUTF8(), ss.str()));
    
    nodes.push_back(n);
    return result;
}
