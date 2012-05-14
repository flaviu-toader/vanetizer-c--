#ifndef VANETSPATIALMODELPROPERTYFORM_H
#define VANETSPATIALMODELPROPERTYFORM_H

#include "abstractpropertyform.h"

namespace Wt
{
    class WStandardItem;
    class WSpinBox;
    class WCheckBox;
    class WLineEdit;
}

class VanetSpatialModelPropertyForm : public AbstractPropertyForm
{

public:
    VanetSpatialModelPropertyForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any, std::less< std::string >, std::allocator< std::pair< const std::string, boost::any > > >& values);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
    
private:
    Wt::WSpinBox* minX_, * minY_, * maxX_, * maxY_, * maxTrafficLights_, * laneNumber_, * max_;
    Wt::WLineEdit* trafficLight_;
    Wt::WCheckBox* reflectDirs_, * full_, * dir_;
};

#endif // VANETSPATIALMODELPROPERTYFORM_H
