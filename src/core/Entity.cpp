#include "Entity.h"
#include "../components/TransformC.h"
#include "../components/RenderableC.h"
#include "../components/PhysicsC.h"
#include "../components/VehicleC.h"
#include "../components/AudioC.h"
#include "../components/LightC.h"
#include "Vector3D.h"
#include "Quaternion.h"

/**
 * @brief Construct an entity with a unique identifier.
 *
 * Initializes the entity with the provided ID and prepares the component storage.
 *
 * @param id The unique identifier for this entity
 */
Entity::Entity(unsigned int id) : id_(id) {}

/**
 * @brief Set the entity's position.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 */
void Entity::setPosition(float x, float y, float z)
{
    auto transform = getComponent<TransformC>();

    if (!transform)
    {
        auto newTransform = std::make_unique<TransformC>();
        newTransform->position = Vector3D(x, y, z);
        addComponent<TransformC>(std::move(newTransform));
    }
    else
    {
        transform->position = Vector3D(x, y, z);
    }
}

/**
 * @brief Set the entity's rotation.
 *
 * @param pitch Pitch in radians
 * @param yaw Yaw in radians
 * @param roll Roll in radians
 */
void Entity::setRotation(float pitch, float yaw, float roll)
{
    auto transform = getComponent<TransformC>();

    if (!transform)
    {
        auto newTransform = std::make_unique<TransformC>();
        newTransform->rotation = Quaternion::fromEulerAngles(pitch, yaw, roll);
        addComponent<TransformC>(std::move(newTransform));
    }
    else
    {
        transform->rotation = Quaternion::fromEulerAngles(pitch, yaw, roll);
    }
}

/**
 * @brief Set the entity's scale.
 *
 * @param x X scale
 * @param y Y scale
 * @param z Z scale
 */
void Entity::setScale(float x, float y, float z)
{
    auto transform = getComponent<TransformC>();

    if (!transform)
    {
        auto newTransform = std::make_unique<TransformC>();
        newTransform->scale = Vector3D(x, y, z);
        addComponent<TransformC>(std::move(newTransform));
    }
    else
    {
        transform->scale = Vector3D(x, y, z);
    }
}

/**
 * @brief Set renderable component properties.
 *
 * @param meshId ID of the mesh to use
 * @param materialId ID of the material to use
 * @param visible Whether the entity is visible
 */
void Entity::setRenderableComponent(const std::string &meshId, const std::string &materialId, bool visible)
{
    auto renderable = getComponent<RenderableC>();

    if (!renderable)
    {
        auto newRenderable = std::make_unique<RenderableC>(meshId, materialId, visible);
        addComponent<RenderableC>(std::move(newRenderable));
    }
    else
    {
        renderable->meshId = meshId;
        renderable->materialId = materialId;
        renderable->isVisible = visible;
    }
}

/**
 * @brief Set physics component properties.
 *
 * @param hasPhysics Whether the entity has physics
 * @param mass Entity mass
 * @param friction Entity friction
 * @param restitution Entity restitution (bounciness)
 */
void Entity::setPhysicsComponent(bool hasPhysics, float mass, float friction, float restitution)
{
    if (!hasPhysics)
    {
        // If physics is disabled, remove the component if it exists
        components_.erase(std::type_index(typeid(PhysicsC)));
        return;
    }

    auto physics = getComponent<PhysicsC>();

    if (!physics)
    {
        auto newPhysics = std::make_unique<PhysicsC>(mass, friction, restitution);
        addComponent<PhysicsC>(std::move(newPhysics));
    }
    else
    {
        physics->mass = mass;
        physics->friction = friction;
        physics->restitution = restitution;
    }
}

/**
 * @brief Set collider type for physics.
 *
 * @param colliderType Type of collider ("sphere", "box", etc.)
 */
