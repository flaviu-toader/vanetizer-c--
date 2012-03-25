#ifndef VANETEXTENSIONFORM_H
#define VANETEXTENSIONFORM_H

#include <map>

#include "abstractpropertyform.h"

namespace Wt 
{
    class WComboBox;
    class WStandardItem;
}

class VanetExtensionForm : public AbstractPropertyForm
{

public:
    //! Vanet Extension form constructor.
    VanetExtensionForm(Wt::WContainerWidget* parent = 0);
    
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    
    virtual bool validate();
    
    virtual Wt::WStandardItem* treeNode();
    
    void setPreselectedExtension(Wt::WStandardItem* rootItem);
    
private:
    //! Slot called when the combo value changes. Also called when editing an existing extension.
    void comboChanged(int itemIndex);
    
    Wt::WStandardItem* preselectedExtensionItem_;
    Wt::WContainerWidget* extensionFormContainer_;
    Wt::WComboBox* extensionComboBox_;
    AbstractPropertyForm* form_;
    
};

#endif // VANETEXTENSIONFORM_H
