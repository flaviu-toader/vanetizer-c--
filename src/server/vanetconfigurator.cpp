#include <string>

#include "vanetconfigurator.h"
#include "xml/modeltoxmlconverter.h"

using namespace std;
using namespace pugi;

VanetConfigurator::VanetConfigurator(const Node& modelNode)
{
    ModelToXmlConverter converter(modelNode);
    string xml = converter.convert();
    doc_.load(xml.c_str());
}

void VanetConfigurator::save()
{
    doc_.save_file("scenario.xml");
}
