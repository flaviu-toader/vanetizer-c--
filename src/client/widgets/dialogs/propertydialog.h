
#ifndef PROPERTYDIALOG_H_
#define PROPERTYDIALOG_H_

#include <Wt/WDialog>

namespace Wt {
    class WComboBox;
}

class PropertyDialog : public WDialog
{
public:
    PropertyDialog();
private:
    //TODO: also as a private member a list of pairs <string, WContainerWidget*> which will initialize the dialog with each relevant field,
    // depending on the user's selection in the combobox
    Wt::WComboBox *mainComboBox;
};

#endif // PROPERTYDIALOG_H_


