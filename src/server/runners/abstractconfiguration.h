#ifndef ABSTRACTCONFIGURATION_H
#define ABSTRACTCONFIGURATION_H

class AbstractConfiguration
{
public:
    //! The path to the GloMoSim config.in template.
    static const char* const GMSCONFIG_TEMPLATE_PATH;
    //! The path of the GloMoSim config.in file.
    static const char* const GMSCONFIG_PATH;
    //! The path of the VanetMobiSim scenario.xml file.
    static const char* const VMSCONFIG_PATH;
    
    virtual void toFile() = 0;
};

#endif // ABSTRACTCONFIGURATION_H
