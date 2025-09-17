#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Class that manages the dual asset system, providing access to both internal and user assets
 */
class AssetManager {
public:
    enum class AssetType {
        TEXTURE,
        FONT,
        AUDIO,
        MATERIAL,
        MESH,
        SHADER,
        SCENE,
        UNKNOWN
    };

    struct AssetInfo {
        std::string id;
        std::string path;
        AssetType type;
        bool isInternal;
    };

    AssetManager();
    ~AssetManager();

    // Initialize the asset manager with the paths to internal and user assets
    bool initialize(const std::string& internalAssetsPath, const std::string& userAssetsPath);

    // Get the path to an asset by its ID, will search both internal and user assets
    // User assets take precedence over internal assets with the same ID
    std::string getAssetPath(const std::string& assetId) const;
    
    // Get internal asset path by ID
    std::string getInternalAssetPath(const std::string& assetId) const;
    
    // Get user asset path by ID
    std::string getUserAssetPath(const std::string& assetId) const;
    
    // Get the fallback asset ID for a specific type
    std::string getFallbackAssetId(AssetType type) const;
    
    // Get the fallback asset path for a specific type
    std::string getFallbackAssetPath(AssetType type) const;
    
    // Check if an asset exists with the given ID
    bool assetExists(const std::string& assetId) const;
    
    // Check if an internal asset exists with the given ID
    bool internalAssetExists(const std::string& assetId) const;
    
    // Check if a user asset exists with the given ID
    bool userAssetExists(const std::string& assetId) const;
    
    // Convert a string to an asset type
    static AssetType stringToAssetType(const std::string& typeString);
    
    // Convert an asset type to a string
    static std::string assetTypeToString(AssetType type);
    
    // Get all registered asset IDs
    std::vector<std::string> getAllAssetIds() const;
    
    // Register internal assets with the AssetRegistry
    // This allows the internal assets to be used by the engine systems
    bool registerWithAssetRegistry(Assets::AssetRegistry& registry);
    
    // Get the current initialization status
    bool isInitialized() const { return initialized; }

private:
    // Load internal assets configuration
    bool loadInternalAssets();
    
    // Load user assets configuration
    bool loadUserAssets();
    
    std::string internalAssetsPath;
    std::string userAssetsPath;
    
    std::unordered_map<std::string, AssetInfo> internalAssets;
    std::unordered_map<std::string, AssetInfo> userAssets;
    
    // Fallback assets to use when requested assets are not found
    std::unordered_map<AssetType, std::string> fallbackAssets;
    
    bool initialized = false;
};
