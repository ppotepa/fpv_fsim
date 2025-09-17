#ifndef DRONEBUILDER_H
#define DRONEBUILDER_H

#include "IVehicleBuilder.h"
#include "../utils/IJsonQuery.h"
#include <memory>

class DroneBuilder : public IVehicleBuilder
{
public:
    DroneBuilder(std::unique_ptr<IJsonQuery> jsonParser);
    std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) override;

private:
    std::unique_ptr<IJsonQuery> m_jsonParser;
};

#endif
