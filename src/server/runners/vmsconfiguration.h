#ifndef VMSCONFIGURATION_H
#define VMSCONFIGURATION_H

#include <string>
#include "abstractconfiguration.h"

class VmsConfiguration : public AbstractConfiguration
{
public:
    VmsConfiguration();
    std::string xml() const;
    void xml(const std::string& xml);
    virtual void toFile();
private:
    std::string xml_;
};

#endif // VMSCONFIGURATION_H
