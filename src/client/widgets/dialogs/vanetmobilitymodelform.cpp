#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WCheckBox>
#include <Wt/WComboBox>
#include <Wt/WDoubleSpinBox>

#include "vanetmobilitymodelform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

void VanetMobilityModelForm::setPreselectedValues(const map< string, boost::any >& values)
{
    WTable* t = new WTable(this);
    int row = 0;

    WLabel* l = new WLabel(tr("vanet.property.form.mobility.combo"), t->elementAt(row, 0));
    mobilityCombo_ = new WComboBox(t->elementAt(row, 1));
    mobilityCombo_->addItem(tr("vanet.property.form.mobility.combo.im"));
    mobilityCombo_->addItem(tr("vanet.property.form.mobility.combo.lc"));
    
    mobilityCombo_->activated().connect(this, &VanetMobilityModelForm::mobilityChanged);
    l->setBuddy(mobilityCombo_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.minspeed"), t->elementAt(row, 0));
    minSpeed_ = new WDoubleSpinBox(t->elementAt(row, 1));
    minSpeed_->setDecimals(1);
    minSpeed_->setMaximum(100.0);
    minSpeed_->setMinimum(0.0);
    minSpeed_->setValue(0.0);
    l->setBuddy(minSpeed_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.maxspeed"), t->elementAt(row, 0));
    maxSpeed_ = new WDoubleSpinBox(t->elementAt(row, 1));
    maxSpeed_->setDecimals(1);
    maxSpeed_->setMaximum(300.0);
    maxSpeed_->setMinimum(0.0);
    maxSpeed_->setValue(0.0);
    l->setBuddy(maxSpeed_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.length"), t->elementAt(row, 0));
    length_ = new WDoubleSpinBox(t->elementAt(row, 1));
    length_->setDecimals(1);
    length_->setMaximum(20.0);
    length_->setMinimum(0.1);
    length_->setValue(5.0);
    l->setBuddy(length_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.maxaccel"), t->elementAt(row, 0));
    maxAccel_ = new WDoubleSpinBox(t->elementAt(row, 1));
    maxAccel_->setDecimals(1);
    maxAccel_->setMaximum(10.0);
    maxAccel_->setMinimum(0.0);
    maxAccel_->setValue(0.6);
    l->setBuddy(maxAccel_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.comfydecel"), t->elementAt(row, 0));
    comfyDecel_ = new WDoubleSpinBox(t->elementAt(row, 1));
    comfyDecel_->setDecimals(1);
    comfyDecel_->setMaximum(10.0);
    comfyDecel_->setMinimum(0.0);
    comfyDecel_->setValue(0.6);
    l->setBuddy(comfyDecel_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.jamdist"), t->elementAt(row, 0));
    jamDistance_ = new WDoubleSpinBox(t->elementAt(row, 1));
    jamDistance_->setDecimals(1);
    jamDistance_->setMaximum(5.0);
    jamDistance_->setMinimum(0.1);
    jamDistance_->setValue(2.0);
    l->setBuddy(jamDistance_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.t"), t->elementAt(row, 0));
    safeTimeHeadway_ = new WDoubleSpinBox(t->elementAt(row, 1));
    safeTimeHeadway_->setDecimals(1);
    safeTimeHeadway_->setMaximum(10.0);
    safeTimeHeadway_->setMinimum(0.1);
    safeTimeHeadway_->setValue(1.5);
    l->setBuddy(safeTimeHeadway_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.step"), t->elementAt(row, 0));
    step_ = new WDoubleSpinBox(t->elementAt(row, 1));
    step_->setDecimals(1);
    step_->setMaximum(10.0);
    step_->setMinimum(0.1);
    l->setBuddy(step_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.stay"), t->elementAt(row, 0));
    stay_ = new WDoubleSpinBox(t->elementAt(row, 1));
    stay_->setDecimals(1);
    stay_->setMaximum(10.0);
    stay_->setMinimum(0.0);
    stay_->setValue(0.0);
    l->setBuddy(stay_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    random_ = new WCheckBox(tr("vanet.property.form.mobility.random"), t->elementAt(row, 0));
    random_->setCheckState(Unchecked);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    ignoreBorders_ = new WCheckBox(tr("vanet.property.form.mobility.ignoreborders"), t->elementAt(row, 0));
    ignoreBorders_->setCheckState(Unchecked);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.bsave"), t->elementAt(row, 0));
    bsave_ = new WDoubleSpinBox(t->elementAt(row, 1));
    bsave_->setDecimals(1);
    bsave_->setMaximum(10.0);
    bsave_->setMinimum(0.0);
    bsave_->setValue(4.0);
    bsave_->setDisabled(true);
    l->setBuddy(bsave_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.p"), t->elementAt(row, 0));
    politeness_ = new WDoubleSpinBox(t->elementAt(row, 1));
    politeness_->setDecimals(1);
    politeness_->setMaximum(1.0);
    politeness_->setMinimum(0.0);
    politeness_->setValue(0.5);
    politeness_->setDisabled(true);
    l->setBuddy(politeness_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.athr"), t->elementAt(row, 0));
    accelThresh_ = new WDoubleSpinBox(t->elementAt(row, 1));
    accelThresh_->setDecimals(1);
    accelThresh_->setMaximum(10.0);
    accelThresh_->setMinimum(0.0);
    accelThresh_->setValue(0.2);
    accelThresh_->setDisabled(true);
    l->setBuddy(accelThresh_);
    
}

WStandardItem* VanetMobilityModelForm::treeNode()
{

}

bool VanetMobilityModelForm::validate()
{
    return AbstractPropertyForm::validate();
}

vector< string > VanetMobilityModelForm::feedbackMessages()
{
    return AbstractPropertyForm::feedbackMessages();
}

void VanetMobilityModelForm::mobilityChanged(int itemIndex)
{
    bool disableItems = true;
    switch(itemIndex)
    {
        case 0:
            disableItems = true;
            break;
        case 1:
            disableItems = false;
            break;
    }
    bsave_->setDisabled(disableItems);
    politeness_->setDisabled(disableItems);
    accelThresh_->setDisabled(disableItems);
}
