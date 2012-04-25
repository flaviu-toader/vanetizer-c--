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
    
    virtual bool validate(std::vector< std::string >& messages);
    
    virtual Wt::WStandardItem* treeNode(std::vector< Node >& nodes);
    
    void setPreselectedExtension(Wt::WStandardItem* rootItem);
    
private:
    //! Slot called when the combo value changes. Also called when editing an existing extension.
    void extensionComboChanged(int itemIndex);
    
    std::map <std::string, boost::any> getValuesMap();
    
    Wt::WStandardItem* preselectedExtensionItem_;
    Wt::WContainerWidget* extensionFormContainer_;
    Wt::WComboBox* extensionComboBox_;
    AbstractPropertyForm* form_;
    
};

#endif // VANETEXTENSIONFORM_H
