
#ifndef VANETAREAPROPERTYFORM_H_
#define VANETAREAPROPERTYFORM_H_

#include <string>
#include <vector>

#include "abstractpropertyform.h"

namespace Wt {
    class WStandardItem;
    class WSpinBox;
    class WLength;
    class WStandardItemModel;
}

class VanetAreaPropertyForm : public AbstractPropertyForm
{
public:
    VanetAreaPropertyForm(Wt::WStandardItemModel *model, Wt::WContainerWidget* parent = 0);
    Wt::WStandardItem *treeNode();
    Wt::WLength formWidth();
    Wt::WLength formHeight();
    bool validate();
    std::vector<std::string> feedbackMessages();
protected:
    std::vector<Wt::WStandardItem *> propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue);

private:
    std::vector<std::string> messages;
    Wt::WLength fWidth, fHeight;
    std::string dimxLabel, dimyLabel;
    Wt::WSpinBox *dimx, *dimy;
    Wt::WStandardItemModel *model;
};

#endif // VANETAREAPROPERTYFORM_H_
