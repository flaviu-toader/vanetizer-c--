
#ifndef VANETAREAPROPERTYFORM_H_
#define VANETAREAPROPERTYFORM_H_

#include <boost/any.hpp>

#include <string>
#include <vector>

#include "abstractpropertyform.h"

namespace Wt 
{
    class WStandardItem;
    class WSpinBox;
}

class VanetAreaPropertyForm : public AbstractPropertyForm
{
public:
    VanetAreaPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual Wt::WStandardItem *treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
private:
    Wt::WSpinBox* dimx_, * dimy_;
};

#endif // VANETAREAPROPERTYFORM_H_
