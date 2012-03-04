

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
    virtual Wt::WStandardItem *treeNode() = 0;
    //! The width that the property dialog should be resized to when displaying this property form.
    virtual Wt::WLength formWidth() = 0;
    //! The height that the property dialog should be resized to when displaying this property form.
    virtual Wt::WLength formHeight() = 0;
    //! Validate the property form
    virtual bool validate() = 0;
    //! Return the feedback messages
    virtual std::vector<std::string> feedbackMessages() = 0;
//     virtual ~AbstractPropertyForm() = 0;
protected:
    virtual std::vector<Wt::WStandardItem *> propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue) = 0;
};


#endif // ABSTRACTPROPERTYFORM_H_
