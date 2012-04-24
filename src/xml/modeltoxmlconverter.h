#ifndef MODELTOXMLCONVERTER_H
#define MODELTOXMLCONVERTER_H

#include <pugixml/pugixml.hpp>

namespace Wt
{
    class WStandardItemModel;
}

// namespace pugi
// {
//     class xml_document;
//     class xml_node;
// }

class ModelToXmlConverter
{

public:
    ModelToXmlConverter(Wt::WStandardItemModel* model);
    void validate();
private:
    void convertXml();
    
    Wt::WStandardItemModel* model_;
    pugi::xml_document doc_;
    pugi::xml_node root_;
};

#endif // MODELTOXMLCONVERTER_H
