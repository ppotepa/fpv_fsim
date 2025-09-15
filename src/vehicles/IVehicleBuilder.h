#ifndef IVEHICLEBUILDER_H
#define IVEHICLEBUILDER_H

#include <memory>
#include <string>
#include "core/Entity.h"
#include "core/EventBus.h"

class IVehicleBuilder {
public:
    virtual ~IVehicleBuilder() = default;
    virtual std::unique_ptr<Entity> build(const std::string& configPath, EventBus& eventBus) = 0;
};

#endif
