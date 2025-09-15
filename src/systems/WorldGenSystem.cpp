#include "WorldGenSystem.h"
#include "core/Entity.h"
#include "core/Vector3D.h"
#include "core/Quaternion.h"
#include <iostream>
#include <cmath>
#include <memory>

// Component definitions
#include "../core/IComponent.h"

struct TransformC : public IComponent
{
    struct Vector3
    {
        float x, y, z;
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    };

    struct Quaternion
    {
        float x, y, z, w;
        Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
        static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }
    };

    Vector3 position;
    Quaternion orientation;
    Vector3 scale;

    TransformC(Vector3 pos = Vector3(), Quaternion rot = Quaternion::Identity(), Vector3 scl = Vector3(1, 1, 1))
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

WorldGenSystem::WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), defaultWorldGenerated(false)
{
    // Subscribe to no packages found event
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    // Subscribe to default world generated event (when we have XML configuration)
    eventBus.subscribe(EventType::DefaultWorldGenerated, [this](const IEvent &event)
                       {
        const auto& worldEvent = static_cast<const DefaultWorldGeneratedEvent&>(event);
        OnDefaultWorldRequested(worldEvent); });
}

void WorldGenSystem::update(World &world, float deltaTime)
{
    // World generation is event-driven, no continuous updates needed
}

void WorldGenSystem::GenerateDefaultSphereWorld()
{
    if (defaultWorldGenerated)
        return;

    std::cout << "Generating default Earth-like sphere world..." << std::endl;

    // Create the main Earth sphere entity
    static unsigned int nextEntityId = 1;
    auto earthEntity = std::make_unique<Entity>(nextEntityId++);
    earthEntity->addComponent(std::make_unique<TransformC>(TransformC::Vector3(0.0f, 0.0f, 0.0f), TransformC::Quaternion::Identity(), TransformC::Vector3(1.0f, 1.0f, 1.0f)));
    earthEntity->addComponent(std::make_unique<RenderableC>(GenerateProceduralSphereMesh(6371.0f, 32), GetEarthMaterialId(), true));

    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere layers
    for (int i = 0; i < 3; ++i)
    {
        float radius = 6371.0f + (i + 1) * 50.0f; // Increasing radius for each layer
        auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
        atmosphereEntity->addComponent(std::make_unique<TransformC>(TransformC::Vector3(0.0f, 0.0f, 0.0f), TransformC::Quaternion::Identity(), TransformC::Vector3(1.0f, 1.0f, 1.0f)));
        atmosphereEntity->addComponent(std::make_unique<RenderableC>(GenerateProceduralSphereMesh(radius, 32), GetAtmosphereMaterialId(i), true));

        worldRef.addEntity(std::move(atmosphereEntity));
    }

    // Create cloud layer
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(TransformC::Vector3(0.0f, 0.0f, 0.0f), TransformC::Quaternion::Identity(), TransformC::Vector3(1.0f, 1.0f, 1.0f)));
    cloudEntity->addComponent(std::make_unique<RenderableC>(GenerateProceduralSphereMesh(6371.0f + 10.0f, 32), GetCloudMaterialId(), true));

    worldRef.addEntity(std::move(cloudEntity));

    defaultWorldGenerated = true;

    // Publish event that default world was generated
    eventBus.publish(DefaultWorldGeneratedEvent{});

    std::cout << "Default world generation complete." << std::endl;
}

AssetId WorldGenSystem::GenerateProceduralSphereMesh(float radius, int segments)
{
    // TODO: Implement procedural sphere mesh generation
    // For now, return a placeholder ID
    static int nextId = 1000;
    return "sphere_mesh_" + std::to_string(nextId++);
}

AssetId WorldGenSystem::GetEarthMaterialId()
{
    // TODO: Return proper Earth material ID from asset registry
    // For now, return a placeholder ID
    return "earth_material";
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    // TODO: Return proper atmosphere material IDs from asset registry
    // For now, return placeholder IDs
    return "atmosphere_material_" + std::to_string(layer);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    // TODO: Return proper cloud material ID from asset registry
    // For now, return a placeholder ID
    return "cloud_material";
}

void WorldGenSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)
{
    if (defaultWorldGenerated)
        return;

    // Get the default scene configuration from the asset registry
    const std::string *sceneConfig = assetRegistry_.getDefaultScene();
    if (sceneConfig != nullptr)
    {
        std::cout << "Generating world from XML scene configuration..." << std::endl;
        GenerateWorldFromXMLScene(*sceneConfig);
    }
    else
    {
        std::cout << "No scene configuration found, falling back to default generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

void WorldGenSystem::GenerateWorldFromXMLScene(const std::string &sceneXml)
{
    if (defaultWorldGenerated)
        return;

    std::cout << "Parsing XML scene configuration for Earth-like world..." << std::endl;

    // Parse entities from the XML scene configuration
    // Look for Earth entity
    if (sceneXml.find("name=\"Earth\"") != std::string::npos)
    {
        std::cout << "Creating Earth entity from XML configuration..." << std::endl;
        static unsigned int nextEntityId = 1;
        auto earthEntity = std::make_unique<Entity>(nextEntityId++);
        earthEntity->addComponent(std::make_unique<TransformC>(
            TransformC::Vector3(0.0f, -6371000.0f, 0.0f), // Earth center at -6371km as specified in XML
            TransformC::Quaternion::Identity(), 
            TransformC::Vector3(6371000.0f, 6371000.0f, 6371000.0f))); // Earth scale from XML
        earthEntity->addComponent(std::make_unique<RenderableC>(
            GenerateProceduralSphereMesh(6371000.0f, 64), // Higher quality for Earth
            "EarthSurfaceMaterial", true));

        worldRef.addEntity(std::move(earthEntity));
    }

    // Look for atmosphere layers
    if (sceneXml.find("name=\"AtmosphereLayer1\"") != std::string::npos)
    {
        std::cout << "Creating atmospheric layers from XML configuration..." << std::endl;
        static unsigned int nextEntityId = 2;
        
        // Atmosphere Layer 1
        auto atmos1Entity = std::make_unique<Entity>(nextEntityId++);
        atmos1Entity->addComponent(std::make_unique<TransformC>(
            TransformC::Vector3(0.0f, -6371000.0f, 0.0f),
            TransformC::Quaternion::Identity(),
            TransformC::Vector3(6371000.0f + 50000.0f, 6371000.0f + 50000.0f, 6371000.0f + 50000.0f))); // 50km atmosphere
        atmos1Entity->addComponent(std::make_unique<RenderableC>(
            GenerateProceduralSphereMesh(6371000.0f + 50000.0f, 32),
            "AtmosphereLayer1Material", true));

        worldRef.addEntity(std::move(atmos1Entity));
    }

    if (sceneXml.find("name=\"AtmosphereLayer2\"") != std::string::npos)
    {
        static unsigned int nextEntityId = 3;
        
        // Atmosphere Layer 2
        auto atmos2Entity = std::make_unique<Entity>(nextEntityId++);
        atmos2Entity->addComponent(std::make_unique<TransformC>(
            TransformC::Vector3(0.0f, -6371000.0f, 0.0f),
            TransformC::Quaternion::Identity(),
            TransformC::Vector3(6371000.0f + 100000.0f, 6371000.0f + 100000.0f, 6371000.0f + 100000.0f))); // 100km atmosphere
        atmos2Entity->addComponent(std::make_unique<RenderableC>(
            GenerateProceduralSphereMesh(6371000.0f + 100000.0f, 32),
            "AtmosphereLayer2Material", true));

        worldRef.addEntity(std::move(atmos2Entity));
    }

    // Look for voxel clouds
    if (sceneXml.find("name=\"VoxelClouds\"") != std::string::npos)
    {
        std::cout << "Creating cloud layer from XML configuration..." << std::endl;
        static unsigned int nextEntityId = 4;
        
        auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
        cloudEntity->addComponent(std::make_unique<TransformC>(
            TransformC::Vector3(0.0f, -6371000.0f, 0.0f),
            TransformC::Quaternion::Identity(),
            TransformC::Vector3(6371000.0f + 5000.0f, 6371000.0f + 5000.0f, 6371000.0f + 5000.0f))); // 5km cloud altitude
        cloudEntity->addComponent(std::make_unique<RenderableC>(
            GenerateProceduralSphereMesh(6371000.0f + 5000.0f, 24),
            "CloudLayerMaterial", true));

        worldRef.addEntity(std::move(cloudEntity));
    }

    defaultWorldGenerated = true;
    std::cout << "XML-based world generation complete." << std::endl;
}
