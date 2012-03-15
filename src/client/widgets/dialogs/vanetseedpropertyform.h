#ifndef VANETSEEDPROPERTYFORM_H
#define VANETSEEDPROPERTYFORM_H

#include <boost/any.hpp>

#include <string>
#include <vector>

#include "abstractpropertyform.h"

namespace Wt {
    class WStandardItem;
    class WStandardItemModel;
    class WLineEdit;
}


class VanetSeedPropertyForm : public AbstractPropertyForm
{

public:
    VanetSeedPropertyForm(Wt::WStandardItemModel *model, Wt::WContainerWidget *parent = 0);
    virtual void setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values);
    virtual std::vector< std::string, std::allocator< std::string > > feedbackMessages();
    virtual bool validate();
    virtual Wt::WStandardItem* treeNode();
    
private:
    std::vector<std::string> messages_;
    Wt::WStandardItemModel *model_;
    std::string seedLabel_;
    Wt::WLineEdit *seed_;
};

#endif // VANETSEEDPROPERTYFORM_H
