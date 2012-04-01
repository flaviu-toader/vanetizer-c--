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


void VanetTimeSimulationPropertyForm::setPreselectedValues(const map< string, boost::any >& values)
{
    map< string, boost::any>::const_iterator it;
    it = values.find("param=");
    if (it != values.end()) 
    {
        double param = boost::lexical_cast< double >(boost::any_cast< string >(it->second));
        param_->setValue(param);
    }
}

Wt::WStandardItem* VanetTimeSimulationPropertyForm::treeNode()
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.timesim"));
    result->setData(VanetTimeSimulation);
    
    stringstream ss;
    ss.precision(1);
    ss << std::fixed << param_->value();
    result->appendRow(propertyRow(string("param="), tr("mappropertyeditor.group.timesim.param").toUTF8(), ss.str()));
    
    return result;
}
