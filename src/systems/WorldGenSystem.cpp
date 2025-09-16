#include "factory/EntityFactory.h"
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

WorldGenSystem::WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, Material::MaterialManager &materialManager)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), materialManager_(materialManager), sceneLoaded(false)
{
    // Initialize generic backend systems
    meshGenerator_ = std::make_unique<VoxelMeshGenerator>();
    textureGenerator_ = std::make_unique<ProceduralTexture::ProceduralTextureGenerator>();
    sceneParser_ = std::make_unique<SceneConfig::SceneConfigParser>();

    // Initialize EntityFactory
    entityFactory_ = std::make_unique<EntityFactory::EntityFactory>(eventBus, materialManager);
    entityFactory_->loadConfiguration("configs/entity_factory_config.xml");

    // Connect systems together
    materialManager_.SetTextureGenerator(textureGenerator_.get());

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

WorldGenSystem::~WorldGenSystem() = default;

void WorldGenSystem::update(World &world, float deltaTime)
{
    // World generation is event-driven, no continuous updates needed
}

void WorldGenSystem::LoadScene(const std::string &sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;

    // Try to load XML scene configuration first
    auto parseResult = sceneParser_->loadXmlScene(sceneType);

    if (parseResult.success && parseResult.scene)
    {
        std::cout << "Successfully loaded XML scene: " << parseResult.scene->name << std::endl;
        LoadSceneEntities(*parseResult.scene);
        sceneLoaded = true;
        eventBus.publish(DefaultWorldGeneratedEvent{});
        return;
    }

    std::cout << "XML scene loading failed: " << parseResult.errorMessage << std::endl;
    std::cout << "Falling back to hardcoded scene generation..." << std::endl;

    // Fallback to hardcoded generation
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

    std::cout << "Generating simplified loading indicator world..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create central globe entity using EntityFactory
    auto globeEntity = entityFactory_->createFromTemplate("earth_sphere", "LoadingGlobe", nextEntityId++);
    if (globeEntity)
    {
        worldRef.addEntity(std::move(globeEntity));
        std::cout << "Created LoadingGlobe entity" << std::endl;
    }

    // Create first orbiting aircraft
    auto aircraft1Entity = entityFactory_->createFromTemplate("basic_drone", "OrbitingAircraft1", nextEntityId++);
    if (aircraft1Entity)
    {
        worldRef.addEntity(std::move(aircraft1Entity));
        std::cout << "Created OrbitingAircraft1 entity" << std::endl;
    }

    // Create second orbiting aircraft
    auto aircraft2Entity = entityFactory_->createFromTemplate("basic_drone", "OrbitingAircraft2", nextEntityId++);
    if (aircraft2Entity)
    {
        worldRef.addEntity(std::move(aircraft2Entity));
        std::cout << "Created OrbitingAircraft2 entity" << std::endl;
    }

    // Create cloud entities
    for (int i = 0; i < 5; i++)
    {
        auto cloudEntity = entityFactory_->createFromTemplate("cloud_object", "LoadingCloud" + std::to_string(i), nextEntityId++);
        if (cloudEntity)
        {
            worldRef.addEntity(std::move(cloudEntity));
        }
    }

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Loading indicator scene created successfully with basic entities." << std::endl;
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene &sceneData)
{
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
    std::cout << "Scene: " << sceneData.name << " (ID: " << sceneData.id << ")" << std::endl;

    static unsigned int nextEntityId = 1;
    int entitiesCreated = 0;

    // If scene has parsed entities, use them
    if (!sceneData.rootEntities.empty())
    {
        for (const auto &entityPtr : sceneData.rootEntities)
        {
            if (!entityPtr)
                continue;

            const auto &entityData = *entityPtr;

            try
            {
                // Create ECS entity with transform component
                auto entity = std::make_unique<Entity>(nextEntityId++);

                // Add transform component
                entity->addComponent(std::make_unique<TransformC>(
                    Math::float3(entityData.transform.position.x,
                                 entityData.transform.position.y,
                                 entityData.transform.position.z),
                    Math::float4(entityData.transform.rotation.x,
                                 entityData.transform.rotation.y,
                                 entityData.transform.rotation.z,
                                 entityData.transform.rotation.w),
                    Math::float3(entityData.transform.scale.x,
                                 entityData.transform.scale.y,
                                 entityData.transform.scale.z)));

                // Add entity to world
                worldRef.addEntity(std::move(entity));
                entitiesCreated++;

                std::cout << "Created entity: " << entityData.id << " (type: " << entityData.type << ")" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error creating entity " << entityData.id << ": " << e.what() << std::endl;
            }
        }
    }
    else
    {
        // Scene parser didn't create entities yet, create based on scene type
        std::cout << "No parsed entities found, creating entities based on scene ID..." << std::endl;

        if (sceneData.id == "loading_indicator")
        {
            // Create loading indicator entities programmatically based on XML structure
            CreateLoadingIndicatorEntitiesFromXmlStructure(nextEntityId, entitiesCreated);
        }
        else if (sceneData.id == "default_sphere_world" || sceneData.id == "procedural_earth_like")
        {
            CreateDefaultSphereEntitiesFromXmlStructure(nextEntityId, entitiesCreated);
        }
        else
        {
            std::cout << "Unknown scene type for entity creation: " << sceneData.id << std::endl;
        }
    }

    std::cout << "Successfully created " << entitiesCreated << " entities from XML scene data" << std::endl;
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

    // Create Earth entity using EntityFactory
    auto earthEntity = entityFactory_->createFromTemplate("earth_sphere", "Earth", nextEntityId++);
    if (earthEntity)
    {
        // Override position and scale for Earth
        if (auto transform = earthEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, -6371000.0f, 0.0f};
            transform->scale = {1.0f, 1.0f, 1.0f};
        }

        // Use MaterialManager to create dynamic Earth material
        if (auto renderable = earthEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_.CreateEarthMaterial(6371000.0f, 2);
            renderable->meshId = "earth_sphere_mesh";
        }

        worldRef.addEntity(std::move(earthEntity));
    }

    // Create atmosphere entity using EntityFactory
    auto atmosphereEntity = entityFactory_->createFromTemplate("earth_sphere", "Atmosphere", nextEntityId++);
    if (atmosphereEntity)
    {
        // Override settings for atmosphere
        if (auto transform = atmosphereEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, -6371000.0f, 0.0f};
            transform->scale = {1.0f, 1.0f, 1.0f};
        }

        if (auto renderable = atmosphereEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("AtmosphereMaterial") ? "AtmosphereMaterial" : materialManager_.CreateAtmosphereMaterial(1, 0.1f);
            renderable->meshId = "atmosphere_sphere_mesh";
        }

        worldRef.addEntity(std::move(atmosphereEntity));
    }

    // Create cloud entity using EntityFactory
    auto cloudEntity = entityFactory_->createFromTemplate("cloud_object", "GlobalClouds", nextEntityId++);
    if (cloudEntity)
    {
        // Override settings for global cloud layer
        if (auto transform = cloudEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, -6371000.0f, 0.0f};
            transform->scale = {1.0f, 1.0f, 1.0f};
        }

        if (auto renderable = cloudEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_.CreateCloudMaterial(0.6f, 0.3f);
            renderable->meshId = "cloud_sphere_mesh";
        }

        worldRef.addEntity(std::move(cloudEntity));
    }

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

    // Try to load the default scene configuration from the asset registry
    try
    {
        const std::string *defaultSceneXml = assetRegistry_.getDefaultScene();
        if (defaultSceneXml != nullptr)
        {
            std::cout << "Loading default scene configuration from package..." << std::endl;
            
            // Parse the scene type from the XML (looking for type="procedural_earth_like")
            size_t typeStart = defaultSceneXml->find("type=\"") + 6;
            size_t typeEnd = defaultSceneXml->find("\"", typeStart);
            if (typeStart != std::string::npos + 6 && typeEnd != std::string::npos)
            {
                std::string sceneType = defaultSceneXml->substr(typeStart, typeEnd - typeStart);
                std::cout << "Loading scene of type: " << sceneType << std::endl;
                LoadScene(sceneType);
            }
            else
            {
                std::cout << "Unable to parse scene type from default scene XML, falling back to hardcoded generation..." << std::endl;
                GenerateDefaultSphereWorld();
            }
        }
        else
        {
            std::cout << "No default scene registered, falling back to hardcoded generation..." << std::endl;
            GenerateDefaultSphereWorld();
        }
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
    std::string materialId = materialManager_.HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_.CreateEarthMaterial(6371000.0f, 1);
    return MaterialIdToAssetId(materialId);
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    std::string materialName = "AtmosphereMaterial_Layer" + std::to_string(layer);
    std::string materialId = materialManager_.HasMaterial(materialName) ? materialName : materialManager_.CreateAtmosphereMaterial(layer, 0.1f);
    return MaterialIdToAssetId(materialId);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    std::string materialId = materialManager_.HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_.CreateCloudMaterial(0.6f, 0.3f);
    return MaterialIdToAssetId(materialId);
}

