#ifndef VANETNODEFORM_H
#define VANETNODEFORM_H

#include "abstractpropertyform.h"
#include "vanetmobilitymodelform.h"

namespace Wt 
{
    class WLineEdit;
    class WStandardItem;
}

class VanetNodeForm : public AbstractPropertyForm
{

public:
    VanetNodeForm();
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual bool validate(std::vector< std::string >& messages);
    virtual Wt::WStandardItem* treeNode();
private:
    Wt::WLineEdit* id_;
    VanetMobilityModelForm* form_;
};

#endif // VANETNODEFORM_H
