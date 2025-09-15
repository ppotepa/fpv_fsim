#pragma once
#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "core/AssetRegistry.h"
#include "events/WorldGenEvents.h"

/**
 * World generation system for creating procedural worlds and default scenes.
 */
class WorldGenSystem : public ISystem
{
public:
    WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry);
    virtual ~WorldGenSystem() = default;

    void update(World &world, float deltaTime) override;
    void GenerateDefaultSphereWorld();
    void GenerateWorldFromXMLScene(const std::string &sceneXml);

private:
    EventBus &eventBus;
    World &worldRef;
    AssetRegistry &assetRegistry_;
    bool defaultWorldGenerated;

    // Event handlers
    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event);

    // Helper methods for procedural generation
    AssetId GenerateProceduralSphereMesh(float radius, int segments);
    AssetId GetEarthMaterialId();
    AssetId GetAtmosphereMaterialId(int layer);
    AssetId GetCloudMaterialId();
};
