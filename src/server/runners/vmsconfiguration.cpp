#include "vmsconfiguration.h"

using namespace std;

VmsConfiguration::VmsConfiguration():
    xml_("")
{
}

string VmsConfiguration::xml() const
{
    return xml_;
}

void VmsConfiguration::xml(const string& xml)
{
    xml_ = xml;
}

void VmsConfiguration::toFile()
{
    if (!xml_.empty())
    {

    }
}

