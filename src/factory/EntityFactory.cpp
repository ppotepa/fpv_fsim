#include "EntityFactory.h"
#include "core/Entity.h"
#include "core/EventBus.h"
#include "systems/MaterialManager.h"
#include "../config/EntityConfigParser.h"
#include <iostream>

namespace EntityFactory
{

EntityFactory::EntityFactory(EventBus &eventBus, Material::MaterialManager &materialManager)
    : eventBus_(eventBus), materialManager_(materialManager), nextEntityId_(1)
{
}

bool EntityFactory::loadConfiguration(const std::string &configFilePath)
{
    try
    {
        // Load configuration using EntityConfigParser
        config_ = EntityConfig::EntityConfigParser::loadFromFile(configFilePath);

        // Clear existing templates and reload
        templates_.clear();
        for (const auto &templateDef : config_.templates)
        {
            templates_[templateDef.templateId] = templateDef;
        }

        std::cout << "EntityFactory: Loaded " << templates_.size() << " entity templates from " << configFilePath << std::endl;

        if (config_.logCreation)
        {
            std::cout << "EntityFactory: Entity creation logging enabled" << std::endl;
        }

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "EntityFactory: Failed to load configuration from " << configFilePath << ": " << e.what() << std::endl;
        return loadDefaultConfiguration();
    }
}

bool EntityFactory::loadDefaultConfiguration()
{
    config_ = EntityConfig::EntityFactoryConfiguration{};

    // Create default drone template
    EntityConfig::EntityTemplate droneTemplate;
    droneTemplate.templateId = "basic_drone";
    droneTemplate.category = "vehicle";
    droneTemplate.name = "FPV Drone";
    droneTemplate.description = "Basic FPV racing drone";
    droneTemplate.defaultDefinition.entityType = "vehicle";
    droneTemplate.defaultDefinition.name = "FPV Drone";
    droneTemplate.defaultDefinition.transform = EntityConfig::Transform{
        {0.0f, 10.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    
    // Create components as unique_ptr
    droneTemplate.defaultDefinition.renderable = std::make_unique<EntityConfig::RenderableComponent>();
    droneTemplate.defaultDefinition.renderable->meshId = "drone_mesh";
    droneTemplate.defaultDefinition.renderable->materialId = "drone_material";
    droneTemplate.defaultDefinition.renderable->isVisible = true;
    
    droneTemplate.defaultDefinition.physics = std::make_unique<EntityConfig::PhysicsComponent>();
    droneTemplate.defaultDefinition.physics->mass = 1.5f;
    droneTemplate.defaultDefinition.physics->colliderSize[0] = 1.0f;
    droneTemplate.defaultDefinition.physics->colliderSize[1] = 0.5f;
    droneTemplate.defaultDefinition.physics->colliderSize[2] = 1.0f;
    droneTemplate.defaultDefinition.physics->useGravity = true;
    droneTemplate.defaultDefinition.physics->isKinematic = false;
    
    droneTemplate.defaultDefinition.vehicle = std::make_unique<EntityConfig::VehicleComponent>();
    droneTemplate.defaultDefinition.vehicle->vehicleType = "quadcopter";
    droneTemplate.defaultDefinition.vehicle->maxSpeed = 100.0f;
    droneTemplate.defaultDefinition.vehicle->acceleration = 15.0f;

    templates_[droneTemplate.templateId] = std::move(droneTemplate);

    // Create default earth template
    EntityConfig::EntityTemplate earthTemplate;
    earthTemplate.templateId = "earth_sphere";
    earthTemplate.category = "environment";
    earthTemplate.name = "Earth";
    earthTemplate.description = "Planet Earth sphere";
    earthTemplate.defaultDefinition.entityType = "environment";
    earthTemplate.defaultDefinition.name = "Earth";
    earthTemplate.defaultDefinition.transform = EntityConfig::Transform{
        {0.0f, -50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {50.0f, 50.0f, 50.0f}};
    
    earthTemplate.defaultDefinition.renderable = std::make_unique<EntityConfig::RenderableComponent>();
    earthTemplate.defaultDefinition.renderable->meshId = "sphere_mesh";
    earthTemplate.defaultDefinition.renderable->materialId = "earth_material";
    earthTemplate.defaultDefinition.renderable->isVisible = true;

    templates_[earthTemplate.templateId] = std::move(earthTemplate);

    std::cout << "EntityFactory: Using default configuration with " << templates_.size() << " templates" << std::endl;
    return true;
}

std::unique_ptr<::Entity> EntityFactory::createFromTemplate(const std::string &templateId,
                                                            const std::string &entityName,
                                                            unsigned int entityId)
{
    auto templateIt = templates_.find(templateId);
    if (templateIt == templates_.end())
    {
        std::cerr << "EntityFactory: Template '" << templateId << "' not found" << std::endl;
        return nullptr;
    }

    // Get template definition and create copy for modification
    EntityConfig::EntityDefinition definition = templateIt->second.defaultDefinition;

    // Override name if provided
    if (!entityName.empty())
    {
        definition.name = entityName;
    }

    return createFromDefinition(definition);
}

std::unique_ptr<::Entity> EntityFactory::createFromDefinition(const EntityConfig::EntityDefinition &definition)
{
    // Create entity with next available ID
    unsigned int entityId = nextEntityId_++;
    auto entity = std::make_unique<::Entity>(entityId, definition.name);

    // Create all components
    createComponents(entity.get(), definition);

    // Log creation if enabled
    if (config_.logCreation)
    {
        logEntityCreation(definition);
    }

    return entity;
}

std::vector<std::unique_ptr<::Entity>> EntityFactory::createFromFile(const std::string &entityFilePath)
{
    // TODO: Implement XML file parsing for multiple entities
    std::cout << "Warning: EntityFactory::createFromFile not yet implemented for " << entityFilePath << std::endl;
    return {};
}

void EntityFactory::registerCustomComponentFactory(const std::string &componentType,
                                                   std::function<std::unique_ptr<IComponent>(const EntityConfig::CustomProperty &)> factory)
{
    customComponentFactories_[componentType] = factory;
}

std::vector<std::string> EntityFactory::getAvailableTemplates() const
{
    std::vector<std::string> templateIds;
    for (const auto &pair : templates_)
    {
        templateIds.push_back(pair.first);
    }
    return templateIds;
}

const EntityConfig::EntityTemplate *EntityFactory::getTemplate(const std::string &templateId) const
{
    auto it = templates_.find(templateId);
    return it != templates_.end() ? &it->second : nullptr;
}

bool EntityFactory::validateDefinition(const EntityConfig::EntityDefinition &definition) const
{
    // Basic validation
    if (definition.name.empty())
    {
        std::cerr << "EntityFactory: Entity definition missing name" << std::endl;
        return false;
    }

    // Validate renderable component
    if (definition.renderable && definition.renderable->meshId.empty())
    {
        std::cerr << "EntityFactory: Renderable component missing mesh ID" << std::endl;
        return false;
    }

    return true;
}

void EntityFactory::createComponents(::Entity *entity, const EntityConfig::EntityDefinition &definition)
{
    // Always create transform component
    createTransformComponent(entity, definition.transform);

    // Create optional components based on presence
    if (definition.renderable)
    {
        createRenderableComponent(entity, *definition.renderable);
    }

    if (definition.physics)
    {
        createPhysicsComponent(entity, *definition.physics);
    }

    if (definition.audio)
    {
        createAudioComponent(entity, *definition.audio);
    }

    if (definition.vehicle)
    {
        createVehicleComponent(entity, *definition.vehicle);
    }

    if (definition.light)
    {
        createLightComponent(entity, *definition.light);
    }

    // Create custom components
    if (!definition.customProperties.empty())
    {
        createCustomComponents(entity, definition.customProperties);
    }
}

void EntityFactory::createTransformComponent(::Entity *entity, const EntityConfig::Transform &transform)
{
    // TODO: Create actual TransformComponent - for now just log
    std::cout << "Creating TransformComponent for entity " << entity->getId() 
              << " at position (" << transform.position[0] << ", " << transform.position[1] << ", " << transform.position[2] << ")" << std::endl;
}

void EntityFactory::createRenderableComponent(::Entity *entity, const EntityConfig::RenderableComponent &renderable)
{
    // TODO: Create actual RenderableComponent with MaterialManager integration
    std::cout << "Creating RenderableComponent for entity " << entity->getId() 
              << " with mesh '" << renderable.meshId << "' and material '" << renderable.materialId << "'" << std::endl;
}

void EntityFactory::createPhysicsComponent(::Entity *entity, const EntityConfig::PhysicsComponent &physics)
{
    // TODO: Create actual PhysicsComponent
    std::cout << "Creating PhysicsComponent for entity " << entity->getId() 
              << " with mass " << physics.mass << std::endl;
}

void EntityFactory::createAudioComponent(::Entity *entity, const EntityConfig::AudioComponent &audio)
{
    // TODO: Create actual AudioComponent
    std::cout << "Creating AudioComponent for entity " << entity->getId() 
              << " with sound '" << audio.soundId << "'" << std::endl;
}

void EntityFactory::createVehicleComponent(::Entity *entity, const EntityConfig::VehicleComponent &vehicle)
{
    // TODO: Create actual VehicleComponent
    std::cout << "Creating VehicleComponent for entity " << entity->getId() 
              << " of type '" << vehicle.vehicleType << "'" << std::endl;
}

void EntityFactory::createLightComponent(::Entity *entity, const EntityConfig::LightComponent &light)
{
    // TODO: Create actual LightComponent
    std::cout << "Creating LightComponent for entity " << entity->getId() 
              << " of type '" << light.lightType << "'" << std::endl;
}

void EntityFactory::createCustomComponents(::Entity *entity, const std::vector<EntityConfig::CustomProperty> &properties)
{
    for (const auto &property : properties)
    {
        auto factoryIt = customComponentFactories_.find(property.name);
        if (factoryIt != customComponentFactories_.end())
        {
            auto component = factoryIt->second(property);
            if (component)
            {
                // TODO: Add component to entity when component system is ready
                std::cout << "Created custom component '" << property.name << "' for entity " << entity->getId() << std::endl;
            }
        }
        else
        {
            std::cout << "Warning: No factory registered for custom component '" << property.name << "'" << std::endl;
        }
    }
}

EntityConfig::EntityDefinition EntityFactory::applyOverrides(const EntityConfig::EntityDefinition &baseDefinition,
                                                             const std::unordered_map<std::string, std::string> &overrides) const
{
    EntityConfig::EntityDefinition result = baseDefinition;

    for (const auto &override : overrides)
    {
        parseProperty(override.first, override.second, result);
    }

    return result;
}

EntityConfig::EntityDefinition EntityFactory::resolveTemplate(const std::string &templateId) const
{
    auto templateIt = templates_.find(templateId);
    if (templateIt == templates_.end())
    {
        throw std::runtime_error("Template not found: " + templateId);
    }

    return templateIt->second.defaultDefinition;
}

void EntityFactory::parseProperty(const std::string &propertyPath, const std::string &value, EntityConfig::EntityDefinition &definition) const
{
    // Simple property override parsing - could be extended for nested properties
    if (propertyPath == "name")
    {
        definition.name = value;
    }
    else if (propertyPath == "transform.position.x")
    {
        definition.transform.position[0] = std::stof(value);
    }
    else if (propertyPath == "transform.position.y")
    {
        definition.transform.position[1] = std::stof(value);
    }
    else if (propertyPath == "transform.position.z")
    {
        definition.transform.position[2] = std::stof(value);
    }
    else if (propertyPath == "renderable.meshId")
    {
        if (!definition.renderable) definition.renderable = std::make_unique<EntityConfig::RenderableComponent>();
        definition.renderable->meshId = value;
    }
    else if (propertyPath == "renderable.materialId")
    {
        if (!definition.renderable) definition.renderable = std::make_unique<EntityConfig::RenderableComponent>();
        definition.renderable->materialId = value;
    }
    else
    {
        std::cout << "Warning: Unknown property path '" << propertyPath << "' for override" << std::endl;
    }
}

void EntityFactory::logEntityCreation(const EntityConfig::EntityDefinition &definition) const
{
    std::cout << "EntityFactory: Created entity '" << definition.name << "' with components:";
    
    if (definition.renderable) std::cout << " Renderable";
    if (definition.physics) std::cout << " Physics";
    if (definition.audio) std::cout << " Audio";
    if (definition.vehicle) std::cout << " Vehicle";
    if (definition.light) std::cout << " Light";
    if (!definition.customProperties.empty()) std::cout << " Custom(" << definition.customProperties.size() << ")";
    
    std::cout << std::endl;
}

} // namespace EntityFactory
