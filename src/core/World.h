#ifndef WORLD_H
#define WORLD_H

#include "EventBus.h"
#include "ISystem.h"
#include "Entity.h"
#include <vector>
#include <memory>

class World
{
public:
    World(EventBus &eventBus);
    void addEntity(std::unique_ptr<Entity> entity);
    void addSystem(std::unique_ptr<ISystem> system);
    void update(float dt);

private:
    EventBus &eventBus_;
    std::vector<std::unique_ptr<Entity>> entities_;
    std::vector<std::unique_ptr<ISystem>> systems_;
};

#endif
