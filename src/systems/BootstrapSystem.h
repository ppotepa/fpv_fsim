#pragma once
#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include "events/WorldGenEvents.h"

/**
 * Bootstrap system responsible for initializing the world, loading assets, and checking for asset packages.
 */
class BootstrapSystem : public ISystem
{
public:
    BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader);
    virtual ~BootstrapSystem() = default;

    void update(World &world, float deltaTime) override;
    void Init();
    void PostFrameUpdate();

private:
    EventBus &eventBus;
    World &worldRef;
    AssetRegistry &assetRegistry_;
    AssetPackLoader &assetLoader_;
    bool initialized;

    bool CheckForAssetPackages();
    bool LoadAvailablePackages();
    void InitializeAssetCompilation();
};

