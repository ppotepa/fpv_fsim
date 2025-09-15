#ifndef ISYSTEM_H
#define ISYSTEM_H

class World;

/**
 * @brief Base interface for all systems in the Entity Component System (ECS).
 *
 * Systems contain the logic that operates on entities and their components.
 * Each system is updated every frame with the current world state and delta time.
 */
class ISystem
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived systems.
     */
    virtual ~ISystem() = default;

    /**
     * @brief Update the system with the current world state.
     *
     * This method is called once per frame for each system, allowing it to
     * process entities, update components, and perform game logic.
     *
     * @param world Reference to the world containing all entities and systems.
     * @param dt Time elapsed since the last update in seconds.
     */
    virtual void update(World &world, float dt) = 0;
};

#endif
