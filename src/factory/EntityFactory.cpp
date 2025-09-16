#include "EntityFactory.h"
#include "systems/MaterialManager.h"
#include "core/Entity.h"
#include "core/EventBus.h"
#include "core/Vector3D.h"
#include "core/Quaternion.h"
#include "loaders/EntityXmlParser.h"
#include "config/EntityConfigParser.h"
#include "components/RenderableC.h"
#include "components/PhysicsC.h"
#include "components/VehicleC.h"
#include "components/AudioC.h"
#include "components/LightC.h"
#include <iostream>

namespace EntityFactory
{

    EntityFactory::EntityFactory(EventBus &eventBus, Material::MaterialManager &materialManager)
        : eventBus_(eventBus), materialManager_(materialManager), nextEntityId_(1)
    {
        initializeDefaultTemplates();
    }

    bool EntityFactory::loadConfiguration(const std::string &configFilePath)
    {
        // Load entity factory configuration
        std::cout << "EntityFactory: Loading configuration from " << configFilePath << std::endl;

        EntityConfig::EntityFactoryConfiguration config =
            EntityConfig::EntityConfigParser::loadFromFile(configFilePath);

        // Store entity templates
        entityTemplates_ = std::move(config.templates);

        // Store any simple name-value templates for backward compatibility
        for (const auto &entityTemplate : entityTemplates_)
        {
            templates_[entityTemplate.templateId] = entityTemplate.name;
        }

        return true;
    }

    std::unique_ptr<Entity> EntityFactory::createFromTemplate(const std::string &templateName,
                                                              const std::string &entityName,
                                                              unsigned int entityId)
    {
        if (entityId == 0)
        {
            entityId = getNextEntityId();
        }

        // Create basic entity
        auto entity = std::make_unique<Entity>(entityId);

        std::cout << "EntityFactory: Creating entity '" << entityName
                  << "' from template '" << templateName << "' with ID " << entityId << std::endl;

        // Find template in loaded templates
        for (const auto &entityTemplate : entityTemplates_)
        {
            if (entityTemplate.templateId == templateName)
            {
                // Create a copy of the template's default definition
                EntityConfig::EntityDefinition definition;

                // Copy basic properties
                definition.entityType = entityTemplate.defaultDefinition.entityType;
                definition.name = entityTemplate.defaultDefinition.name;
                definition.description = entityTemplate.defaultDefinition.description;
                definition.startActive = entityTemplate.defaultDefinition.startActive;
                definition.lifetime = entityTemplate.defaultDefinition.lifetime;
                definition.transform = entityTemplate.defaultDefinition.transform;
                definition.customProperties = entityTemplate.defaultDefinition.customProperties;

                // Copy component pointers (deep copy)
                if (entityTemplate.defaultDefinition.renderable)
                {
                    definition.renderable = std::make_unique<EntityConfig::RenderableComponent>(*entityTemplate.defaultDefinition.renderable);
                }

                if (entityTemplate.defaultDefinition.physics)
                {
                    definition.physics = std::make_unique<EntityConfig::PhysicsComponent>(*entityTemplate.defaultDefinition.physics);
                }

                if (entityTemplate.defaultDefinition.audio)
                {
                    definition.audio = std::make_unique<EntityConfig::AudioComponent>(*entityTemplate.defaultDefinition.audio);
                }

                if (entityTemplate.defaultDefinition.vehicle)
                {
                    definition.vehicle = std::make_unique<EntityConfig::VehicleComponent>(*entityTemplate.defaultDefinition.vehicle);
                }

                if (entityTemplate.defaultDefinition.light)
                {
                    definition.light = std::make_unique<EntityConfig::LightComponent>(*entityTemplate.defaultDefinition.light);
                }

                // Override the name if provided
                if (!entityName.empty())
                {
                    definition.name = entityName;
                }

                // Add components based on the definition
                addEntityComponents(*entity, definition);

                return entity;
            }
        }

        // If template not found, create a basic entity as fallback
        std::cout << "Warning: Template '" << templateName << "' not found, creating basic entity" << std::endl;
        return entity;
    }

