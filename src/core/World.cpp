#include "World.h"

World::World(EventBus &eventBus) : eventBus_(eventBus) {}

void World::addEntity(std::unique_ptr<Entity> entity)
{
    entities_.push_back(std::move(entity));
}

void World::addSystem(std::unique_ptr<ISystem> system)
{
    systems_.push_back(std::move(system));
}

void World::update(float dt)
{
    for (auto &system : systems_)
    {
        system->update(*this, dt);
    }
}