void WorldGenSystem::CreateLoadingIndicatorEntitiesFromXmlStructure(unsigned int &nextEntityId, int &entitiesCreated)
{
    std::cout << "Creating loading indicator entities based on XML structure..." << std::endl;

    // Create central globe entity (from XML: central_globe)
    auto globeEntity = std::make_unique<Entity>(nextEntityId++);
    globeEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, 0.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(2.0f, 2.0f, 2.0f))); // Scale from XML

    std::string globeMaterialId = materialManager_.HasMaterial("LandMaterial") ? "LandMaterial" : materialManager_.CreateEarthMaterial(2.0f, 1);
    globeEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        globeMaterialId,
        true));
    worldRef.addEntity(std::move(globeEntity));
    entitiesCreated++;

    // Create 2 aircraft entities (from XML: aircraft_1, aircraft_2)
    for (int i = 0; i < 2; ++i)
    {
        auto aircraftEntity = std::make_unique<Entity>(nextEntityId++);
        float xPos = (i == 0) ? 5.0f : -5.0f; // From XML positions
        aircraftEntity->addComponent(std::make_unique<TransformC>(
            Math::float3(xPos, 0.0f, 0.0f),
            Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
            Math::float3(0.5f, 0.5f, 0.5f))); // Scale from XML

        std::string aircraftMaterialId = materialManager_.HasMaterial("AircraftBodyMaterial") ? "AircraftBodyMaterial" : materialManager_.CreateContrailMaterial({0.8f, 0.2f, 0.2f});
        aircraftEntity->addComponent(std::make_unique<RenderableC>(
            "aircraft_mesh",
            aircraftMaterialId,
            true));
        worldRef.addEntity(std::move(aircraftEntity));
        entitiesCreated++;
    }

    // Create 6 cloud entities (from XML: cloud_1 to cloud_6)
    Math::float3 cloudPositions[] = {
        {3.0f, 2.0f, 1.0f}, {-3.0f, 2.0f, -1.0f}, {1.0f, -2.0f, 3.0f}, {-1.0f, -2.0f, -3.0f}, {2.0f, 0.0f, 4.0f}, {-2.0f, 0.0f, -4.0f}};

    for (int i = 0; i < 6; ++i)
    {
        auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
        cloudEntity->addComponent(std::make_unique<TransformC>(
            cloudPositions[i],
            Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
            Math::float3(1.0f, 1.0f, 1.0f)));

        std::string cloudMaterialId = materialManager_.HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_.CreateCloudMaterial(0.8f, 0.4f);
        cloudEntity->addComponent(std::make_unique<RenderableC>(
            "cloud_mesh",
            cloudMaterialId,
            true));
        worldRef.addEntity(std::move(cloudEntity));
        entitiesCreated++;
    }

    std::cout << "Created " << entitiesCreated << " entities based on loading_indicator.xml structure" << std::endl;
}

