#include <vector>
#include <string>

#include <Wt/WStandardItem>
#include <Wt/WLineEdit>
#include <Wt/WDoubleSpinBox>
#include <Wt/WSpinBox>
#include <Wt/WCheckBox>
#include <boost/concept_check.hpp>

#include "logger.h"
#include "abstractpropertyform.h"

using namespace Wt;
using namespace std;
    
const char* const AbstractPropertyForm::LANE_CHANGING_MODEL = "polito.uomm.IDM_LC";
const char* const AbstractPropertyForm::INTERSECTION_MANAGEMENT_MODEL = "polito.uomm.IDM_IM";


std::vector<WStandardItem *> AbstractPropertyForm::propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue)
{
    std::vector<WStandardItem *> propertyItems;
    WStandardItem *item;

    // tree column 0: property name
    item = new WStandardItem(propertyName);
    propertyItems.push_back(item);

    // tree column 1: property value
    item = new WStandardItem(propertyValue);
    propertyItems.push_back(item);
    
    // tree column 2: property id (hidden column)
    item = new WStandardItem(propertyId);
    propertyItems.push_back(item);

    return propertyItems;
}


void AbstractPropertyForm::setPreselectedDoubleValue(const char* key, const map < string, boost::any >& values, WDoubleSpinBox* spinBox)
{
    map< string, boost::any >::const_iterator it;
    it = values.find(string(key));
    if (it != values.end())
    {
        spinBox->setValue(boost::lexical_cast< double >(boost::any_cast< string >(it->second)));
        Logger::entry("info") << "Adding preselected value " << boost::any_cast< string >(it->second) << " for key " << key;
    }
    else
    {
        Logger::entry("info") << "No value was found in the map for key " << key;
    }
}

void AbstractPropertyForm::setPreselectedCheckboxValue(const char* key, const map< string, boost::any >& values, WCheckBox* checkBox)
{
    map< string, boost::any >::const_iterator it;
    it = values.find(string(key));
    if (it != values.end())
    {
        string checkvalue = boost::any_cast< string >(it->second);
        if (checkvalue == tr("constant.yes").toUTF8())
        {
            checkBox->setCheckState(Checked);
        }
        else
        {
            checkBox->setCheckState(Unchecked);
        }
        Logger::entry("info") << "Adding preselected value " << boost::any_cast< string >(it->second) << " for key " << key;
    }
    else
    {
        Logger::entry("info") << "No value was found in the map for key " << key;
    }
}

void AbstractPropertyForm::setPreselectedIntegerValue(const char* key, const std::map< std::string, boost::any >& values, WSpinBox* spinBox)
{
    map< string, boost::any >::const_iterator it;
    it = values.find(string(key));
    if (it != values.end())
    {
        spinBox->setValue(boost::lexical_cast< int >(boost::any_cast< string >(it->second)));
        Logger::entry("info") << "Adding preselected value " << boost::any_cast< string >(it->second) << " for key " << key;
    }
    else
    {
        Logger::entry("info") << "No value was found in the map for key " << key;
    }
}

void AbstractPropertyForm::setPreselectedLineValue(const char* key, const std::map< std::string, boost::any >& values, WLineEdit* lineEdit)
{
    map< string, boost::any >::const_iterator it;
    it = values.find(string(key));
    if (it != values.end())
    {
        lineEdit->setValueText(WString::fromUTF8(boost::any_cast< string >(it->second)));
        Logger::entry("info") << "Adding preselected value " << boost::any_cast< string >(it->second) << " for key " << key;
    }
    else
    {
        Logger::entry("info") << "No value was found in the map for key " << key;
    }
}

