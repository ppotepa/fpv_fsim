// Add implementation of the addEntityComponents method
#include "debug.h"

void EntityFactory::addEntityComponents(Entity &entity, const EntityConfig::EntityDefinition &definition)
{
    DEBUG_LOG("Adding components to entity " + std::to_string(entity.getId()) + " with definition " + definition.name);
    // Set entity properties
    if (!definition.name.empty())
    {
        entity.setName(definition.name);
    }

    // Set transform properties
    entity.setPosition(definition.transform.position);
    entity.setRotation(definition.transform.rotation);
    entity.setScale(definition.transform.scale);

    // Add renderable component if defined
    if (definition.renderable)
    {
        DEBUG_LOG("Adding renderable component to entity " + std::to_string(entity.getId()));
        auto renderableComp = std::make_shared<RenderableC>();
        renderableComp->meshId = definition.renderable->meshId;
        renderableComp->materialId = definition.renderable->materialId;
        renderableComp->isVisible = definition.renderable->isVisible;
        renderableComp->opacity = definition.renderable->opacity;
        renderableComp->renderLayer = definition.renderable->renderLayer;
        entity.addComponent<RenderableC>(renderableComp);
    }

    // Add physics component if defined
    if (definition.physics)
    {
        DEBUG_LOG("Adding physics component to entity " + std::to_string(entity.getId()));
        auto physicsComp = std::make_shared<PhysicsC>();
        physicsComp->mass = definition.physics->mass;
        physicsComp->friction = definition.physics->friction;
        physicsComp->restitution = definition.physics->restitution;
        physicsComp->isKinematic = definition.physics->isKinematic;
        physicsComp->useGravity = definition.physics->useGravity;
        physicsComp->colliderType = definition.physics->colliderType;

        // Copy collider size
        physicsComp->colliderSize.x = definition.physics->colliderSize[0];
        physicsComp->colliderSize.y = definition.physics->colliderSize[1];
        physicsComp->colliderSize.z = definition.physics->colliderSize[2];

        entity.addComponent<PhysicsC>(physicsComp);
    }

    // Add vehicle component if defined
    if (definition.vehicle)
    {
        DEBUG_LOG("Adding vehicle component to entity " + std::to_string(entity.getId()));
        auto vehicleComp = std::make_shared<VehicleC>();
        vehicleComp->vehicleType = definition.vehicle->vehicleType;
        vehicleComp->maxSpeed = definition.vehicle->maxSpeed;
        vehicleComp->acceleration = definition.vehicle->acceleration;
        vehicleComp->maneuverability = definition.vehicle->maneuverability;
        vehicleComp->controllerType = definition.vehicle->controllerType;
        entity.addComponent<VehicleC>(vehicleComp);
    }

    // Add audio component if defined
    if (definition.audio)
    {
        DEBUG_LOG("Adding audio component to entity " + std::to_string(entity.getId()));
        auto audioComp = std::make_shared<AudioC>();
        audioComp->soundId = definition.audio->soundId;
        audioComp->volume = definition.audio->volume;
        audioComp->loop = definition.audio->loop;
        entity.addComponent<AudioC>(audioComp);
    }

    // Add light component if defined
    if (definition.light)
    {
        DEBUG_LOG("Adding light component to entity " + std::to_string(entity.getId()));
        auto lightComp = std::make_shared<LightC>();
        lightComp->lightType = definition.light->lightType;
        lightComp->color = definition.light->color;
        lightComp->intensity = definition.light->intensity;
        lightComp->range = definition.light->range;
        entity.addComponent<LightC>(lightComp);
    }

    // Process custom properties
    for (const auto &prop : definition.customProperties)
    {
        entity.setCustomProperty(prop.name, prop.value);
    }
}

