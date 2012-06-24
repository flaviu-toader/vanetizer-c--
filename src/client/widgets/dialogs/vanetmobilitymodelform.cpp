#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <boost/concept_check.hpp>

#include <Wt/WTable>
#include <Wt/WLabel>
#include <Wt/WCheckBox>
#include <Wt/WComboBox>
#include <Wt/WDoubleSpinBox>
#include <Wt/WStandardItem>

#include "abstractpropertyform.h"
#include "vanetmobilitymodelform.h"
#include "logger.h"

using namespace Wt;
using namespace std;

VanetMobilityModelForm::VanetMobilityModelForm(WContainerWidget* parent)
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
    length_->setMinimum(0.0);
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
    jamDistance_->setMinimum(0.0);
    jamDistance_->setValue(2.0);
    l->setBuddy(jamDistance_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.t"), t->elementAt(row, 0));
    safeTimeHeadway_ = new WDoubleSpinBox(t->elementAt(row, 1));
    safeTimeHeadway_->setDecimals(1);
    safeTimeHeadway_->setMaximum(10.0);
    safeTimeHeadway_->setMinimum(0.0);
    safeTimeHeadway_->setValue(1.5);
    l->setBuddy(safeTimeHeadway_);
    
    ++row;
    l = new WLabel(tr("vanet.property.form.mobility.step"), t->elementAt(row, 0));
    step_ = new WDoubleSpinBox(t->elementAt(row, 1));
    step_->setDecimals(1);
    step_->setMaximum(10.0);
    step_->setMinimum(0.1);
    step_->setValue(0.9);
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
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    random_ = new WCheckBox(tr("vanet.property.form.mobility.random"), t->elementAt(row, 0));
    random_->setCheckState(Unchecked);
    
    ++row;
    t->elementAt(row, 0)->setColumnSpan(2);
    ignoreBorders_ = new WCheckBox(tr("vanet.property.form.mobility.ignoreborders"), t->elementAt(row, 0));
    ignoreBorders_->setCheckState(Unchecked);
}

WStandardItem* VanetMobilityModelForm::treeNode(std::list< Node >& nodes)
{
    WStandardItem* result = new WStandardItem(tr("mappropertyeditor.group.mobility"));
    
    appendPropertyRows(result, nodes);

    return result;
}

