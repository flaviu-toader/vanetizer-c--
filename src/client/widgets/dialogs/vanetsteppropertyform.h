#ifndef VANETSTEPPROPERTYFORM_H
#define VANETSTEPPROPERTYFORM_H

#include <boost/any.hpp>

#include <vector>

#include "abstractpropertyform.h"

namespace Wt 
{
    class WStandardItem;
    class WDoubleSpinBox;
}

class VanetStepPropertyForm : public AbstractPropertyForm
{

public:
    VanetStepPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode(std::vector< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
private:
    Wt::WDoubleSpinBox *step_;
};

#endif // VANETSTEPPROPERTYFORM_H
