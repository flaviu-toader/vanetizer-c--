#ifndef VANETTRAFFICLIGHTPROPERTYFORM_H
#define VANETTRAFFICLIGHTPROPERTYFORM_H

#include "abstractpropertyform.h"

namespace Wt 
{
    class WSpinBox;
    class WStandardItem;
}

class VanetTrafficLightPropertyForm : public AbstractPropertyForm
{

public:
    VanetTrafficLightPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode();
    virtual bool validate();
private:
    Wt::WSpinBox* step_;
};

#endif // VANETTRAFFICLIGHTPROPERTYFORM_H