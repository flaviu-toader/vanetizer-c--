#ifndef GMSCONFIGURATION_H
#define GMSCONFIGURATION_H

#include <map>
#include <string>

#include "abstractconfiguration.h"

class GmsConfiguration : public AbstractConfiguration
{
public:
    GmsConfiguration();
    //! Get the routing protocol string
    std::string protocol() const;
    //! Set the routing protocol string
    void protocol(const std::string& s);
    //! Get the simulation time string
    std::string simulationTime() const;
    //! Set the simulation time string
    void simulationTime(const std::string& s);
    //! Get the map width
    std::string dimx() const;
    //! Set the map width
    void dimx(const std::string& s);
    //! Get the map height
    std::string dimy() const;
    //! Set the map height
    void dimy(const std::string& s);
    //! Get the node count
    std::string nodeCount() const;
    //! Set the node count
    void nodeCount(const std::string& s);
    
    virtual void toFile();
private:
    std::string simtime_, dimx_, dimy_, protocol_, nodecount_;
    
    //! Maps GUI string to configuration file constant string.
    std::map< std::string, std::string > protocolMap_;
};

#endif // GMSCONFIGURATION_H
