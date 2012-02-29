
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
    ~VanetAreaPropertyForm();
private:
    Wt::WLength fWidth;
    Wt::WLength fHeight;
    std::string dimxLabel;
    std::string dimyLabel;
    Wt::WSpinBox *dimx;
    Wt::WSpinBox *dimy;
};

#endif // VANETAREAPROPERTYFORM_H_
