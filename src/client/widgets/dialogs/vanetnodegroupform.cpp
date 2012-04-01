#include "vanetnodegroupform.h"

void VanetNodeGroupForm::setPreselectedValues(const std::map< std::string, boost::any, std::less< std::string >, std::allocator< std::pair< const std::string, boost::any > > >& values)
{

}

Wt::WStandardItem* VanetNodeGroupForm::treeNode()
{

}

bool VanetNodeGroupForm::validate()
{
    return AbstractPropertyForm::validate();
}

std::vector< std::string, std::allocator< std::string > > VanetNodeGroupForm::feedbackMessages()
{
    return AbstractPropertyForm::feedbackMessages();
}

