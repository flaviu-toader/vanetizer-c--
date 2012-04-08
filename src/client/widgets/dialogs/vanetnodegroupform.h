#ifndef VANETNODEGROUPFORM_H
#define VANETNODEGROUPFORM_H

#include "abstractpropertyform.h"


class VanetNodeGroupForm : public AbstractPropertyForm
{

public:
    VanetNodeGroupForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode();
    virtual bool validate();
    virtual std::vector< std::string > feedbackMessages();
private:
    Wt::WLineEdit* id_;
    Wt::WSpinBox* number_;
};

#endif // VANETNODEGROUPFORM_H
