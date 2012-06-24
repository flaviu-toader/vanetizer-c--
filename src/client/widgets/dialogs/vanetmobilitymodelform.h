#ifndef VANETMOBILITYMODELFORM_H
#define VANETMOBILITYMODELFORM_H

#include "abstractpropertyform.h"

namespace Wt
{
    class WStandardItem;
    class WComboBox;
    class WDoubleSpinBox;
    class WCheckBox;
}

//! Used only in configuring node groups and nodes.
/*!
 * Defines the common fields of mobility models. Handles the IDM_IM and IDM_LC mobility models with their properties.
 */
class VanetMobilityModelForm : public AbstractPropertyForm
{

public:
    VanetMobilityModelForm(Wt::WContainerWidget* parent = 0);
    virtual void setPreselectedValues(const std::map< std::string, boost::any >& values);
    virtual Wt::WStandardItem* treeNode(std::list< Node >& nodes);
    virtual bool validate(std::vector< std::string >& messages);
    void appendPropertyRows(Wt::WStandardItem* item, std::list< Node >& nodes);
private:
    void mobilityChanged(int itemIndex);
    Wt::WComboBox* mobilityCombo_;
    Wt::WDoubleSpinBox* minSpeed_, * maxSpeed_, * length_, * maxAccel_, * comfyDecel_, * jamDistance_, * safeTimeHeadway_,
        * step_, * stay_, * bsave_, * politeness_, * accelThresh_;
    Wt::WCheckBox * random_, * ignoreBorders_;
};

#endif // VANETMOBILITYMODELFORM_H