void WorldGenSystem::CreateDefaultSphereEntitiesFromXmlStructure(unsigned int &nextEntityId, int &entitiesCreated)
{
    std::cout << "Creating default sphere entities based on XML structure..." << std::endl;

    // Create earth sphere entity using EntityFactory (from XML: earth_sphere)
    auto earthEntity = entityFactory_->createFromTemplate("earth_sphere", "Earth", nextEntityId++);
    if (earthEntity)
    {
        // Override settings based on XML structure
        if (auto transform = earthEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, 0.0f, 0.0f};
            transform->scale = {1.0f, 1.0f, 1.0f};
        }

        if (auto renderable = earthEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_.CreateEarthMaterial(6371000.0f, 2);
            renderable->meshId = "earth_sphere_mesh";
        }

        worldRef.addEntity(std::move(earthEntity));
        entitiesCreated++;
    }

    // Create atmosphere layer using EntityFactory (from XML: atmosphere_layer_1)
    auto atmosphereEntity = entityFactory_->createFromTemplate("earth_sphere", "Atmosphere", nextEntityId++);
    if (atmosphereEntity)
    {
        // Override settings based on XML structure
        if (auto transform = atmosphereEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, 0.0f, 0.0f};
            transform->scale = {1.1f, 1.1f, 1.1f}; // Scale from XML
        }

        if (auto renderable = atmosphereEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("AtmosphereMaterial") ? "AtmosphereMaterial" : materialManager_.CreateAtmosphereMaterial(1, 0.1f);
            renderable->meshId = "atmosphere_mesh";
        }

        worldRef.addEntity(std::move(atmosphereEntity));
        entitiesCreated++;
    }

    // Create cloud layer using EntityFactory (from XML: cloud_layer)
    auto cloudEntity = entityFactory_->createFromTemplate("cloud_object", "Clouds", nextEntityId++);
    if (cloudEntity)
    {
        // Override settings based on XML structure
        if (auto transform = cloudEntity->getComponent<TransformC>())
        {
            transform->position = {0.0f, 0.0f, 0.0f};
            transform->scale = {1.05f, 1.05f, 1.05f}; // Scale from XML
        }

        if (auto renderable = cloudEntity->getComponent<RenderableC>())
        {
            renderable->materialId = materialManager_.HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_.CreateCloudMaterial(0.6f, 0.3f);
            renderable->meshId = "cloud_mesh";
        }

        worldRef.addEntity(std::move(cloudEntity));
        entitiesCreated++;
    }

    std::cout << "Created " << entitiesCreated << " entities based on default_sphere_world.xml structure" << std::endl;
}
