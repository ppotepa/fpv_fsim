#ifndef WORLD_H
#define WORLD_H

#include "EventBus.h"
#include "ISystem.h"
#include "Entity.h"
#include <vector>
#include <memory>

/**
 * @brief The central world class that manages all entities and systems in the ECS.
 *
 * The World acts as the container and coordinator for all entities, components,
 * and systems in the simulation. It provides methods to add entities and systems,
 * and coordinates their updates each frame. The World also provides access to
 * the event bus for inter-system communication.
 */
class World
{
public:
    /**
     * @brief Construct a world with an event bus for communication.
     *
     * @param eventBus Reference to the event bus used for inter-system communication
     */
    World(EventBus &eventBus);

    /**
     * @brief Add an entity to the world.
     *
     * The world takes ownership of the entity and will manage its lifetime.
     *
     * @param entity Unique pointer to the entity to add
     */
    void addEntity(std::unique_ptr<Entity> entity);

    /**
     * @brief Add a system to the world.
     *
     * Systems are updated in the order they are added. The world takes
     * ownership of the system and will manage its lifetime.
     *
     * @param system Unique pointer to the system to add
     */
    void addSystem(std::unique_ptr<ISystem> system);

    /**
     * @brief Update all systems in the world.
     *
     * This method iterates through all registered systems and calls their
     * update methods with the current delta time.
     *
     * @param dt Time elapsed since the last update in seconds
     */
    void update(float dt);

    /**
     * @brief Get read-only access to all systems in the world.
     *
     * @return Const reference to the vector of systems
     */
    const std::vector<std::unique_ptr<ISystem>> &getSystems() const { return systems_; }

    /**
     * @brief Get read-only access to all entities in the world.
     *
     * @return Const reference to the vector of entities
     */
    const std::vector<std::unique_ptr<Entity>> &getEntities() const { return entities_; }

private:
    EventBus &eventBus_;                            /**< Reference to the event bus for communication */
    std::vector<std::unique_ptr<Entity>> entities_; /**< All entities in the world */
    std::vector<std::unique_ptr<ISystem>> systems_; /**< All systems in the world, updated in order */
};

#endif
