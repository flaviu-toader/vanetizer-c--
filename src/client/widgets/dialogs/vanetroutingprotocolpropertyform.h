#ifndef VANETROUTINGPROTOCOLPROPERTYFORM_H
#define VANETROUTINGPROTOCOLPROPERTYFORM_H

#include "abstractpropertyform.h"

namespace Wt 
{
    class WStandardItem;
    class WComboBox;
}

class VanetRoutingProtocolPropertyForm : public AbstractPropertyForm
{

public:
    VanetRoutingProtocolPropertyForm(Wt::WContainerWidget* parent = 0);
    
    virtual void setPreselectedValues(const std::map< std::string, boost::any, std::less< std::string >, std::allocator< std::pair< const std::string, boost::any > > >& values);
    virtual bool validate(std::vector< std::string, std::allocator< std::string > >& messages);
    virtual Wt::WStandardItem* treeNode(std::list< Node, std::allocator< Node > >& nodes);
private:
    int getIndexForText(const std::string& text);
    
    Wt::WComboBox* routingCombo_;
    Wt::WSpinBox* nodesCount_;
};

#endif // VANETROUTINGPROTOCOLPROPERTYFORM_H