void Entity::setColliderType(const std::string &colliderType)
{
    auto physics = getComponent<PhysicsC>();

    if (!physics)
    {
        auto newPhysics = std::make_unique<PhysicsC>();
        newPhysics->colliderType = colliderType;
        addComponent<PhysicsC>(std::move(newPhysics));
    }
    else
    {
        physics->colliderType = colliderType;
    }
}

/**
 * @brief Set collider size for physics.
 *
 * @param x X size
 * @param y Y size
 * @param z Z size
 */
void Entity::setColliderSize(float x, float y, float z)
{
    auto physics = getComponent<PhysicsC>();

    if (!physics)
    {
        auto newPhysics = std::make_unique<PhysicsC>();
        newPhysics->colliderSize[0] = x;
        newPhysics->colliderSize[1] = y;
        newPhysics->colliderSize[2] = z;
        addComponent<PhysicsC>(std::move(newPhysics));
    }
    else
    {
        physics->colliderSize[0] = x;
        physics->colliderSize[1] = y;
        physics->colliderSize[2] = z;
    }
}

/**
 * @brief Set whether the entity is kinematic.
 *
 * @param isKinematic True if the entity is kinematic, false otherwise
 */
void Entity::setKinematic(bool isKinematic)
{
    auto physics = getComponent<PhysicsC>();

    if (!physics)
    {
        auto newPhysics = std::make_unique<PhysicsC>();
        newPhysics->isKinematic = isKinematic;
        addComponent<PhysicsC>(std::move(newPhysics));
    }
    else
    {
        physics->isKinematic = isKinematic;
    }
}

/**
 * @brief Set whether the entity uses gravity.
 *
 * @param useGravity True if the entity uses gravity, false otherwise
 */
void Entity::setUseGravity(bool useGravity)
{
    auto physics = getComponent<PhysicsC>();

    if (!physics)
    {
        auto newPhysics = std::make_unique<PhysicsC>();
        newPhysics->useGravity = useGravity;
        addComponent<PhysicsC>(std::move(newPhysics));
    }
    else
    {
        physics->useGravity = useGravity;
    }
}

/**
 * @brief Set vehicle component properties.
 *
 * @param vehicleType Type of vehicle
 * @param maxSpeed Maximum speed
 * @param acceleration Acceleration
 */
void Entity::setVehicleComponent(const std::string &vehicleType, float maxSpeed, float acceleration)
{
    auto vehicle = getComponent<VehicleC>();

    if (!vehicle)
    {
        auto newVehicle = std::make_unique<VehicleC>(vehicleType, maxSpeed, acceleration);
        addComponent<VehicleC>(std::move(newVehicle));
    }
    else
    {
        vehicle->vehicleType = vehicleType;
        vehicle->maxSpeed = maxSpeed;
        vehicle->acceleration = acceleration;
    }
}

/**
 * @brief Set audio component properties.
 *
 * @param soundId ID of the sound to play
 * @param volume Volume level
 * @param loop Whether to loop the sound
 */
void Entity::setAudioComponent(const std::string &soundId, float volume, bool loop)
{
    auto audio = getComponent<AudioC>();

    if (!audio)
    {
        auto newAudio = std::make_unique<AudioC>(soundId, volume, loop);
        addComponent<AudioC>(std::move(newAudio));
    }
    else
    {
        audio->soundId = soundId;
        audio->volume = volume;
        audio->loop = loop;
    }
}

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
void Entity::setLightComponent(const std::string &lightType, float r, float g, float b, float intensity, float range)
{
    auto light = getComponent<LightC>();

    if (!light)
    {
        auto newLight = std::make_unique<LightC>(lightType, r, g, b, intensity, range);
        addComponent<LightC>(std::move(newLight));
    }
    else
    {
        light->lightType = lightType;
        light->color[0] = r;
        light->color[1] = g;
        light->color[2] = b;
        light->intensity = intensity;
        light->range = range;
    }
}

/**
 * @brief Set a custom property on the entity.
 *
 * @param name Property name
 * @param value Property value
 */
void Entity::setCustomProperty(const std::string &name, const std::string &value)
{
    customProperties_[name] = value;
}
