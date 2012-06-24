#include <string>
#include <iostream>
#include <fstream>

#include "simulationoutput.h"
#include "logger.h"

using namespace std;

SimulationOutput::SimulationOutput():
    vmsClout_(""),
    gmsClout_("")
{
}

void SimulationOutput::vmsCommandLineOutput(const string& out)
{
    vmsClout_ = out;
}

void SimulationOutput::gmsCommandLineOutput(const string& out)
{
    gmsClout_ = out;
}

string SimulationOutput::vmsCommandLineOutput() const
{
    return vmsClout_;
}

string SimulationOutput::gmsCommandLineOutput() const
{
    return gmsClout_;
}

string SimulationOutput::fileContents(const string& filename)
{
    ifstream inputfile(filename.c_str());
    if (inputfile.is_open())
    {
        stringstream ss;
        ss << inputfile.rdbuf();
        inputfile.close();
        return ss.str();
    }
    else
    {
        Logger::entry("error") << "Unable to open the output file " << filename;
        return "";
    }
}

string SimulationOutput::vmsNodesInputFileContents()
{
    return fileContents("nodes.input");
}

string SimulationOutput::vmsMobilityInFileContents()
{
    return fileContents("mobility.in");
}

string SimulationOutput::gmsGlomoStatFileContents()
{
    return fileContents("glomo.stat");
}
