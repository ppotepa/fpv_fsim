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

    if (sceneType == "loading_indicator")
    {
        std::cout << "Creating loading indicator scene with central globe and orbiting objects..." << std::endl;
        GenerateLoadingIndicatorWorld();
    }
    else
    {
        std::cout << "Unknown scene type, falling back to default generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

void WorldGenSystem::GenerateLoadingIndicatorWorld()
{
    if (sceneLoaded)
        return;

    std::cout << "Generating loading indicator world with orbiting aircraft and clouds..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create central globe entity (larger, different color)
    auto globeEntity = std::make_unique<Entity>(nextEntityId++);
    globeEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, 0.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(2.0f, 2.0f, 2.0f))); // Larger globe

    // Use green material for the globe (different from default)
    std::string globeMaterialId = materialManager_->HasMaterial("LandMaterial") ? "LandMaterial" : materialManager_->CreateEarthMaterial(2.0f, 1);

    globeEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        globeMaterialId,
        true));

    worldRef.addEntity(std::move(globeEntity));

    // Create first orbiting aircraft entity
    auto aircraft1Entity = std::make_unique<Entity>(nextEntityId++);
    aircraft1Entity->addComponent(std::make_unique<TransformC>(
        Math::float3(4.5f, 0.0f, 0.0f), // Start at radius 4.5
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(0.5f, 0.5f, 0.5f))); // Aircraft scale

    std::string aircraftMaterialId = materialManager_->HasMaterial("AircraftBodyMaterial") ? "AircraftBodyMaterial" : materialManager_->CreateContrailMaterial({0.8f, 0.2f, 0.2f}); // Red

    aircraft1Entity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        aircraftMaterialId,
        true));

    worldRef.addEntity(std::move(aircraft1Entity));

    // Create second orbiting aircraft entity
    auto aircraft2Entity = std::make_unique<Entity>(nextEntityId++);
    aircraft2Entity->addComponent(std::make_unique<TransformC>(
        Math::float3(-5.2f, 1.0f, 0.0f), // Start at different position
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(0.4f, 0.4f, 0.4f)));

    aircraft2Entity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        aircraftMaterialId,
        true));

    worldRef.addEntity(std::move(aircraft2Entity));

    // Create some cloud entities around the globe
    for (int i = 0; i < 6; i++)
    {
        auto cloudEntity = std::make_unique<Entity>(nextEntityId++);

        // Distribute clouds in a circle around the globe
        float angle = (i / 6.0f) * 2.0f * 3.14159f;
        float radius = 6.0f + (i * 0.3f); // Varying distances
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        float y = -1.0f + (i * 0.3f); // Varying heights

        cloudEntity->addComponent(std::make_unique<TransformC>(
            Math::float3(x, y, z),
            Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
            Math::float3(0.6f, 0.6f, 0.6f)));

        std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.8f, 0.4f);

        cloudEntity->addComponent(std::make_unique<RenderableC>(
            "earth_sphere_mesh",
            cloudMaterialId,
            true));

        worldRef.addEntity(std::move(cloudEntity));
    }

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Loading indicator scene created successfully with 1 globe, 2 aircraft, and 6 clouds." << std::endl;
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene &sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig)
{
    std::cout << "Generating voxel mesh: " << meshConfig.name << " (ID: " << meshConfig.id << ")" << std::endl;

    // Convert SceneConfig::CompoundMesh to VoxelMesh::CompoundParams
    VoxelMesh::CompoundParams params;
    params.name = meshConfig.name;

    // Convert each VoxelPrimitive to CompoundPart
    for (const auto &primitive : meshConfig.parts)
    {
        VoxelMesh::CompoundPart part;

        // Convert primitive type
        switch (primitive.type)
        {
        case SceneConfig::VoxelPrimitive::Type::Cube:
            part.primitive.type = VoxelMesh::VoxelType::Cube;
            break;
        case SceneConfig::VoxelPrimitive::Type::Sphere:
            part.primitive.type = VoxelMesh::VoxelType::Sphere;
            break;
        case SceneConfig::VoxelPrimitive::Type::Cylinder:
            part.primitive.type = VoxelMesh::VoxelType::Cylinder;
            break;
        case SceneConfig::VoxelPrimitive::Type::Plane:
            part.primitive.type = VoxelMesh::VoxelType::Plane;
            break;
        }

        // Set primitive parameters
        part.primitive.size = primitive.size;
        part.primitive.radius = primitive.radius;
        part.primitive.height = primitive.height;
        part.primitive.subdivisions = primitive.subdivisions;

        // Set transform
        part.offset = Math::float3(
            primitive.transform.position.x,
            primitive.transform.position.y,
            primitive.transform.position.z);
        part.scale = Math::float3(
            primitive.transform.scale.x,
            primitive.transform.scale.y,
            primitive.transform.scale.z);

        part.name = primitive.materialId; // Use material ID as part name for reference
        params.parts.push_back(part);
    }

    // Generate the mesh using VoxelMeshGenerator
    VoxelMesh::MeshData meshData = meshGenerator_->generateCompound(params);

    if (meshData.isEmpty())
    {
        std::cerr << "Failed to generate voxel mesh: " << meshConfig.name << std::endl;
        return 0; // Return invalid AssetId
    }

    // Create a MeshRecipeAsset from the generated mesh data
    auto meshAsset = std::make_unique<MeshRecipeAsset>();
    meshAsset->generator = "VoxelMeshGenerator";
    meshAsset->params["mesh_type"] = std::string("compound_mesh");
    meshAsset->params["mesh_name"] = std::string(meshConfig.name);
    meshAsset->params["part_count"] = static_cast<int>(meshConfig.parts.size());

    // Store vertex and index data (simplified - in production this would need proper mesh asset structure)
    std::cout << "Generated mesh with " << meshData.vertices.size() << " vertices and "
              << meshData.indices.size() << " indices" << std::endl;

    // Generate numeric asset ID for the mesh using FNV-1a hash
    constexpr uint32_t FNV_OFFSET_BASIS = 2166136261u;
    constexpr uint32_t FNV_PRIME = 16777619u;

    std::string meshIdString = "voxel_mesh:" + meshConfig.id;
    uint32_t meshAssetId = FNV_OFFSET_BASIS;
    for (char c : meshIdString)
    {
        meshAssetId ^= static_cast<uint32_t>(c);
        meshAssetId *= FNV_PRIME;
    }

    // Ensure we don't return 0 (reserved for invalid ID)
    if (meshAssetId == 0)
        meshAssetId = 1;

    // Register the mesh asset
    assetRegistry_.registerMeshRecipe(meshAssetId, std::move(meshAsset));

    return meshAssetId;
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

// Helper method to convert MaterialId to numeric AssetId
AssetId WorldGenSystem::MaterialIdToAssetId(const std::string &materialId)
{
    // Use FNV-1a hash algorithm for consistent ID generation
    constexpr uint32_t FNV_OFFSET_BASIS = 2166136261u;
    constexpr uint32_t FNV_PRIME = 16777619u;

    uint32_t hash = FNV_OFFSET_BASIS;
    for (char c : materialId)
    {
        hash ^= static_cast<uint32_t>(c);
        hash *= FNV_PRIME;
    }

    // Ensure we don't return 0 (reserved for invalid ID)
    return (hash == 0) ? 1 : hash;
}

// Legacy material methods (placeholder implementations)
AssetId WorldGenSystem::GetEarthMaterialId()
{
    std::string materialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(6371000.0f, 1);
    return MaterialIdToAssetId(materialId);
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    std::string materialName = "AtmosphereMaterial_Layer" + std::to_string(layer);
    std::string materialId = materialManager_->HasMaterial(materialName) ? materialName : materialManager_->CreateAtmosphereMaterial(layer, 0.1f);
    return MaterialIdToAssetId(materialId);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    std::string materialId = materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.6f, 0.3f);
    return MaterialIdToAssetId(materialId);
}
