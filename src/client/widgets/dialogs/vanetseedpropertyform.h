#ifndef VANETSEEDPROPERTYFORM_H
#define VANETSEEDPROPERTYFORM_H

#include <boost/any.hpp>

#include <map>

#include "abstractpropertyform.h"

namespace Wt 
{
    class WStandardItem;
    class WLineEdit;
}


class VanetSeedPropertyForm : public AbstractPropertyForm
{

public:
    VanetSeedPropertyForm(Wt::WContainerWidget *parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual bool validate(std::vector< std::string >& messages);
    virtual Wt::WStandardItem* treeNode(std::vector< Node >& nodes);
    
private:
    Wt::WLineEdit *seed_;
};

#endif // VANETSEEDPROPERTYFORM_H
