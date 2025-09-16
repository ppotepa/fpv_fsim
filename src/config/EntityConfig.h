#ifndef ENTITY_CONFIG_H
#define ENTITY_CONFIG_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace EntityConfig
{

    // Basic transform data structures
    struct Vec3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Vec4
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 1.0f;
    };

    /**
     * @brief 3D position and rotation structure
     */
    struct Transform
    {
        Vec3 position;
        Vec4 rotation; // Quaternion 
        Vec3 scale{1.0f, 1.0f, 1.0f};

        Transform() = default;
    };

    /**
     * @brief Renderable component configuration
     */
    struct RenderableComponent
    {
        std::string meshId;
        std::string materialId;
        bool isVisible = true;
        float opacity = 1.0f;
        int renderLayer = 0;
    };

    /**
     * @brief Physics component configuration
     */
    struct PhysicsComponent
    {
        bool hasPhysics = true;
        float mass = 1.0f;
        float friction = 0.5f;
        float restitution = 0.3f;
        float colliderSize[3] = {1.0f, 1.0f, 1.0f};
        bool isKinematic = false;
        bool useGravity = true;
        std::string colliderType = "sphere";
    };

    /**
     * @brief Audio component configuration
     */
    struct AudioComponent
    {
        std::string soundId;
        float volume = 1.0f;
        bool loop = false;
    };

    /**
     * @brief Vehicle control component configuration
     */
    struct VehicleComponent
    {
        std::string vehicleType = "drone";
        float maxSpeed = 100.0f;
        float acceleration = 10.0f;
        float maneuverability = 5.0f;
        std::string controllerType = "manual";
    };

    /**
     * @brief Light component configuration
     */
    struct LightComponent
    {
        std::string lightType = "point";
        float color[3] = {1.0f, 1.0f, 1.0f};
        float intensity = 1.0f;
        float range = 10.0f;
    };

    /**
     * @brief Custom property for extensibility
     */
    struct CustomProperty
    {
        std::string name;
        std::string type;
        std::string value;
    };

    /**
     * @brief Complete entity configuration
     */
    struct EntityDefinition
    {
        std::string entityType;
        std::string name;
        std::string description;
        bool startActive = true;
        float lifetime = -1.0f;
        
        Transform transform;

        // Component pointers - parser creates these dynamically
        std::unique_ptr<RenderableComponent> renderable;
        std::unique_ptr<PhysicsComponent> physics;
        std::unique_ptr<AudioComponent> audio;
        std::unique_ptr<VehicleComponent> vehicle;
        std::unique_ptr<LightComponent> light;

        // Custom properties for extensibility
        std::vector<CustomProperty> customProperties;
    };

    /**
     * @brief Entity template configuration
     */
    struct EntityTemplate
    {
        std::string templateId;
        std::string category;
        std::string name;
        std::string description;
        EntityDefinition defaultDefinition;
    };

    /**
     * @brief Entity factory configuration
     */
    struct EntityFactoryConfiguration
    {
        bool validateComponents = true;
        bool logCreation = false;
        bool enablePooling = false;
        int maxPoolSize = 100;
        std::vector<EntityTemplate> templates;
        std::unordered_map<std::string, std::string> materialMappings;
        std::unordered_map<std::string, std::string> meshMappings;
        std::unordered_map<std::string, std::string> audioclipMappings;
    };

} // namespace EntityConfig

#endif // ENTITY_CONFIG_H