    std::unique_ptr<Entity> EntityFactory::createFromXmlFile(const std::string &xmlFilePath, unsigned int entityId)
    {
        EntityLoader::EntityXmlParser parser;
        auto entityDef = parser.loadFromFile(xmlFilePath);

        if (!entityDef)
        {
            std::cerr << "Failed to load entity from XML file: " << xmlFilePath << std::endl;
            return nullptr;
        }

        return createFromDefinition(*entityDef, entityId);
    }

    std::unique_ptr<Entity> EntityFactory::createFromDefinition(
        const EntityConfig::EntityDefinition &definition, unsigned int entityId)
    {

        if (entityId == 0)
        {
            entityId = getNextEntityId();
        }

        // Create basic entity
        auto entity = std::make_unique<Entity>(entityId);

        std::cout << "EntityFactory: Creating entity '" << definition.name
                  << "' of type '" << definition.entityType << "' with ID " << entityId << std::endl;

        // Add components based on the definition
        addEntityComponents(*entity, definition);

        return entity;
    }

    void EntityFactory::initializeDefaultTemplates()
    {
        // Initialize basic templates
        templates_["earth_sphere"] = "basic_sphere";
        templates_["basic_drone"] = "aircraft";
        templates_["cloud_object"] = "cloud";

        // Create some default entity templates
        EntityConfig::EntityTemplate earthTemplate;
        earthTemplate.templateId = "earth_sphere";
        earthTemplate.name = "Earth";
        earthTemplate.category = "environment";
        earthTemplate.description = "Basic spherical planet";

        // Set up default definition for earth template
        earthTemplate.defaultDefinition.entityType = "sphere";
        earthTemplate.defaultDefinition.name = "Earth";
        earthTemplate.defaultDefinition.transform.scale = {1.0f, 1.0f, 1.0f};

        // Add a renderable component
        auto renderable = std::make_unique<EntityConfig::RenderableComponent>();
        renderable->meshId = "sphere";
        renderable->materialId = "earth";
        earthTemplate.defaultDefinition.renderable = std::move(renderable);

        // Add the template
        entityTemplates_.push_back(std::move(earthTemplate));

        // Create drone template
        EntityConfig::EntityTemplate droneTemplate;
        droneTemplate.templateId = "basic_drone";
        droneTemplate.name = "Drone";
        droneTemplate.category = "vehicle";
        droneTemplate.description = "Basic quadcopter drone";

        droneTemplate.defaultDefinition.entityType = "drone";
        droneTemplate.defaultDefinition.name = "Drone";

        // Add a vehicle component
        auto vehicle = std::make_unique<EntityConfig::VehicleComponent>();
        vehicle->vehicleType = "drone";
        vehicle->maxSpeed = 20.0f;
        droneTemplate.defaultDefinition.vehicle = std::move(vehicle);

        // Add the template
        entityTemplates_.push_back(std::move(droneTemplate));

        // Create cloud template
        EntityConfig::EntityTemplate cloudTemplate;
        cloudTemplate.templateId = "cloud_object";
        cloudTemplate.name = "Cloud";
        cloudTemplate.category = "environment";
        cloudTemplate.description = "Atmospheric cloud";

        cloudTemplate.defaultDefinition.entityType = "cloud";
        cloudTemplate.defaultDefinition.name = "Cloud";
    }

