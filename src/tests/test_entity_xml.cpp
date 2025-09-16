#include <iostream>
#include <memory>
#include "loaders/EntityXmlParser.h"
#include "factory/EntityFactory.h"
#include "core/Entity.h"
#include "components/TransformC.h"
#include "components/RenderableC.h"
#include "components/PhysicsC.h"
#include "components/VehicleC.h"
#include "components/AudioC.h"
#include "components/LightC.h"
#include "../debug.h"

bool testEntityXmlLoading()
{
    if (Debug())
    {
        DEBUG_LOG("Testing XML Entity Loading...");
    }

    // Create parser
    EntityLoader::EntityXmlParser parser;

    // Load test entity
    std::string filePath = "assets/entities/simple_drone.xml";
    std::unique_ptr<EntityConfig::EntityDefinition> definition = parser.loadFromFile(filePath);

    if (!definition)
    {
        std::cerr << "Failed to load entity definition from " << filePath << std::endl;
        return false;
    }

    // Check basic entity properties
    if (Debug())
    {
        DEBUG_LOG("Entity: " << definition->name);
        DEBUG_LOG("Type: " << definition->entityType);
    }

    // Create entity using EntityFactory
    EntityFactory factory;
    std::unique_ptr<Entity> entity = factory.createFromDefinition(*definition);

    if (!entity)
    {
        std::cerr << "Failed to create entity from definition" << std::endl;
        return false;
    }

    // Verify components
    if (Debug())
    {
        DEBUG_LOG("Verifying entity components...");
    }

    // Transform component
    auto transform = entity->getComponent<TransformC>();
    if (!transform)
    {
        std::cerr << "Entity has no transform component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Transform: pos(" << transform->position.x << ", "
                  << transform->position.y << ", "
                  << transform->position.z << ")");
    }

    // Renderable component
    auto renderable = entity->getComponent<RenderableC>();
    if (!renderable)
    {
        std::cerr << "Entity has no renderable component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Renderable: mesh=" << renderable->meshId
                  << ", material=" << renderable->materialId);
    }

    // Physics component
    auto physics = entity->getComponent<PhysicsC>();
    if (!physics)
    {
        std::cerr << "Entity has no physics component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Physics: mass=" << physics->mass
                  << ", collider=" << physics->colliderType);
    }

    // Vehicle component
    auto vehicle = entity->getComponent<VehicleC>();
    if (!vehicle)
    {
        std::cerr << "Entity has no vehicle component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Vehicle: type=" << vehicle->vehicleType
                  << ", speed=" << vehicle->maxSpeed);
    }

    // Audio component
    auto audio = entity->getComponent<AudioC>();
    if (!audio)
    {
        std::cerr << "Entity has no audio component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Audio: sound=" << audio->soundId);
    }

    // Light component
    auto light = entity->getComponent<LightC>();
    if (!light)
    {
        std::cerr << "Entity has no light component" << std::endl;
        return false;
    }
    if (Debug())
    {
        DEBUG_LOG("Light: type=" << light->lightType
                  << ", intensity=" << light->intensity);

        DEBUG_LOG("All entity components verified successfully!");
    }
    return true;
}

int main()
{
    if (testEntityXmlLoading())
    {
        if (Debug())
        {
            DEBUG_LOG("XML Entity Loading Test: PASSED");
        }
        return 0;
    }
    else
    {
        std::cerr << "XML Entity Loading Test: FAILED" << std::endl;
        return 1;
    }
}


