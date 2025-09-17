// Integration between the AssetManager dual asset system and the BootstrapSystem
// This extension ensures internal assets are used as fallbacks for the package system

// Add to BootstrapSystem.h
#include "core/AssetManager.h"

// Additional BootstrapSystem method declarations
private:
    void InitializeInternalAssets(AssetManager& assetManager);

// Implementation in BootstrapSystem.cpp
void BootstrapSystem::InitializeInternalAssets(AssetManager& assetManager)
{
    DEBUG_LOG("Registering internal assets with asset registry");
    
    if (!assetManager.isInitialized())
    {
        DEBUG_LOG("ERROR: AssetManager not initialized");
        return;
    }
    
    // Register all internal assets with the AssetRegistry
    if (assetManager.registerWithAssetRegistry(assetRegistry_))
    {
        DEBUG_LOG("✅ Internal assets registered with asset registry");
    }
    else
    {
        DEBUG_LOG("⚠️ Failed to register some internal assets");
    }
}

// Modify the Init() method in BootstrapSystem.cpp to include:
/*
void BootstrapSystem::Init()
{
    DEBUG_LOG("Initializing bootstrap system");
    if (initialized)
        return;

    DEBUG_LOG("Initializing bootstrap system...");
    
    // Initialize internal assets before running asset compilation
    InitializeInternalAssets(assetManager); // Get AssetManager instance from IoC or global
    
    // Initialize and run asset compilation
    InitializeAssetCompilation();
    
    // Rest of the method...
}
*/
