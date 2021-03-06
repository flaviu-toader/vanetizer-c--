#ifndef VANETSPMODELDUMP_H
#define VANETSPMODELDUMP_H

#include "abstractpropertyform.h"

namespace Wt
{
    class WStandardItem;
    class WLineEdit;
}

class VanetSpModelDump : public AbstractPropertyForm
{

public:
    VanetSpModelDump(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
private:
    Wt::WLineEdit* output_;
};

#endif // VANETSPMODELDUMP_H
