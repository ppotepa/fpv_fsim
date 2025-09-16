#ifndef DRONEBUILDER_H
#define DRONEBUILDER_H

#include "IVehicleBuilder.h"
#include "utils/IXmlQuery.h"

class DroneBuilder : public IVehicleBuilder
{
public:
    DroneBuilder(IXmlQuery &xmlParser);
    std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) override;

private:
    IXmlQuery &xmlParser_;
};

#endif

