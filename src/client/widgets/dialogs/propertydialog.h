
#ifndef PROPERTYDIALOG_H_
#define PROPERTYDIALOG_H_

#include <Wt/WDialog>
#include <map>

#include "client/widgets/dialogs/abstractpropertyform.h"

namespace Wt {
    class WComboBox;
    class WStandardItemModel;
    class WStandardItem;
}

class PropertyDialog : public Wt::WDialog
{
public:
    PropertyDialog(Wt::WStandardItemModel *model);
    void setPreselectedProperty(Wt::WStandardItem *rootItem);

private:
    void submit(Wt::WDialog::DialogCode result);
    void comboChanged(int itemIndex);
    bool itemIsNew(Wt::WStandardItem* item);
    
    Wt::WStandardItemModel* model_;
    Wt::WStandardItem* preselectedItem_;
    Wt::WContainerWidget* formContainer_;
    Wt::WComboBox* mainComboBox_;
    std::map<VanetProperty, Wt::WString> comboMap_;
};

#endif // PROPERTYDIALOG_H_


