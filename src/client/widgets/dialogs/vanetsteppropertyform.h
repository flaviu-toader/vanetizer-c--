#ifndef VANETSTEPPROPERTYFORM_H
#define VANETSTEPPROPERTYFORM_H

#include <boost/any.hpp>

#include <string>
#include <vector>

#include "abstractpropertyform.h"

namespace Wt {
    class WStandardItem;
    class WDoubleSpinBox;
    class WStandardItemModel;
}

class VanetStepPropertyForm : public AbstractPropertyForm
{

public:
    VanetStepPropertyForm(Wt::WStandardItemModel *model, Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values);
    virtual std::vector< std::string, std::allocator< std::string > > feedbackMessages();
    virtual bool validate();
    virtual Wt::WStandardItem* treeNode();
    
private:
    Wt::WStandardItemModel *model_;
    std::string stepLabel_;
    Wt::WDoubleSpinBox *step_;
};

#endif // VANETSTEPPROPERTYFORM_H
