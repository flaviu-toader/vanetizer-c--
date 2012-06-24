#include <stdio.h>

#include "gmsconfiguration.h"
#include "vmsconfiguration.h"
#include "simulationoutput.h"
#include "logger.h"

#include "simulationrunner.h"

using namespace std;

SimulationRunner::SimulationRunner(VmsConfiguration vmsCfg, GmsConfiguration gmsCfg):
    vmsCfg_(vmsCfg),
    gmsCfg_(gmsCfg)
{
}

string SimulationRunner::executeCommand(const std::string& command)
{
    FILE* f = popen(command.c_str(), "r");
    if (f == 0)
    {
        Logger::entry("error") << "Could not execute command " << command;
        throw std::exception();
    }

    char buf[1000];
    string result = "";
    while (fgets(buf, sizeof(buf), f))
    {
        result += string(buf);
    }
    pclose(f);
    return result;
}

SimulationOutput SimulationRunner::runSimulation()
{
    vmsCfg_.toFile();
    gmsCfg_.toFile();
    SimulationOutput result;

    Logger::entry("info") << "Running VanetMobiSim...";
    string vmsOut = executeCommand("java -jar VanetMobiSim-1.1.jar scenario.xml");
    result.vmsCommandLineOutput(vmsOut);

    Logger::entry("info") << "Running GloMoSim...";
    string gmsOut = executeCommand("./glomosim config.in");
    result.gmsCommandLineOutput(gmsOut);

    return result;
}
