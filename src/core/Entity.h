#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.h"
#include <memory>
#include <string>
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
     * @brief Get the unique identifier of this entity.
     *
     * @return The entity's unique ID
     */
    unsigned int getId() const { return id_; }

    /**
     * @brief Set the name of this entity.
     *
     * @param name The name to set for this entity
     */
    void setName(const std::string &name) { name_ = name; }

    /**
     * @brief Get the name of this entity.
     *
     * @return The entity's name
     */
    const std::string &getName() const { return name_; }

    /**
     * @brief Set whether this entity is active.
     *
     * @param active True if the entity should be active, false otherwise
     */
    void setActive(bool active) { active_ = active; }

    /**
     * @brief Check if this entity is active.
     *
     * @return True if the entity is active, false otherwise
     */
    bool isActive() const { return active_; }

    /**
     * @brief Set the entity's position.
     *
     * @param x X coordinate
     * @param y Y coordinate
     * @param z Z coordinate
     */
    void setPosition(float x, float y, float z);

    /**
     * @brief Set the entity's rotation.
     *
     * @param pitch Pitch in radians
     * @param yaw Yaw in radians
     * @param roll Roll in radians
     */
    void setRotation(float pitch, float yaw, float roll);

    /**
     * @brief Set the entity's scale.
     *
     * @param x X scale
     * @param y Y scale
     * @param z Z scale
     */
    void setScale(float x, float y, float z);

    /**
     * @brief Set renderable component properties.
     *
     * @param meshId ID of the mesh to use
     * @param materialId ID of the material to use
     * @param visible Whether the entity is visible
     */
    void setRenderableComponent(const std::string &meshId, const std::string &materialId, bool visible);

    /**
     * @brief Set physics component properties.
     *
     * @param hasPhysics Whether the entity has physics
     * @param mass Entity mass
     * @param friction Entity friction
     * @param restitution Entity restitution (bounciness)
     */
    void setPhysicsComponent(bool hasPhysics, float mass, float friction, float restitution);

    /**
     * @brief Set collider type for physics.
     *
     * @param colliderType Type of collider ("sphere", "box", etc.)
     */
    void setColliderType(const std::string &colliderType);

    /**
     * @brief Set collider size for physics.
     *
     * @param x X size
     * @param y Y size
     * @param z Z size
     */
    void setColliderSize(float x, float y, float z);

    /**
     * @brief Set whether the entity is kinematic.
     *
     * @param isKinematic True if the entity is kinematic, false otherwise
     */
    void setKinematic(bool isKinematic);

    /**
     * @brief Set whether the entity uses gravity.
     *
     * @param useGravity True if the entity uses gravity, false otherwise
     */
    void setUseGravity(bool useGravity);

    /**
     * @brief Set vehicle component properties.
     *
     * @param vehicleType Type of vehicle
     * @param maxSpeed Maximum speed
     * @param acceleration Acceleration
     */
    void setVehicleComponent(const std::string &vehicleType, float maxSpeed, float acceleration);

    /**
     * @brief Set audio component properties.
     *
     * @param soundId ID of the sound to play
     * @param volume Volume level
     * @param loop Whether to loop the sound
     */
    void setAudioComponent(const std::string &soundId, float volume, bool loop);

    /**
     * @brief Set light component properties.
     *
     * @param lightType Type of light
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     * @param intensity Light intensity
     * @param range Light range
     */
    void setLightComponent(const std::string &lightType, float r, float g, float b, float intensity, float range);

    /**
     * @brief Set a custom property on the entity.
     *
     * @param name Property name
     * @param value Property value
     */
    void setCustomProperty(const std::string &name, const std::string &value);

    /**
     * @brief Set the lifetime of this entity.
     *
     * @param lifetime Lifetime in seconds, -1 for infinite
     */
    void setLifetime(float lifetime) { lifetime_ = lifetime; }

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
    std::string name_;                                                            /**< Entity name */
    bool active_ = true;                                                          /**< Whether the entity is active */
    float lifetime_ = -1.0f;                                                      /**< Entity lifetime in seconds, -1 for infinite */
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components_; /**< Map of component types to component instances */
    std::unordered_map<std::string, std::string> customProperties_;               /**< Custom entity properties */
};

#endif
