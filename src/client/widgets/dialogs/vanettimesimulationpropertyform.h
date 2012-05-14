#ifndef VANETTIMESIMULATIONPROPERTYFORM_H
#define VANETTIMESIMULATIONPROPERTYFORM_H

#include "abstractpropertyform.h"


namespace Wt
{
    class WStandardItem;
    class WDoubleSpinBox;
}

class VanetTimeSimulationPropertyForm : public AbstractPropertyForm
{

public:
    VanetTimeSimulationPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
private:
    Wt::WDoubleSpinBox* param_;
};

#endif // VANETTIMESIMULATIONPROPERTYFORM_H
