#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "physics/IAirDensityModel.h"
#include "physics/IWindModel.h"
#include "physics/ICollisionResolver.h"

class PhysicsSystem : public ISystem
{
public:
    PhysicsSystem(EventBus &eventBus, IAirDensityModel &airDensityModel, IWindModel &windModel, ICollisionResolver &collisionResolver);
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
    IAirDensityModel &airDensityModel_;
    IWindModel &windModel_;
    ICollisionResolver &collisionResolver_;
};

#endif
