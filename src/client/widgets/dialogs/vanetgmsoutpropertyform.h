#ifndef VANETGMSOUTPROPERTYFORM_H
#define VANETGMSOUTPROPERTYFORM_H

#include "abstractpropertyform.h"

namespace Wt 
{
    class WStandardItem;
    class WLineEdit;
    class WDoubleSpinBox;
}

//! Class is no longer used.
class VanetGmsOutPropertyForm : public AbstractPropertyForm
{

public:
    VanetGmsOutPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual bool validate(std::vector< std::string >& messages);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
private:
    Wt::WDoubleSpinBox* step_;
    Wt::WLineEdit* outputFileName_;
};

#endif // VANETGMSOUTPROPERTYFORM_H
