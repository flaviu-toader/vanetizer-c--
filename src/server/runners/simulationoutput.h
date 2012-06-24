#ifndef SIMULATIONOUTPUT_H
#define SIMULATIONOUTPUT_H

#include <string>

class SimulationOutput
{
public:
    SimulationOutput();
    //! Get the VanetMobiSim command line output.
    std::string vmsCommandLineOutput() const;
    //! Set the VanetMobiSim command line output. Normally should only be called by the runner.
    void vmsCommandLineOutput(const std::string& out);
    //! Get the VanetMobiSim output from the nodes.input file.
    std::string vmsNodesInputFileContents();
    //! Get the VanetMobiSim output from the mobility.in file. Big string.
    std::string vmsMobilityInFileContents();

    //! Get the GloMoSim command line output.
    std::string gmsCommandLineOutput() const;
    //! Set the GloMoSim command line output. Normally should only be called by the runner.
    void gmsCommandLineOutput(const std::string& out);
    //! Get the GloMoSim command line output from the glomo.stat file.
    std::string gmsGlomoStatFileContents();

private:
    std::string fileContents(const std::string& filename);
    //! VanetMobiSim command line output.
    std::string vmsClout_;
    //! GloMoSim command line output.
    std::string gmsClout_;
};

#endif // SIMULATIONOUTPUT_H