    void EntityFactory::addEntityComponents(Entity &entity, const EntityConfig::EntityDefinition &definition)
    {
        // Set entity properties
        if (!definition.name.empty())
        {
            entity.setName(definition.name);
        }

        // Set transform properties
        // Convert from EntityConfig::Vec3 to Vector3D
        Vector3D position(
            definition.transform.position.x,
            definition.transform.position.y,
            definition.transform.position.z);
        entity.setPosition(position.x, position.y, position.z);

        // Convert quaternion to Euler angles
        float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;

        // Only convert if not identity quaternion
        if (definition.transform.rotation.w != 1.0f)
        {
            yaw = std::atan2(2.0f * (definition.transform.rotation.y * definition.transform.rotation.z +
                                     definition.transform.rotation.w * definition.transform.rotation.x),
                             definition.transform.rotation.w * definition.transform.rotation.w -
                                 definition.transform.rotation.x * definition.transform.rotation.x -
                                 definition.transform.rotation.y * definition.transform.rotation.y +
                                 definition.transform.rotation.z * definition.transform.rotation.z);

            pitch = std::asin(-2.0f * (definition.transform.rotation.x * definition.transform.rotation.z -
                                       definition.transform.rotation.w * definition.transform.rotation.y));

            roll = std::atan2(2.0f * (definition.transform.rotation.x * definition.transform.rotation.y +
                                      definition.transform.rotation.w * definition.transform.rotation.z),
                              definition.transform.rotation.w * definition.transform.rotation.w +
                                  definition.transform.rotation.x * definition.transform.rotation.x -
                                  definition.transform.rotation.y * definition.transform.rotation.y -
                                  definition.transform.rotation.z * definition.transform.rotation.z);
        }

        entity.setRotation(pitch, yaw, roll);

        // Convert from EntityConfig::Vec3 to Vector3D
        Vector3D scale(
            definition.transform.scale.x,
            definition.transform.scale.y,
            definition.transform.scale.z);
        entity.setScale(scale.x, scale.y, scale.z);

        // Add renderable component if defined
        if (definition.renderable)
        {
            auto renderableComp = std::make_unique<RenderableC>();
            renderableComp->meshId = definition.renderable->meshId;
            renderableComp->materialId = definition.renderable->materialId;
            renderableComp->isVisible = definition.renderable->isVisible;
            entity.addComponent<RenderableC>(std::move(renderableComp));
        }

        // Add physics component if defined
        if (definition.physics)
        {
            auto physicsComp = std::make_unique<PhysicsC>();
            physicsComp->mass = definition.physics->mass;
            physicsComp->friction = definition.physics->friction;
            physicsComp->restitution = definition.physics->restitution;
            physicsComp->isKinematic = definition.physics->isKinematic;
            physicsComp->useGravity = definition.physics->useGravity;
            physicsComp->colliderType = definition.physics->colliderType;

            // Copy collider size
            physicsComp->colliderSize[0] = definition.physics->colliderSize[0];
            physicsComp->colliderSize[1] = definition.physics->colliderSize[1];
            physicsComp->colliderSize[2] = definition.physics->colliderSize[2];

            entity.addComponent<PhysicsC>(std::move(physicsComp));
        }

        // Add vehicle component if defined
        if (definition.vehicle)
        {
            auto vehicleComp = std::make_unique<VehicleC>();
            vehicleComp->vehicleType = definition.vehicle->vehicleType;
            vehicleComp->maxSpeed = definition.vehicle->maxSpeed;
            vehicleComp->acceleration = definition.vehicle->acceleration;
            vehicleComp->maneuverability = definition.vehicle->maneuverability;
            vehicleComp->controllerType = definition.vehicle->controllerType;
            entity.addComponent<VehicleC>(std::move(vehicleComp));
        }

        // Add audio component if defined
        if (definition.audio)
        {
            entity.setAudioComponent(definition.audio->soundId, definition.audio->volume, definition.audio->loop);
        }

        // Add light component if defined
        if (definition.light)
        {
            float r = 1.0f, g = 1.0f, b = 1.0f;
            if (definition.light->color[0] > 0)
                r = definition.light->color[0];
            if (definition.light->color[1] > 0)
                g = definition.light->color[1];
            if (definition.light->color[2] > 0)
                b = definition.light->color[2];

            entity.setLightComponent(definition.light->lightType, r, g, b,
                                     definition.light->intensity, definition.light->range);
        }

        // Process custom properties
        for (const auto &prop : definition.customProperties)
        {
            entity.setCustomProperty(prop.name, prop.value);
        }
    }

} // namespace EntityFactory
