#include <string>

#include <Wt/WString>

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

bool VanetConfigurator::validate(vector< Wt::WString >& validationMessages)
{
    bool isValid = true;
    // check for spatial model
    xml_node spatialModel = doc_.find_child_by_attribute("extension", "class", "de.uni_stuttgart.informatik.canu.spatialmodel.core.SpatialModel");
    if (!spatialModel || spatialModel.empty())
    {
        validationMessages.push_back(Wt::WString::tr("business.validation.error.nospatialmodel"));
        isValid = false;
    }
}

