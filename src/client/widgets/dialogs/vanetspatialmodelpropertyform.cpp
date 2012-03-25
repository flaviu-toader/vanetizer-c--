#include <map>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/concept_check.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WSpinBox>
#include <Wt/WLengthValidator>
#include <Wt/WCheckBox>
#include <Wt/WStandardItem>
#include <Wt/WValidator>

#include "vanetspatialmodelpropertyform.h"

using namespace Wt;
using namespace std;

VanetSpatialModelPropertyForm::VanetSpatialModelPropertyForm(Wt::WContainerWidget* parent)
{
    WTable* t = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("vanet.property.form.spmodel.minx"), t->elementAt(row, 0));
    minX_ = new WSpinBox(t->elementAt(row, 1));
    minX_->setMaximum(20000);
    minX_->setMinimum(0);
    minX_->setValue(0);
    minX_->validator()->setMandatory(true);
    l->setBuddy(minX_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.miny"), t->elementAt(row, 0));
    minY_ = new WSpinBox(t->elementAt(row, 1));
    minY_->setMaximum(20000);
    minY_->setMinimum(0);
    minY_->setValue(0);
    minY_->validator()->setMandatory(true);
    l->setBuddy(minY_); 
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.maxx"), t->elementAt(row, 0));
    maxX_ = new WSpinBox(t->elementAt(row, 1));
    maxX_->setMaximum(20000);
    maxX_->setMinimum(0);
    maxX_->setValue(0);
    maxX_->validator()->setMandatory(true);
    l->setBuddy(maxX_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.maxy"), t->elementAt(row, 0));
    maxY_ = new WSpinBox(t->elementAt(row, 1));
    maxY_->setMaximum(20000);
    maxY_->setMinimum(0);
    maxY_->setValue(0);
    maxY_->validator()->setMandatory(true);
    l->setBuddy(maxY_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.trlight"), t->elementAt(row, 0));
    trafficLight_ = new WLineEdit(t->elementAt(row, 1));
    WLengthValidator* validator = new WLengthValidator(0, 24);
    validator->setMandatory(false);
    trafficLight_->setValidator(validator);
    l->setBuddy(trafficLight_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.maxtrlight"), t->elementAt(row, 0));
    maxTrafficLights_ = new WSpinBox(t->elementAt(row, 1));
    maxTrafficLights_->setMaximum(1000);
    maxTrafficLights_->setMinimum(0);
    maxTrafficLights_->setValue(5);
    maxTrafficLights_->validator()->setMandatory(false);
    l->setBuddy(maxTrafficLights_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.lanes"), t->elementAt(row, 0));
    laneNumber_ = new WSpinBox(t->elementAt(row, 1));
    laneNumber_->setMaximum(4);
    laneNumber_->setMinimum(1);
    laneNumber_->setValue(1);
    l->setBuddy(laneNumber_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    full_ = new WCheckBox(tr("vanet.property.form.spmodel.allmulti"), t->elementAt(row, 0));
    full_->setCheckState(Unchecked);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.nomulti"), t->elementAt(row, 0));
    max_ = new WSpinBox(t->elementAt(row, 1));
    max_->setMaximum(1000);
    max_->setMinimum(0);
    max_->setValue(4);
    l->setBuddy(max_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    dir_ = new WCheckBox(tr("vanet.property.form.spmodel.bidirmulti"), t->elementAt(row, 0));
    dir_->setCheckState(Unchecked);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    reflectDirs_ = new WCheckBox(tr("vanet.property.form.spmodel.bidir"), t->elementAt(row, 0));
    reflectDirs_->setCheckState(Unchecked);

}


void VanetSpatialModelPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    minX_->setValue(boost::any_cast<int>(*(values.find("min_x="))));
    minY_->setValue(boost::any_cast<int>(*(values.find("min_y="))));
    maxX_->setValue(boost::any_cast<int>(*(values.find("max_x="))));
    maxY_->setValue(boost::any_cast<int>(*(values.find("max_y="))));
    trafficLight_->setValueText(boost::any_cast< WString >(*(values.find("traffic_light="))));
    maxTrafficLights_->setValue(boost::any_cast<int>(*(values.find("max_traffic_lights"))));
    laneNumber_->setValue(boost::any_cast<int>(*(values.find("number_lane"))));
    string checkvalue = *(values.find("full="));
    full_->setCheckState((checkvalue == "Yes") ? Checked : Unchecked);
    max_->setValue(boost::any_cast<int>(*(values.find("max="))));
    checkvalue = *(values.find("dir="));
    dir_->setCheckState((checkvalue == "Yes") ? Checked : Unchecked);
    checkvalue = *(values.find("reflect_directions"));
    reflectDirs_->setCheckState((checkvalue == "Yes") ? Checked : Unchecked);
}

Wt::WStandardItem* VanetSpatialModelPropertyForm::treeNode()
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.spmodel"));
    result->setData(VanetSpatialModel);
    
    result->appendRow(propertyRow(string("min_x="), tr("mappropertyeditor.group.spmodel.minx").toUTF8(), boost::lexical_cast<string>(minX_->value())));
    result->appendRow(propertyRow(string("min_y="), tr("mappropertyeditor.group.spmodel.miny").toUTF8(), boost::lexical_cast<string>(minY_->value())));
    result->appendRow(propertyRow(string("max_x="), tr("mappropertyeditor.group.spmodel.maxx").toUTF8(), boost::lexical_cast<string>(maxX_->value())));
    result->appendRow(propertyRow(string("max_y="), tr("mappropertyeditor.group.spmodel.maxy").toUTF8(), boost::lexical_cast<string>(maxY_->value())));
    string trafficLightName = trafficLight_->valueText().toUTF8();
    if (!trafficLightName.empty()) 
    {
        result->appendRow(propertyRow(string("traffic_light="), tr("mappropertyeditor.group.spmodel.trlight").toUTF8(), trafficLightName));
    }
    result->appendRow(propertyRow(string("max_traffic_lights"), tr("mappropertyeditor.group.spmodel.maxtrlight").toUTF8(), boost::lexical_cast<string>(maxTrafficLights_->value())));
    result->appendRow(propertyRow(string("number_lane"), tr("mappropertyeditor.group.spmodel.lanes").toUTF8(), boost::lexical_cast<string>(laneNumber_->value())));
    string checkvalue = "Yes";
    if (full_->checkState() == Unchecked)
    {
        checkvalue = "No";
    }
    result->appendRow(propertyRow(string("full="), tr("mappropertyeditor.group.spmodel.allmulti").toUTF8(), checkvalue));
    result->appendRow(propertyRow(string("max="), tr("mappropertyeditor.group.spmodel.nomulti").toUTF8(), boost::lexical_cast<string>(max_->value())));
    checkvalue = "Yes";
    if (dir_->checkState() == Unchecked)
    {
        checkvalue = "No";
    }
    result->appendRow(propertyRow(string("dir="), tr("mappropertyeditor.group.spmodel.bidirmulti").toUTF8(), checkvalue));
    checkvalue = "Yes";
    if (reflectDirs_->checkState() == Unchecked)
    {
        checkvalue = "No";
    }
    result->appendRow(propertyRow(string("reflect_directions"), tr("mappropertyeditor.group.spmodel.bidir").toUTF8(), checkvalue));
    return result;
}

bool VanetSpatialModelPropertyForm::validate()
{
    bool valid = true;
    if (maxX_->value() <= minX_->value())
    {
        messages_.push_back(tr("vanet.property.form.spmodel.error.xerr").toUTF8());
        valid = false;
    }
    
    if (maxY_->value() <= minY_->value())
    {
        messages_.push_back(tr("vanet.property.form.spmodel.error.yerr").toUTF8());
        valid = false;
    }
    
    if (maxX_->validate() == WValidator::Invalid ||
        maxY_->validate() == WValidator::Invalid ||
        minX_->validate() == WValidator::Invalid ||
        minY_->validate() == WValidator::Invalid ||
        trafficLight_->validate() == WValidator::Invalid ||
        maxTrafficLights_->validate() == WValidator::Invalid ||
        laneNumber_->validate() == WValidator::Invalid ||
        full_->validate() == WValidator::Invalid ||
        max_->validate() == WValidator::Invalid ||
        dir_->validate() == WValidator::Invalid || 
        reflectDirs_->validate() == WValidator::Invalid
    )
    {
        messages_.push_back(tr("vanet.property.form.spmodel.error.inputerr").toUTF8());
        valid = false;
    }
    return valid;
}

