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
    l->setBuddy(minX_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.miny"), t->elementAt(row, 0));
    minY_ = new WSpinBox(t->elementAt(row, 1));
    minY_->setMaximum(20000);
    minY_->setMinimum(0);
    minY_->setValue(0);
    l->setBuddy(minY_); 
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.maxx"), t->elementAt(row, 0));
    maxX_ = new WSpinBox(t->elementAt(row, 1));
    maxX_->setMaximum(20000);
    maxX_->setMinimum(0);
    maxX_->setValue(0);
    l->setBuddy(maxX_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.maxy"), t->elementAt(row, 0));
    maxY_ = new WSpinBox(t->elementAt(row, 1));
    maxY_->setMaximum(20000);
    maxY_->setMinimum(0);
    maxY_->setValue(0);
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
    l->setBuddy(maxTrafficLights_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.lanes"), t->elementAt(row, 0));
    laneNumber_ = new WSpinBox(t->elementAt(row, 1));
    laneNumber_->setMaximum(4);
    laneNumber_->setMinimum(1);
    laneNumber_->setValue(1);
    l->setBuddy(laneNumber_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.spmodel.nomulti"), t->elementAt(row, 0));
    max_ = new WSpinBox(t->elementAt(row, 1));
    max_->setMaximum(1000);
    max_->setMinimum(0);
    max_->setValue(4);
    l->setBuddy(max_);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    full_ = new WCheckBox(tr("vanet.property.form.spmodel.allmulti"), t->elementAt(row, 0));
    full_->setCheckState(Unchecked);
    
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
    setPreselectedIntegerValue("min_x=", values, minX_);
    setPreselectedIntegerValue("min_y=", values, minY_);
    setPreselectedIntegerValue("max_x=", values, maxX_);
    setPreselectedIntegerValue("max_y=", values, maxY_);
    setPreselectedLineValue("traffic_light=", values, trafficLight_);
    setPreselectedIntegerValue("max_traffic_lights", values, maxTrafficLights_);
    setPreselectedIntegerValue("number_lane", values, laneNumber_);
    setPreselectedCheckboxValue("full=", values, full_);
    setPreselectedIntegerValue("max=", values, max_);
    setPreselectedCheckboxValue("dir=", values, dir_);
    setPreselectedCheckboxValue("reflect_directions", values, reflectDirs_);
}

Wt::WStandardItem* VanetSpatialModelPropertyForm::treeNode(std::list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.spmodel"));
    result->setData(VanetSpatialModel);
    
    Node extNode("extension");
    Attribute classAttr("class", "de.uni_stuttgart.informatik.canu.spatialmodel.core.SpatialModel");
    extNode.addAttribute(classAttr);
    
    Attribute minxAttr("min_x", boost::lexical_cast<string>(minX_->value()));
    extNode.addAttribute(minxAttr);
    result->appendRow(propertyRow(string("min_x="), tr("mappropertyeditor.group.spmodel.minx").toUTF8(), boost::lexical_cast<string>(minX_->value())));
    
    Attribute minyAttr("min_y", boost::lexical_cast<string>(minY_->value()));
    extNode.addAttribute(minyAttr);
    result->appendRow(propertyRow(string("min_y="), tr("mappropertyeditor.group.spmodel.miny").toUTF8(), boost::lexical_cast<string>(minY_->value())));
    
    Attribute maxxAttr("max_x", boost::lexical_cast<string>(maxX_->value()));
    extNode.addAttribute(maxxAttr);
    result->appendRow(propertyRow(string("max_x="), tr("mappropertyeditor.group.spmodel.maxx").toUTF8(), boost::lexical_cast<string>(maxX_->value())));
    
    Attribute maxyAttr("max_y", boost::lexical_cast<string>(maxY_->value()));
    extNode.addAttribute(maxyAttr);
    result->appendRow(propertyRow(string("max_y="), tr("mappropertyeditor.group.spmodel.maxy").toUTF8(), boost::lexical_cast<string>(maxY_->value())));
    
    string trafficLightName = trafficLight_->valueText().toUTF8();
    if (!trafficLightName.empty()) 
    {
        Attribute trafficLightAttr("traffic_light", trafficLightName);
        extNode.addAttribute(trafficLightAttr);
        result->appendRow(propertyRow(string("traffic_light="), tr("mappropertyeditor.group.spmodel.trlight").toUTF8(), trafficLightName));
    }
    
    Node maxTrLightsNode("max_traffic_lights");
    maxTrLightsNode.value(boost::lexical_cast<string>(maxTrafficLights_->value()));
    extNode.addChild(maxTrLightsNode);
    result->appendRow(propertyRow(string("max_traffic_lights"), tr("mappropertyeditor.group.spmodel.maxtrlight").toUTF8(), boost::lexical_cast<string>(maxTrafficLights_->value())));
    
    Node numberLaneNode("number_lane");
    numberLaneNode.value(boost::lexical_cast<string>(laneNumber_->value()));
    result->appendRow(propertyRow(string("number_lane"), tr("mappropertyeditor.group.spmodel.lanes").toUTF8(), boost::lexical_cast<string>(laneNumber_->value())));
    
    Attribute fullAttr("full", "true");
    string checkvalue = tr("constant.yes").toUTF8();
    if (full_->checkState() == Unchecked)
    {
        fullAttr.value("false");
        checkvalue = tr("constant.no").toUTF8();
    }
    numberLaneNode.addAttribute(fullAttr);
    result->appendRow(propertyRow(string("full="), tr("mappropertyeditor.group.spmodel.allmulti").toUTF8(), checkvalue));
    
    Attribute maxAttr("max", boost::lexical_cast<string>(max_->value()));
    numberLaneNode.addAttribute(maxAttr);
    result->appendRow(propertyRow(string("max="), tr("mappropertyeditor.group.spmodel.nomulti").toUTF8(), boost::lexical_cast<string>(max_->value())));
    
    Attribute dirAttr("dir", "true");
    checkvalue = tr("constant.yes").toUTF8();
    if (dir_->checkState() == Unchecked)
    {
        dirAttr.value("false");
        checkvalue = tr("constant.no").toUTF8();
    }
    numberLaneNode.addAttribute(dirAttr);
    result->appendRow(propertyRow(string("dir="), tr("mappropertyeditor.group.spmodel.bidirmulti").toUTF8(), checkvalue));
    extNode.addChild(numberLaneNode);
    
    Node reflectDirsNode("reflect_directions");
    reflectDirsNode.value("true");
    checkvalue = tr("constant.yes").toUTF8();
    if (reflectDirs_->checkState() == Unchecked)
    {
        reflectDirsNode.value("false");
        checkvalue = tr("constant.no").toUTF8();
    }
    result->appendRow(propertyRow(string("reflect_directions"), tr("mappropertyeditor.group.spmodel.bidir").toUTF8(), checkvalue));
    extNode.addChild(reflectDirsNode);
    
    nodes.push_back(extNode);
    
    // Default values for Position Generator and Trip Generator.
    Node posGenNode("extension");
    Attribute pgNameAttr("name", "PosGen");
    posGenNode.addAttribute(pgNameAttr);
    Attribute pgClass("class", "de.uni_stuttgart.informatik.canu.tripmodel.generators.RandomInitialPositionGenerator");
    posGenNode.addAttribute(pgClass);
    nodes.push_back(posGenNode);
    
    Node tripGenNode("extension");
    Attribute tgNameAttr("name", "TripGen");
    tripGenNode.addAttribute(tgNameAttr);
    Attribute tgClass("class", "de.uni_stuttgart.informatik.canu.tripmodel.generators.RandomTripGenerator");
    tripGenNode.addAttribute(tgClass);
    tripGenNode.addChild(reflectDirsNode);
    Node tgMinStay("minstay");
    tgMinStay.value("5.0");
    tripGenNode.addChild(tgMinStay);
    Node tgMaxStay("maxstay");
    tgMaxStay.value("30.0");
    tripGenNode.addChild(tgMaxStay);
    nodes.push_back(tripGenNode);

    Node guiNode = Node("extension");
    Attribute guiClassAttr = Attribute("class", "de.uni_stuttgart.informatik.canu.mobisimadd.extensions.GUI");
    guiNode.addAttribute(guiClassAttr);
    Node widthNode = Node("width");
    widthNode.value("640");
    Node heightNode = Node("height");
    heightNode.value("480");
    Node stepNode = Node("step");
    stepNode.value("1");
    guiNode.addChild(widthNode);
    guiNode.addChild(heightNode);
    guiNode.addChild(stepNode);
    nodes.push_back(guiNode);

    return result;
}

bool VanetSpatialModelPropertyForm::validate(std::vector< std::string >& messages)
{
    bool valid = true;
    if (maxX_->value() <= minX_->value())
    {
        messages.push_back(tr("vanet.property.form.spmodel.error.xerr").toUTF8());
        valid = false;
    }
    
    if (maxY_->value() <= minY_->value())
    {
        messages.push_back(tr("vanet.property.form.spmodel.error.yerr").toUTF8());
        valid = false;
    }
    
    if (maxX_->value() == 0 ||
        maxY_->value() == 0 ||
        trafficLight_->validate() == WLengthValidator::Invalid 
    )
    {
        messages.push_back(tr("vanet.property.form.spmodel.error.inputerr").toUTF8());
        valid = false;
    }
    return valid;
}

