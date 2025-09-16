#pragma once
#include "Package.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <optional>

namespace Assets {

/**
 * Registry for managing all loaded assets from packages.
 * Provides centralized access to assets by AssetId and supports
 * asset reference resolution and lifecycle management.
 */
class AssetRegistry {
public:
    /**
     * Structure containing asset metadata and loading information
     */
    struct AssetInfo {
        AssetId id;
        std::string packageId;
        std::string assetName;
        AssetType type;
        std::string filePath;
        bool isLoaded = false;
        void* data = nullptr; // Pointer to loaded asset data
        size_t dataSize = 0;
        
        AssetInfo() = default;
        AssetInfo(AssetId id, const std::string& packageId, const std::string& assetName, 
                 AssetType type, const std::string& filePath)
            : id(id), packageId(packageId), assetName(assetName), type(type), filePath(filePath) {}
    };
    
    /**
     * Callback type for asset loading operations
     */
    using AssetLoadCallback = std::function<void*(const std::string& filePath, size_t& outSize)>;
    using AssetUnloadCallback = std::function<void(void* data, AssetType type)>;
    
    AssetRegistry();
    ~AssetRegistry();
    
    /**
     * Initialize the asset registry
     */
    void initialize();
    
    /**
     * Shutdown the registry and unload all assets
     */
    void shutdown();
    
    /**
     * Register assets from a package
     * @param package The package containing assets to register
     */
    void registerPackageAssets(const Package& package);
    
    /**
     * Unregister all assets from a package
     * @param packageId ID of the package to unregister
     */
    void unregisterPackageAssets(const std::string& packageId);
    
    /**
     * Load an asset by ID
     * @param assetId ID of the asset to load
     * @return True if asset was successfully loaded
     */
    bool loadAsset(AssetId assetId);
    
    /**
     * Unload an asset by ID
     * @param assetId ID of the asset to unload
     */
    void unloadAsset(AssetId assetId);
    
    /**
     * Get asset information by ID
     * @param assetId ID of the asset
     * @return Pointer to asset info, or nullptr if not found
     */
    const AssetInfo* getAssetInfo(AssetId assetId) const;
    
    /**
     * Get loaded asset data by ID
     * @param assetId ID of the asset
     * @return Pointer to asset data, or nullptr if not loaded
     */
    void* getAssetData(AssetId assetId) const;
    
    /**
     * Get asset data with type checking
     * @param assetId ID of the asset
     * @return Typed pointer to asset data, or nullptr if not loaded or wrong type
     */
    template<typename T>
    T* getAssetData(AssetId assetId) const {
        const auto* info = getAssetInfo(assetId);
        if (info && info->isLoaded && info->data) {
            return static_cast<T*>(info->data);
        }
        return nullptr;
    }
    
    /**
     * Check if an asset is loaded
     * @param assetId ID of the asset
     * @return True if the asset is loaded
     */
    bool isAssetLoaded(AssetId assetId) const;
    
    /**
     * Resolve an asset reference to an AssetId
     * @param packageId ID of the package containing the reference
     * @param assetRef Asset reference string (e.g., "meshes/cube.obj")
     * @return AssetId if found, nullopt otherwise
     */
    std::optional<AssetId> resolveAssetReference(const std::string& packageId, 
                                                const std::string& assetRef) const;
    
    /**
     * Get all assets of a specific type
     * @param type Asset type to filter by
     * @return Vector of asset IDs matching the type
     */
    std::vector<AssetId> getAssetsByType(AssetType type) const;
    
    /**
     * Get all assets from a specific package
     * @param packageId ID of the package
     * @return Vector of asset IDs from the package
     */
    std::vector<AssetId> getAssetsByPackage(const std::string& packageId) const;
    
    /**
     * Register asset loading callbacks for specific asset types
     * @param type Asset type
     * @param loadCallback Function to load asset data from file
     * @param unloadCallback Function to cleanup asset data
     */
    void registerAssetLoader(AssetType type, AssetLoadCallback loadCallback, 
                           AssetUnloadCallback unloadCallback);
    
    /**
     * Preload all assets from a package
     * @param packageId ID of the package
     * @return Number of assets successfully loaded
     */
    size_t preloadPackageAssets(const std::string& packageId);
    
    /**
     * Unload all assets from a package
     * @param packageId ID of the package
     */
    void unloadPackageAssets(const std::string& packageId);
    
    /**
     * Get memory usage statistics
     */
    struct MemoryStats {
        size_t totalAssets = 0;
        size_t loadedAssets = 0;
        size_t totalMemoryUsage = 0;
        std::unordered_map<AssetType, size_t> memoryByType;
    };
    
    MemoryStats getMemoryStats() const;
    
    /**
     * Force garbage collection of unused assets
     * @return Number of assets unloaded
     */
    size_t garbageCollect();
    
private:
    // Asset storage
    std::unordered_map<AssetId, AssetInfo> assets;
    
    // Asset loaders by type
    std::unordered_map<AssetType, AssetLoadCallback> loadCallbacks;
    std::unordered_map<AssetType, AssetUnloadCallback> unloadCallbacks;
    
    // Package to assets mapping for efficient cleanup
    std::unordered_map<std::string, std::vector<AssetId>> packageAssets;
    
    bool isInitialized = false;
    
    /**
     * Load asset data using registered loader
     */
    bool loadAssetData(AssetInfo& assetInfo);
    
    /**
     * Unload asset data using registered unloader
     */
    void unloadAssetData(AssetInfo& assetInfo);
    
    /**
     * Get default asset path relative to package
     */
    std::string getAssetPath(const Package& package, const AssetDefinition& asset) const;
};

} // namespace Assets
