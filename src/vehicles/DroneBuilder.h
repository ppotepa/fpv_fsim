#ifndef DRONEBUILDER_H
#define DRONEBUILDER_H

#include "IVehicleBuilder.h"
#include "utils/IXmlParser.h"

class DroneBuilder : public IVehicleBuilder {
public:
    DroneBuilder(IXmlParser& xmlParser);
    std::unique_ptr<Entity> build(const std::string& configPath, EventBus& eventBus) override;
private:
    IXmlParser& xmlParser_;
};

#endif
