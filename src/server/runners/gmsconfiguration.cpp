#include "gmsconfiguration.h"

#include <Wt/WString>
#include <Wt/WTemplate>

#include "templatefile.h"

using namespace std;

GmsConfiguration::GmsConfiguration()
{
    protocolMap_.insert(make_pair<string, string>(
        Wt::WString::tr("vanet.property.form.routing.combo.aodv").toUTF8(), "AODV"));
    protocolMap_.insert(make_pair<string, string>(
        Wt::WString::tr("vanet.property.form.routing.combo.bf").toUTF8(), "BELLMANFORD"));
    protocolMap_.insert(make_pair<string, string>(
        Wt::WString::tr("vanet.property.form.routing.combo.dsr").toUTF8(), "DSR"));
    protocolMap_.insert(make_pair<string, string>(
        Wt::WString::tr("vanet.property.form.routing.combo.lar").toUTF8(), "LAR1"));
    protocolMap_.insert(make_pair<string, string>(
        Wt::WString::tr("vanet.property.form.routing.combo.wrp").toUTF8(), "WRP"));
    
    // default value for simulation time is 10 minutes.
    simtime_ = "10M";
}

void GmsConfiguration::toFile()
{
    TemplateFile t = TemplateFile(string(GMSCONFIG_TEMPLATE_PATH));
    t.replaceString("time", simtime_);
    t.replaceString("dimx", dimx_);
    t.replaceString("dimy", dimy_);
    t.replaceString("nodesnumber", nodecount_);
    t.replaceString("routingprotocol", protocol_);
    t.render(string(GMSCONFIG_PATH));
}


string GmsConfiguration::protocol() const
{
    return protocol_;
}

void GmsConfiguration::protocol(const string& s)
{
    protocol_ = protocolMap_[s];
}

string GmsConfiguration::simulationTime() const
{
    return simtime_;
}

void GmsConfiguration::simulationTime(const string& s)
{
    simtime_ = s.substr(0, s.find(".")) + "S";
}

string GmsConfiguration::dimx() const
{
    return dimx_;
}

void GmsConfiguration::dimx(const string& s)
{
    dimx_ = s;
}

string GmsConfiguration::dimy() const
{
    return dimy_;
}

void GmsConfiguration::dimy(const string& s)
{
    dimy_ = s;
}


string GmsConfiguration::nodeCount() const
{
    return nodecount_;
}

void GmsConfiguration::nodeCount(const string& s)
{
    nodecount_ = s;
}
