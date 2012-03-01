
#ifndef VANETAREAPROPERTYFORM_H_
#define VANETAREAPROPERTYFORM_H_

#include "abstractpropertyform.h"

namespace Wt {
    class WStandardItem;
    class WSpinBox;
    class WLength;
}

namespace std {
    class string;
}

class VanetAreaPropertyForm : public AbstractPropertyForm
{
public:
    VanetAreaPropertyForm(WContainerWidget* parent = 0);
    Wt::WStandardItem treeNode();
    Wt::WLength formWidth();
    Wt::WLength formHeight();
    bool validate();
    ~VanetAreaPropertyForm();
private:

    bool checkValid(WFormWidget *edit, const WString& errorText);

    Wt::WLength fWidth;
    Wt::WLength fHeight;
    std::string dimxLabel;
    std::string dimyLabel;
    Wt::WSpinBox *dimx;
    Wt::WSpinBox *dimy;
    Wt::WContainerWidget *feedbackMessages;
};

#endif // VANETAREAPROPERTYFORM_H_
