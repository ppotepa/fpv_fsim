#ifndef WORLD_H
#define WORLD_H

#include "EventBus.h"
#include "ISystem.h"
#include "Entity.h"
#include &lt; vector & gt;
#include &lt; memory & gt;

class World
{
public:
    World(EventBus &amp; eventBus);
    void addEntity(std::unique_ptr &lt; Entity & gt; entity);
    void addSystem(std::unique_ptr &lt; ISystem & gt; system);
    void update(float dt);

private:
    EventBus &amp;
    eventBus_;
    std::vector &lt;
    std::unique_ptr &lt;
    Entity &gt;
    &gt;
    entities_;
    std::vector &lt;
    std::unique_ptr &lt;
    ISystem &gt;
    &gt;
    systems_;
};

#endif
