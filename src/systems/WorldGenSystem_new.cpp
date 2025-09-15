#include "WorldGenSystem.h"
#include "MaterialManager.h"
#include "core/Entity.h"
#include "../math/MathUtils.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <fstream>

// Component definitions (using Math:: types)
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

void WorldGenSystem::LoadScene(const std::string &sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;

    // For now, fallback to default generation
    // TODO: Implement proper XML scene loading when SceneConfigParser API is ready
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene &sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig)
{
    // TODO: Bridge to VoxelMeshGenerator when API is aligned
    return "generated_mesh_placeholder";
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
        Math::float3(1.0f, 1.0f, 1.0f)));

    // Use MaterialManager to create dynamic Earth material
    std::string earthMaterialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(6371000.0f, 2);

    // For now, use placeholder mesh ID
    earthEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        earthMaterialId,
        true));
    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere entity
    auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
    atmosphereEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)));

    std::string atmosphereMaterialId = materialManager_->HasMaterial("AtmosphereMaterial") ? "AtmosphereMaterial" : materialManager_->CreateAtmosphereMaterial(1, 0.1f);

    atmosphereEntity->addComponent(std::make_unique<RenderableC>(
        "atmosphere_sphere_mesh",
        atmosphereMaterialId,
        true));
    worldRef.addEntity(std::move(atmosphereEntity));

    // Create cloud entity
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)));

    std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.6f, 0.3f);

    cloudEntity->addComponent(std::make_unique<RenderableC>(
        "cloud_sphere_mesh",
        cloudMaterialId,
        true));
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
    catch (const std::exception &e)
    {
        std::cout << "Error loading default scene: " << e.what() << ", falling back to hardcoded generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

// Legacy material methods (placeholder implementations)
AssetId WorldGenSystem::GetEarthMaterialId()
{
    return materialManager_->HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(6371000.0f, 1);
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    std::string materialName = "AtmosphereMaterial_Layer" + std::to_string(layer);
    return materialManager_->HasMaterial(materialName) ? materialName : materialManager_->CreateAtmosphereMaterial(layer, 0.1f);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    return materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.6f, 0.3f);
}
