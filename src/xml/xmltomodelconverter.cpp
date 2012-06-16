#include <string>
#include <list>
#include <pugixml.hpp>

#include "xml/xmltomodelconverter.h"
#include "logger.h"

Node XmlToModelConverter::imageNode(const std::string& imageXml)
{
    Node result = Node("extension");
    pugi::xml_document doc;
    pugi::xml_parse_result parseResult = doc.load(imageXml.c_str());
    if (parseResult)
    {
        Logger::entry("info") << "Pugixml successfully loaded the image xml.";
        for (pugi::xml_node_iterator it = doc.first_child().children().begin(); it != doc.first_child().children().end(); ++it)
        {
            Node n = Node(it->name());
            for (pugi::xml_node_iterator sit = it->children().begin(); sit != it->children().end(); ++sit)
            {
                Node child = Node(sit->name());
                child.value(std::string(sit->first_child().value()));
                n.addChild(child);
            }
            result.addChild(n);
        }
    } 
    else
    {
        Logger::entry("error") << "Pugixml parse error!";
        throw std::exception();
    }
    return result;
}
