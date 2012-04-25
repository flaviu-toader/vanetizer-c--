

#ifndef ABSTRACTPROPERTYFORM_H_
#define ABSTRACTPROPERTYFORM_H_

#include <vector>
#include <string>
#include <boost/any.hpp>

#include <Wt/WContainerWidget>

#include "client/xmlhelper.h"

enum VanetProperty 
{
    VanetNone,                  // 0
    VanetArea,                  // 1
    VanetStep,                  // 2
    VanetSeed,                  // 3
    VanetNode,                  // 4
    VanetNodeGroup,             // 5
    // extensions properties 
    VanetGlomosimOutput,        // 6
    VanetTimeSimulation,        // 7
    VanetSpatialModel,          // 8
    VanetTrafficLights,         // 9
    VanetSpatialModelDump,      // 10
    VanetMobilityTrace,         // 11
    VanetGDFWriter,             // 12
    VanetGDFReader,             // 13
    VanetTIGERReader            // 14
    // end extension properties
};

namespace Wt 
{
    class WStandardItem;
    class WLength;
    class WLineEdit;
    class WDoubleSpinBox;
    class WCheckBox;
    class WSpinBox;
}

class AbstractPropertyForm : public Wt::WContainerWidget
{
public:
    
    //! The constant for the lane changing mobility model.
    static const char* const LANE_CHANGING_MODEL;
    //! The constant for the intersection management mobility model.
    static const char* const INTERSECTION_MANAGEMENT_MODEL;
    
    //! Get the information ready to be added to the model.
    /*!
     * Returns the information held by this form in a model-digestible format (as a WStandardItem).
     * The output parameter nodes contains a vector of xml helper nodes used for conversion to xml of this treeNode.
     */
    virtual Wt::WStandardItem *treeNode(std::vector< Node >& nodes) = 0;
 
    //! Makes special bussiness-related checks on the form.
    /*!
     * This method returns true when from the Vanet point of view the input given in the form is acceptable.
     * It also populates the list of feedback messages.
     */
    virtual bool validate(std::vector< std::string >& messages) = 0;
    
    //! Sets preselected values for the form.
    /*!
     * In case the property dialog is opened via double clicking an already existing root item in the tree view,
     * this method will add in the property form the values that the user previously set to that node,
     * for editing.
     */
    virtual void setPreselectedValues(const std::map< std::string, boost::any > &values) = 0;
    
protected:
    
    //! Get one leaf from the tree view.
    /*! 
     * Returns a list of standard items that make up the leaves of the tree view (the rows that actually contain the relevant information).
     * There are 3 columns in total:
     *  * first column represents the property name
     *  * second column represents the property value
     *  * third column represents a property id (hidden column)
     */
    virtual std::vector<Wt::WStandardItem *> propertyRow(const std::string &propertyId, const std::string &propertyName, const std::string &propertyValue);
    
    //! Set the preselected value for a double spin box.
    virtual void setPreselectedDoubleValue(const char* key, const std::map< std::string, boost::any >& values, Wt::WDoubleSpinBox* spinBox);
    
    //! Set the preselected value for a check box.
    virtual void setPreselectedCheckboxValue(const char* key, const std::map< std::string, boost::any >& values, Wt::WCheckBox* checkBox);
    
    //! Set the preselected value for a line edit.
    virtual void setPreselectedLineValue(const char* key, const std::map< std::string, boost::any >& values, Wt::WLineEdit* lineEdit);
    
    //! Set the preselected value for a spin box;
    virtual void setPreselectedIntegerValue(const char* key, const std::map< std::string, boost::any >& values, Wt::WSpinBox* spinBox);
};


#endif // ABSTRACTPROPERTYFORM_H_
