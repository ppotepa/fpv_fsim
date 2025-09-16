void EntityFactory::addEntityComponents(Entity &entity, const EntityConfig::EntityDefinition &definition)
{
    // Set entity basic properties
    entity.setName(definition.name);
    entity.setActive(definition.startActive);

    // Set transform component
    entity.setPosition(definition.transform.position.x,
                       definition.transform.position.y,
                       definition.transform.position.z);

    // Convert quaternion to euler angles for now (simplified)
    // In a real implementation, you'd maintain the quaternion rotation
    float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
    // Simple conversion, not accurate for all cases
    // This would be replaced with proper quaternion to euler conversion
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
    entity.setScale(definition.transform.scale.x,
                    definition.transform.scale.y,
                    definition.transform.scale.z);

    // Add renderable component if defined
    if (definition.renderable)
    {
        entity.setRenderableComponent(
            definition.renderable->meshId,
            definition.renderable->materialId,
            definition.renderable->isVisible);

        // Set additional renderable properties if available
        // This would use additional Entity methods that would need to be implemented
        // entity.setOpacity(definition.renderable->opacity);
        // entity.setRenderLayer(definition.renderable->renderLayer);
    }

    // Add physics component if defined
    if (definition.physics)
    {
        entity.setPhysicsComponent(
            definition.physics->hasPhysics,
            definition.physics->mass,
            definition.physics->friction,
            definition.physics->restitution);

        // Set additional physics properties
        entity.setColliderType(definition.physics->colliderType);
        entity.setColliderSize(
            definition.physics->colliderSize[0],
            definition.physics->colliderSize[1],
            definition.physics->colliderSize[2]);
        entity.setKinematic(definition.physics->isKinematic);
        entity.setUseGravity(definition.physics->useGravity);
    }

    // Add vehicle component if defined
    if (definition.vehicle)
    {
        entity.setVehicleComponent(
            definition.vehicle->vehicleType,
            definition.vehicle->maxSpeed,
            definition.vehicle->acceleration);

        // Set additional vehicle properties
        // entity.setManeuverability(definition.vehicle->maneuverability);
        // entity.setControllerType(definition.vehicle->controllerType);
    }

    // Add audio component if defined
    if (definition.audio)
    {
        entity.setAudioComponent(
            definition.audio->soundId,
            definition.audio->volume,
            definition.audio->loop);
    }

    // Add light component if defined
    if (definition.light)
    {
        entity.setLightComponent(
            definition.light->lightType,
            definition.light->color[0],
            definition.light->color[1],
            definition.light->color[2],
            definition.light->intensity,
            definition.light->range);
    }

    // Add custom properties
    for (const auto &property : definition.customProperties)
    {
        entity.setCustomProperty(property.name, property.value);
    }

    // Set lifetime if defined (non-negative)
    if (definition.lifetime >= 0.0f)
    {
        entity.setLifetime(definition.lifetime);
    }
}
