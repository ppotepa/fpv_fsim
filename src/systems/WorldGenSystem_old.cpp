#include "WorldGenSystem.h"
#include "MaterialManager.h"
#include "core/Entity.h"
#include "../math/MathUtils.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <fstream>

// Component definitions (using Math:: types instead of old Vector3D/Quaternion)
#include "../core/IComponent.h"

struct TransformC : public IComponent
{
    Math::float3 position;
    Math::float4 orientation; // Quaternion (x, y, z, w)
    Math::float3 scale;

    TransformC(Math::float3 pos = {0.0f, 0.0f, 0.0f}, 
               Math::float4 rot = {0.0f, 0.0f, 0.0f, 1.0f}, 
               Math::float3 scl = {1.0f, 1.0f, 1.0f})
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
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), sceneLoaded(false)
{
    // Initialize generic backend systems
    meshGenerator_ = std::make_unique<VoxelMeshGenerator>();
    textureGenerator_ = std::make_unique<ProceduralTexture::ProceduralTextureGenerator>();
    sceneParser_ = std::make_unique<SceneConfig::SceneConfigParser>();
    materialManager_ = std::make_unique<Material::MaterialManager>();
    
    // Connect systems together
    materialManager_->SetTextureGenerator(textureGenerator_.get());
    materialManager_->LoadDefaultMaterials();

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

void WorldGenSystem::LoadScene(const std::string& sceneType)
{
    if (sceneLoaded)
        return;

    try 
    {
        auto sceneData = sceneParser_.LoadScene(sceneType);
        if (sceneData)
        {
            std::cout << "Loading scene of type: " << sceneType << std::endl;
            LoadSceneEntities(*sceneData);
            defaultWorldGenerated = true;
            eventBus.publish(DefaultWorldGeneratedEvent{});
            std::cout << "Scene loading complete." << std::endl;
        }
        else
        {
            std::cout << "Failed to load scene, falling back to default generation..." << std::endl;
            GenerateDefaultSphereWorld();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error loading scene: " << e.what() << ", falling back to default generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig& sceneData)
{
    static unsigned int nextEntityId = 1;

    for (const auto& entityConfig : sceneData.entities)
    {
        auto entity = std::make_unique<Entity>(nextEntityId++);
        
        // Add transform component
        entity->addComponent(std::make_unique<TransformC>(
            entityConfig.position,
            entityConfig.rotation, 
            entityConfig.scale
        ));

        // Generate mesh based on primitive type
        AssetId meshId = GenerateVoxelMesh(entityConfig.primitive);
        
        // Create or get material based on entity type
        std::string materialId = entityConfig.material;
        if (materialId.empty() || !materialManager_->HasMaterial(materialId)) {
            // Create dynamic material based on entity type
            if (entityConfig.name.find("Earth") != std::string::npos) {
                materialId = materialManager_->CreateEarthMaterial(entityConfig.primitive.radius, 1);
            } else if (entityConfig.name.find("Atmosphere") != std::string::npos) {
                int layer = 0;
                if (entityConfig.name.find("Layer1") != std::string::npos) layer = 1;
                else if (entityConfig.name.find("Layer2") != std::string::npos) layer = 2;
                materialId = materialManager_->CreateAtmosphereMaterial(layer, 0.1f);
            } else if (entityConfig.name.find("Cloud") != std::string::npos) {
                materialId = materialManager_->CreateCloudMaterial(0.6f, 0.3f);
            } else {
                // Use default material
                materialId = entityConfig.material.empty() ? "default_material" : entityConfig.material;
            }
        }
        
        // Add renderable component with generated mesh and material
        entity->addComponent(std::make_unique<RenderableC>(
            meshId,
            materialId,
            true
        ));

        // Add optional components based on configuration
        if (!entityConfig.animationClips.empty())
        {
            entity->addComponent(std::make_unique<AnimationC>(
                entityConfig.animationClips,
                0.0f, // current time
                true  // playing
            ));
        }

        if (entityConfig.hasContrail)
        {
            entity->addComponent(std::make_unique<ContrailC>(
                std::vector<Math::float3>(), // trail points
                entityConfig.contrailWidth,
                entityConfig.contrailLength,
                materialManager_->CreateContrailMaterial({1.0f, 1.0f, 1.0f}),
                entityConfig.contrailLifetime
            ));
        }

        if (entityConfig.hasVoxelCloud)
        {
            entity->addComponent(std::make_unique<VoxelCloudC>(
                entityConfig.cloudDensity,
                entityConfig.cloudScale,
                materialManager_->CreateCloudMaterial(entityConfig.cloudDensity, entityConfig.cloudScale),
                entityConfig.cloudNoiseScale
            ));
        }

        worldRef.addEntity(std::move(entity));
        std::cout << "Created entity: " << entityConfig.name << " with material: " << materialId << std::endl;
    }
}

AssetId WorldGenSystem::GenerateVoxelMesh(const VoxelPrimitive& primitive)
{
    return meshGenerator_.GenerateMesh(primitive);
}

void WorldGenSystem::GenerateDefaultSphereWorld()
{
    if (sceneLoaded)
        return;

    std::cout << "Generating default Earth-like sphere world..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create Earth entity using MaterialManager
    auto earthEntity = std::make_unique<Entity>(nextEntityId++);
    earthEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    // Use MaterialManager to create dynamic Earth material
    std::string earthMaterialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? 
                                 "EarthSurfaceMaterial" : 
                                 materialManager_->CreateEarthMaterial(6371000.0f, 2);
    
    // For now, use placeholder mesh ID
    earthEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        earthMaterialId,
        true
    ));
    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere entity
    auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
    atmosphereEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    std::string atmosphereMaterialId = materialManager_->HasMaterial("AtmosphereMaterial") ? 
                                      "AtmosphereMaterial" : 
                                      materialManager_->CreateAtmosphereMaterial(1, 0.1f);
    
    atmosphereEntity->addComponent(std::make_unique<RenderableC>(
        "atmosphere_sphere_mesh",
        atmosphereMaterialId,
        true
    ));
    worldRef.addEntity(std::move(atmosphereEntity));

    // Create cloud entity
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? 
                                 "CloudMaterial" : 
                                 materialManager_->CreateCloudMaterial(0.6f, 0.3f);
    
    cloudEntity->addComponent(std::make_unique<RenderableC>(
        "cloud_sphere_mesh",
        cloudMaterialId,
        true
    ));
    worldRef.addEntity(std::move(cloudEntity));

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Default world generation complete." << std::endl;
}

void WorldGenSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    LoadScene("loading_indicator");
}

void WorldGenSystem::OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)
{
    if (sceneLoaded)
        return;

    // Try to load the default scene configuration
    try 
    {
        LoadScene("loading_indicator");
    }
    catch (const std::exception& e)
    {
        std::cout << "Error loading default scene: " << e.what() << ", falling back to hardcoded generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

// Simplified scene loading for now
void WorldGenSystem::LoadScene(const std::string& sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;
    
    // For now, fallback to default generation
    // TODO: Implement proper XML scene loading when SceneConfigParser API is ready
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene& sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh& meshConfig)
{
    // TODO: Bridge to VoxelMeshGenerator when API is aligned
    return "generated_mesh_placeholder";
}
