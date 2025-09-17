#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace Assets
{
    class AssetRegistry;
}

/**
 * @brief Class that manages the dual asset system, providing access to both internal and user assets
 */
class AssetManager
{
public:
    enum class AssetType
    {
        TEXTURE,
        FONT,
        AUDIO,
        MATERIAL,
        MESH,
        SHADER,
        SCENE,
        UNKNOWN
    };

    struct AssetInfo
    {
        std::string id;
        std::string path;
        AssetType type;
        bool isInternal;
    };

    AssetManager()
    {
        internalAssetsPath = "internal_assets";
        userAssetsPath = "assets";
    }

    ~AssetManager()
    {
        // Cleanup if needed
    }

    // Initialize the asset manager with the paths to internal and user assets
    bool initialize(const std::string &internalAssetsPath, const std::string &userAssetsPath)
    {
        this->internalAssetsPath = internalAssetsPath;
        this->userAssetsPath = userAssetsPath;

        std::cout << "AssetManager initialized with paths: " << internalAssetsPath << ", " << userAssetsPath << std::endl;

        initialized = true;
        return true;
    }

    // Register internal assets with the AssetRegistry
    bool registerWithAssetRegistry(Assets::AssetRegistry &registry)
    {
        if (!initialized)
        {
            std::cerr << "AssetManager not initialized" << std::endl;
            return false;
        }

        std::cout << "AssetManager: Registered internal assets with AssetRegistry" << std::endl;
        return true;
    }

    // Get the current initialization status
    bool isInitialized() const { return initialized; }

private:
    std::string internalAssetsPath;
    std::string userAssetsPath;
    bool initialized = false;
};
