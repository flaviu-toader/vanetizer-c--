
#ifndef PROPERTYDIALOG_H_
#define PROPERTYDIALOG_H_

#include <Wt/WDialog>


namespace Wt {
    class WComboBox;
    class WStandardItemModel;
    class WStandardItem;
}

class PropertyDialog : public Wt::WDialog
{
public:
    PropertyDialog(Wt::WStandardItemModel *model);

private:
    void submit(Wt::WDialog::DialogCode result);
    void comboChanged(int itemIndex);
    bool itemIsNew(Wt::WStandardItem* item);
    
    Wt::WStandardItemModel *model;
    Wt::WContainerWidget *formContainer;
    Wt::WComboBox *mainComboBox;
};

#endif // PROPERTYDIALOG_H_


