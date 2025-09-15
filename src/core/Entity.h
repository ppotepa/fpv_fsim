#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.h"
#include <memory>
#include <unordered_map>
#include <typeindex>

/**
 * @brief Represents an entity in the Entity Component System (ECS).
 *
 * An entity is a container for components that define its properties and behavior.
 * Entities are identified by a unique ID and can have multiple components attached
 * to them. The entity itself contains no logic - all behavior is implemented
 * through systems that operate on entities with specific component combinations.
 */
class Entity
{
public:
    /**
     * @brief Construct an entity with a unique identifier.
     *
     * @param id The unique identifier for this entity
     */
    Entity(unsigned int id);

    /**
     * @brief Add a component to this entity.
     *
     * Components define the properties and capabilities of an entity.
     * Each component type can only be added once per entity.
     *
     * @tparam T The type of component to add
     * @param component Unique pointer to the component instance
     */
    template <typename T>
    void addComponent(std::unique_ptr<T> component)
    {
        components_[std::type_index(typeid(T))] = std::move(component);
    }

    /**
     * @brief Get a component from this entity.
     *
     * @tparam T The type of component to retrieve
     * @return Pointer to the component if it exists, nullptr otherwise
     */
    template <typename T>
    T *getComponent()
    {
        auto it = components_.find(std::type_index(typeid(T)));
        if (it != components_.end())
        {
            return static_cast<T *>(it->second.get());
        }
        return nullptr;
    }

private:
    unsigned int id_;                                                             /**< Unique identifier for this entity */
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components_; /**< Map of component types to component instances */
};

#endif
