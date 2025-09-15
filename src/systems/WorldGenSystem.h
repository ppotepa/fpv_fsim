#pragma once
#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "core/AssetRegistry.h"
#include "events/WorldGenEvents.h"
#include "../config/SceneConfigParser.h"
#include "../generators/VoxelMeshGenerator.h"
#include "../generators/ProceduralTextureGenerator.h"
#include "MaterialManager.h"
#include "../math/MathUtils.h"
#include <memory>

/**
 * Generic world generation system using XML-driven scene configuration.
 * Supports all scene types through SceneConfigParser and VoxelMeshGenerator.
 */
class WorldGenSystem : public ISystem
{
public:
    WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry);
    virtual ~WorldGenSystem() = default;

    void update(World &world, float deltaTime) override;
    void GenerateDefaultSphereWorld();
    void GenerateWorldFromXMLScene(const std::string &sceneXml);
    void GenerateWorldFromSceneFile(const std::string &sceneFilePath);
    void LoadScene(const SceneConfig::Scene &scene);

private:
    EventBus &eventBus;
    World &worldRef;
    AssetRegistry &assetRegistry_;
    bool sceneLoaded;

    // Generic backend systems
    std::unique_ptr<VoxelMeshGenerator> meshGenerator_;
    std::unique_ptr<ProceduralTexture::ProceduralTextureGenerator> textureGenerator_;
    std::unique_ptr<SceneConfig::SceneConfigParser> sceneParser_;
    std::unique_ptr<Material::MaterialManager> materialManager_;

    // Core scene loading methods
    void LoadScene(const std::string &sceneType);
    void GenerateLoadingIndicatorWorld();
    void LoadSceneEntities(const SceneConfig::Scene &scene);
    AssetId GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig);

    // Event handlers
    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event);

    // Legacy material methods (will be removed when MaterialManager is fully integrated)
    AssetId GetEarthMaterialId();
    AssetId GetAtmosphereMaterialId(int layer);
    AssetId GetCloudMaterialId();

    // Helper method to convert MaterialId to numeric AssetId
    AssetId MaterialIdToAssetId(const std::string &materialId);
};
