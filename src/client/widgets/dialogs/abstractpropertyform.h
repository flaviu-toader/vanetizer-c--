

#ifndef ABSTRACTPROPERTYFORM_H_
#define ABSTRACTPROPERTYFORM_H_

#include <Wt/WContainerWidget>

namespace Wt {
    class WStandardItem;
    class WLength;
}

class AbstractPropertyForm : public Wt::WContainerWidget
{
public:
    virtual Wt::WStandardItem treeNode() = 0;
    //! The width that the property dialog should be resized to when displaying this property form.
    virtual Wt::WLength formWidth() = 0;
    //! The height that the property dialog should be resized to when displaying this property form.
    virtual Wt::WLength formHeight() = 0;
    virtual ~AbstractPropertyForm();

}


#endif // ABSTRACTPROPERTYFORM_H_
