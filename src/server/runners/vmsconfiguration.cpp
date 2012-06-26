#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

#include "vmsconfiguration.h"
#include "logger.h"

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
    boost::regex e("(nodegroup) (id=\".*?\")");
    xml_ = regex_replace(xml, e, "\\1", boost::match_default | boost::format_sed);
}

void VmsConfiguration::toFile()
{
    if (!xml_.empty())
    {
        ofstream outfile(VMSCONFIG_PATH);
        if (outfile.is_open())
        {
            outfile << xml_;
            outfile.close();
        }
        else
        {
            Logger::entry("error") << "Unable to open output file " << VMSCONFIG_PATH;
        }
    }
}

