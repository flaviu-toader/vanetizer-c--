#ifndef VANETEXTENSIONFORM_H
#define VANETEXTENSIONFORM_H

#include <map>

#include "abstractpropertyform.h"

namespace Wt 
{
    class WComboBox;
    class WStandardItem;
    class WStandardItemModel;
}

class VanetExtensionForm : public AbstractPropertyForm
{

public:
    //! Vanet Extension form constructor.
    /*!
     * Main constructor of the form, it receives the model of the treeview where this object will append
     * the user selected and configured extension.
     */
    VanetExtensionForm(Wt::WStandardItemModel* model, Wt::WContainerWidget* parent = 0);
    
    virtual void setPreselectedValues(const std::vector< boost::any, std::allocator< boost::any > >& values);
    
    virtual std::vector< std::string, std::allocator< std::string > > feedbackMessages();
    
    virtual bool validate();
    
    virtual Wt::WStandardItem* treeNode();
    
    void setPreselectedExtension(Wt::WStandardItem* rootItem);
    
private:
    //! Slot called when the combo value changes. Also called when editing an existing extension.
    void comboChanged(int itemIndex);
    
    Wt::WStandardItemModel* model_;
    Wt::WStandardItem* preselectedExtensionItem_;
    Wt::WContainerWidget* extensionFormContainer_;
    Wt::WComboBox* extensionComboBox_;
    std::string comboLabel_;
    std::vector<std::string> messages_;
    
};

#endif // VANETEXTENSIONFORM_H
