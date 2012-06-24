#ifndef SIMULATIONRUNNER_H
#define SIMULATIONRUNNER_H

#include <string>

class VmsConfiguration;
class GmsConfiguration;
class SimulationOutput;

class SimulationRunner 
{
public:
    SimulationRunner(VmsConfiguration vmsCfg, GmsConfiguration gmsCfg);
    SimulationOutput runSimulation();
private:
    std::string executeCommand(const std::string& command);

    VmsConfiguration vmsCfg_;
    GmsConfiguration gmsCfg_;
};

#endif // SIMULATIONRUNNER_H
