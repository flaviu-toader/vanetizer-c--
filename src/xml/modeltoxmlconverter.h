#ifndef MODELTOXMLCONVERTER_H
#define MODELTOXMLCONVERTER_H

#include <pugixml/pugixml.hpp>
#include "xml/xmlhelper.h"

namespace Wt
{
    class WStandardItemModel;
}

class ModelToXmlConverter
{

public:
    //! Constructor for the converter.
    /*!
     * Receives as parameter the root xml helper node, which is a representation of the WStandardItemModel from the treeview.
     */
    ModelToXmlConverter(Node model);
    
    //! Converts the stored model to xml using the pugixml classes.
    /*!
     * Performs the actual conversion to VanetMobiSim-readable xml. 
     * CAUTION! The xml is not yet validated. It contains the settings for both VanetMobiSim and GloMoSim.
     */
    void convert();
    
    //! Get the converted xml document as a pugi::xml_document object.
    pugi::xml_document document();
private:
    void buildXml(const Node& node, pugi::xml_node& xnode);
    pugi::xml_node appendNode(const Node& node, pugi::xml_node& xnode);
    
    Node model_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
};

#endif // MODELTOXMLCONVERTER_H