void VanetMobilityModelForm::appendPropertyRows(WStandardItem* item, list< Node >& nodes)
{
    Node extensionNode = Node("extension");
    string mobilityClass;
    if (mobilityCombo_->currentIndex() == 0 || mobilityCombo_->currentIndex() == -1) 
    {
        mobilityClass = string(AbstractPropertyForm::INTERSECTION_MANAGEMENT_MODEL);
    }
    else
        if (mobilityCombo_->currentIndex() == 1)
        {
            mobilityClass = string(AbstractPropertyForm::LANE_CHANGING_MODEL);
        }
    if (mobilityClass.empty())
    {
        Logger::entry("error") << "Could not determine Mobility class! Exiting";
        throw "Could not determine mobility class.";
    }
    
    Attribute classAttribute = Attribute("class", mobilityClass);
    extensionNode.addAttribute(classAttribute);
    Attribute posGenAttr = Attribute("initposgenerator", "PosGen");
    extensionNode.addAttribute(posGenAttr);
    Attribute tripGenAttr = Attribute("tripgenerator", "TripGen");
    extensionNode.addAttribute(tripGenAttr);
    item->appendRow(propertyRow(string("class="), tr("mappropertyeditor.group.mobility.combo").toUTF8(), mobilityClass));
    
    Node minSpeedNode("minspeed");
    minSpeedNode.value(boost::lexical_cast<string>(minSpeed_->value()));
    extensionNode.addChild(minSpeedNode);
    item->appendRow(propertyRow(string("minspeed"), tr("mappropertyeditor.group.mobility.minspeed").toUTF8(), boost::lexical_cast<string>(minSpeed_->value())));
    
    Node maxSpeedNode("maxspeed");
    maxSpeedNode.value(boost::lexical_cast<string>(maxSpeed_->value()));
    extensionNode.addChild(maxSpeedNode);
    item->appendRow(propertyRow(string("maxspeed"), tr("mappropertyeditor.group.mobility.maxspeed").toUTF8(), boost::lexical_cast<string>(maxSpeed_->value())));
    
    if (length_->value() != length_->minimum())
    {
        Node lNode("l");
        lNode.value(boost::lexical_cast<string>(length_->value()));
        extensionNode.addChild(lNode);
        item->appendRow(propertyRow(string("l"), tr("mappropertyeditor.group.mobility.length").toUTF8(), boost::lexical_cast<string>(length_->value())));
    }
    if (maxAccel_->value() != maxAccel_->minimum())
    {
        Node aNode("a");
        aNode.value(boost::lexical_cast<string>(maxAccel_->value()));
        extensionNode.addChild(aNode);
        item->appendRow(propertyRow(string("a"), tr("mappropertyeditor.group.mobility.maxaccel").toUTF8(), boost::lexical_cast<string>(maxAccel_->value())));
    }
    if (comfyDecel_->value() != comfyDecel_->minimum())
    {
        Node bNode("b");
        bNode.value(boost::lexical_cast<string>(comfyDecel_->value()));
        extensionNode.addChild(bNode);
        item->appendRow(propertyRow(string("b"), tr("mappropertyeditor.group.mobility.comfydecel").toUTF8(), boost::lexical_cast<string>(comfyDecel_->value())));
    }
    if (jamDistance_->value() != jamDistance_->minimum())
    {
        Node jamNode("s0");
        jamNode.value(boost::lexical_cast<string>(jamDistance_->value()));
        extensionNode.addChild(jamNode);
        item->appendRow(propertyRow(string("s0"), tr("mappropertyeditor.group.mobility.jamdist").toUTF8(), boost::lexical_cast<string>(jamDistance_->value())));
    }
    if (safeTimeHeadway_->value() != safeTimeHeadway_->minimum())
    {
        Node tNode("t");
        tNode.value(boost::lexical_cast<string>(safeTimeHeadway_->value()));
        extensionNode.addChild(tNode);
        item->appendRow(propertyRow(string("t"), tr("mappropertyeditor.group.mobility.t").toUTF8(), boost::lexical_cast<string>(safeTimeHeadway_->value())));
    }
    
    Node stepNode("step");
    stepNode.value(boost::lexical_cast<string>(step_->value()));
    extensionNode.addChild(stepNode);
    item->appendRow(propertyRow(string("step"), tr("mappropertyeditor.group.mobility.step").toUTF8(), boost::lexical_cast<string>(step_->value())));
    
    string checkvalue = tr("constant.yes").toUTF8();
    if (stay_->value() != stay_->minimum())
    {
        Node stayNode("stay");
        stayNode.value(boost::lexical_cast<string>(stay_->value()));
        item->appendRow(propertyRow(string("stay"), tr("mappropertyeditor.group.mobility.stay").toUTF8(), boost::lexical_cast<string>(stay_->value())));
        
        Attribute rndAttr("random", "true");
        if (random_->checkState() == Unchecked)
        {
            checkvalue = tr("constant.no").toUTF8();
            rndAttr.value(string("false"));
        }
        stayNode.addAttribute(rndAttr);
        item->appendRow(propertyRow(string("random="), tr("mappropertyeditor.group.mobility.random").toUTF8(), checkvalue));
        extensionNode.addChild(stayNode);
    }
    
    Node ignoreNode("ignoreBorders");
    ignoreNode.value("true");
    checkvalue = tr("constant.yes").toUTF8();
    if (ignoreBorders_->checkState() == Unchecked)
    {
        ignoreNode.value("false");
        checkvalue = tr("constant.no").toUTF8();
    }
    extensionNode.addChild(ignoreNode);
    item->appendRow(propertyRow(string("ignoreBorders"), tr("mappropertyeditor.group.mobility.ignoreborders").toUTF8(), checkvalue));
    
    if (bsave_->isEnabled() && bsave_->value() != bsave_->minimum())
    {
        Node bsaveNode("bsave");
        bsaveNode.value(boost::lexical_cast<string>(bsave_->value()));
        extensionNode.addChild(bsaveNode);
        item->appendRow(propertyRow(string("bsave"), tr("mappropertyeditor.group.mobility.bsave").toUTF8(), boost::lexical_cast<string>(bsave_->value())));
    }
    if (politeness_->isEnabled() && politeness_->value() != politeness_->minimum())
    {
        Node pNode("p");
        pNode.value(boost::lexical_cast<string>(politeness_->value()));
        extensionNode.addChild(pNode);
        item->appendRow(propertyRow(string("p"), tr("mappropertyeditor.group.mobility.p").toUTF8(), boost::lexical_cast<string>(politeness_->value())));
    }
    if (accelThresh_->isEnabled() && accelThresh_->value() != accelThresh_->minimum())
    {
        Node athrNode("athr");
        athrNode.value(boost::lexical_cast<string>(accelThresh_->value()));
        extensionNode.addChild(athrNode);
        item->appendRow(propertyRow(string("athr"), tr("mappropertyeditor.group.mobility.athr").toUTF8(), boost::lexical_cast<string>(accelThresh_->value())));
    }
    nodes.push_back(extensionNode);
}

bool VanetMobilityModelForm::validate(std::vector< std::string >& messages)
{
    if (accelThresh_->isEnabled() &&
        accelThresh_->value() >= maxAccel_->value())
    {
        messages.push_back(tr("vanet.property.form.mobility.error.acceleration").toUTF8());
        return false;
    }
    if (maxSpeed_->value() == 0.0 || minSpeed_->value() == 0.0)
    {
        messages.push_back(tr("vanet.property.form.mobility.error.speed").toUTF8());
        return false;
    }
    return true;
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

void VanetMobilityModelForm::setPreselectedValues(const map< string, boost::any >& values)
{
    map< string, boost::any >::const_iterator it;
    it = values.find("class=");
    if (it != values.end())
    {
        string classString = boost::any_cast<string>(it->second);
        if (classString == string(AbstractPropertyForm::INTERSECTION_MANAGEMENT_MODEL))
        {
            mobilityCombo_->setCurrentIndex(0);
        }
        if (classString == string(AbstractPropertyForm::LANE_CHANGING_MODEL))
        {
            mobilityCombo_->setCurrentIndex(1);
        }
    }
    
    setPreselectedDoubleValue("minspeed", values, minSpeed_);
    setPreselectedDoubleValue("maxspeed", values, maxSpeed_);
    setPreselectedDoubleValue("l", values, length_);
    setPreselectedDoubleValue("a", values, maxAccel_);
    setPreselectedDoubleValue("b", values, comfyDecel_);
    setPreselectedDoubleValue("s0", values, jamDistance_);
    setPreselectedDoubleValue("t", values, safeTimeHeadway_);
    setPreselectedDoubleValue("step", values, step_);
    setPreselectedDoubleValue("stay", values, stay_);
    setPreselectedCheckboxValue("random=", values, random_);
    setPreselectedCheckboxValue("ignoreBorders", values, ignoreBorders_);
    setPreselectedDoubleValue("bsave", values, bsave_);
    setPreselectedDoubleValue("p", values, politeness_);
    setPreselectedDoubleValue("athr", values, accelThresh_);
    
    mobilityChanged(mobilityCombo_->currentIndex());
}
