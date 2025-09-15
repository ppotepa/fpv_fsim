#include "PhysicsSystem.h"
#include "core/World.h"

PhysicsSystem::PhysicsSystem(EventBus &eventBus, IAirDensityModel &airDensityModel, IWindModel &windModel, ICollisionResolver &collisionResolver)
    : eventBus_(eventBus), airDensityModel_(airDensityModel), windModel_(windModel), collisionResolver_(collisionResolver) {}

void PhysicsSystem::update(World &world, float dt)
{
    // Stub: update physics for entities
}
