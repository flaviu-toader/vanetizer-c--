#ifndef VANETNODEGROUPFORM_H
#define VANETNODEGROUPFORM_H

#include "abstractpropertyform.h"
#include "vanetmobilitymodelform.h"

namespace Wt
{
    class WLineEdit;
    class WSpinBox;
    class WStandardItem;
}


class VanetNodeGroupForm : public AbstractPropertyForm
{

public:
    VanetNodeGroupForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
private:
    Wt::WLineEdit* id_;
    Wt::WSpinBox* number_;
    VanetMobilityModelForm* form_;
};

#endif // VANETNODEGROUPFORM_H
