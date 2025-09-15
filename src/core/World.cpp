#include "World.h"

/**
 * @brief Construct a world with an event bus for communication.
 *
 * Initializes the world with a reference to the event bus that will be used
 * for inter-system communication throughout the simulation.
 *
 * @param eventBus Reference to the event bus used for inter-system communication
 */
World::World(EventBus &eventBus) : eventBus_(eventBus) {}

/**
 * @brief Add an entity to the world.
 *
 * The world takes ownership of the entity through the unique pointer,
 * ensuring proper memory management and lifetime control.
 *
 * @param entity Unique pointer to the entity to add
 */
void World::addEntity(std::unique_ptr<Entity> entity)
{
    entities_.push_back(std::move(entity));
}

/**
 * @brief Add a system to the world.
 *
 * Systems are stored in the order they are added and will be updated
 * in that same order during the world's update cycle.
 *
 * @param system Unique pointer to the system to add
 */
void World::addSystem(std::unique_ptr<ISystem> system)
{
    systems_.push_back(std::move(system));
}

/**
 * @brief Update all systems in the world.
 *
 * Iterates through all registered systems and calls their update methods,
 * passing the world reference and delta time. This is the main simulation
 * loop that drives all game logic.
 *
 * @param dt Time elapsed since the last update in seconds
 */
void World::update(float dt)
{
    for (auto &system : systems_)
    {
        system->update(*this, dt);
    }
}
