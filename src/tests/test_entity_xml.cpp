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
        std::cout << "Testing XML Entity Loading..." << std::endl;
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
        std::cout << "Entity: " << definition->name << std::endl;
        std::cout << "Type: " << definition->entityType << std::endl;
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
        std::cout << "Verifying entity components..." << std::endl;
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
        std::cout << "Transform: pos(" << transform->position.x << ", "
                  << transform->position.y << ", "
                  << transform->position.z << ")" << std::endl;
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
        std::cout << "Renderable: mesh=" << renderable->meshId
                  << ", material=" << renderable->materialId << std::endl;
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
        std::cout << "Physics: mass=" << physics->mass
                  << ", collider=" << physics->colliderType << std::endl;
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
        std::cout << "Vehicle: type=" << vehicle->vehicleType
                  << ", speed=" << vehicle->maxSpeed << std::endl;
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
        std::cout << "Audio: sound=" << audio->soundId << std::endl;
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
        std::cout << "Light: type=" << light->lightType
                  << ", intensity=" << light->intensity << std::endl;

        std::cout << "All entity components verified successfully!" << std::endl;
    }
    return true;
}

int main()
{
    if (testEntityXmlLoading())
    {
        if (Debug())
        {
            std::cout << "XML Entity Loading Test: PASSED" << std::endl;
        }
        return 0;
    }
    else
    {
        std::cerr << "XML Entity Loading Test: FAILED" << std::endl;
        return 1;
    }
}
