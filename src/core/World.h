#ifndef WORLD_H
#define WORLD_H

#include "EventBus.h"
#include "ISystem.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

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
     * @brief Get mutable access to all systems in the world.
     *
     * @return Reference to the vector of systems
     */
    std::vector<std::unique_ptr<ISystem>> &getSystems() { return systems_; }

    /**
     * @brief Get a system of a specific type from the world.
     *
     * This method searches for the first system of the specified type T
     * and returns a pointer to it. This provides type-safe system access
     * without relying on magic indices.
     *
     * @tparam T The system type to search for
     * @return Pointer to the system of type T, or nullptr if not found
     */
    template <typename T>
    T *getSystem()
    {
        for (auto &system : systems_)
        {
            T *typedSystem = dynamic_cast<T *>(system.get());
            if (typedSystem != nullptr)
            {
                return typedSystem;
            }
        }
        return nullptr;
    }

    /**
     * @brief Get read-only access to all entities in the world.
     *
     * @return Const reference to the vector of entities
     */
    const std::vector<std::unique_ptr<Entity>> &getEntities() const { return entities_; }

    /**
     * @brief Store a shared resource with the given name
     *
     * This allows storing and retrieving shared resources that need to be accessed
     * by multiple systems but aren't systems themselves, such as asset managers.
     *
     * @tparam T The type of the resource
     * @param name Unique name for the resource
     * @param resource The resource to store
     */
    template <typename T>
    void storeSharedResource(const std::string &name, std::unique_ptr<T> resource)
    {
        // Create a custom deleter that will properly delete the derived type
        auto deleter = [](void *ptr)
        {
            T *typedPtr = static_cast<T *>(ptr);
            delete typedPtr;
        };

        // Store the resource with its custom deleter
        void *rawPtr = resource.release();
        sharedResources_[name] = std::unique_ptr<void, std::function<void(void *)>>(rawPtr, deleter);
    }

    /**
     * @brief Get a shared resource by name
     *
     * @param name The name of the resource to retrieve
     * @return void* Pointer to the resource, or nullptr if not found
     */
    void *getSharedResource(const std::string &name)
    {
        auto it = sharedResources_.find(name);
        if (it != sharedResources_.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

private:
    EventBus &eventBus_;                                                                                  /**< Reference to the event bus for communication */
    std::vector<std::unique_ptr<Entity>> entities_;                                                       /**< All entities in the world */
    std::vector<std::unique_ptr<ISystem>> systems_;                                                       /**< All systems in the world, updated in order */
    std::unordered_map<std::string, std::unique_ptr<void, std::function<void(void *)>>> sharedResources_; /**< Named shared resources */
};

#endif
