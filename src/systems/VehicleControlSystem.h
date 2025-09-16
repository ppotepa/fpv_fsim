#ifndef VEHICLECONTROLSYSTEM_H
#define VEHICLECONTROLSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"

class VehicleControlSystem : public ISystem
{
public:
    VehicleControlSystem(EventBus &eventBus);
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
};

#endif

