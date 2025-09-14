#include "World.h"

World::World(EventBus &amp; eventBus) : eventBus_(eventBus) {}

void World::addEntity(std::unique_ptr &lt; Entity & gt; entity)
{
    entities_.push_back(std::move(entity));
}

void World::addSystem(std::unique_ptr &lt; ISystem & gt; system)
{
    systems_.push_back(std::move(system));
}

void World::update(float dt)
{
    for (auto &amp; system : systems_)
    {
        system - &gt;
        update(*this, dt);
    }
}
