
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
    class WStandardItemModel;
}

class VanetAreaPropertyForm : public AbstractPropertyForm
{
public:
    VanetAreaPropertyForm(Wt::WStandardItemModel *model, Wt::WContainerWidget* parent = 0);
    virtual Wt::WStandardItem *treeNode();
    virtual bool validate();
    virtual std::vector<std::string> feedbackMessages();
    virtual void setPreselectedValues(const std::vector<boost::any> &values);

private:
    std::vector<std::string> messages_;
    std::string dimxLabel_, dimyLabel_;
    Wt::WSpinBox* dimx_, * dimy_;
    Wt::WStandardItemModel* model_;
};

#endif // VANETAREAPROPERTYFORM_H_
