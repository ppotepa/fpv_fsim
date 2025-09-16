#include "AssetRegistry.h"
#include <algorithm>
#include <filesystem>

namespace Assets {

AssetRegistry::AssetRegistry() = default;

AssetRegistry::~AssetRegistry() {
    if (isInitialized) {
        shutdown();
    }
}

void AssetRegistry::initialize() {
    if (isInitialized) {
        return;
    }
    
    assets.clear();
    packageAssets.clear();
    loadCallbacks.clear();
    unloadCallbacks.clear();
    
    isInitialized = true;
}

void AssetRegistry::shutdown() {
    if (!isInitialized) {
        return;
    }
    
    // Unload all assets
    for (auto& [id, info] : assets) {
        if (info.isLoaded) {
            unloadAssetData(info);
        }
    }
    
    assets.clear();
    packageAssets.clear();
    loadCallbacks.clear();
    unloadCallbacks.clear();
    
    isInitialized = false;
}

void AssetRegistry::registerPackageAssets(const Package& package) {
    if (!isInitialized) {
        return;
    }
    
    std::vector<AssetId> assetIds;
    
    for (const auto& asset : package.assets) {
        AssetId assetId = AssetIdGenerator::generateAssetId(package.metadata.id, asset.id);
        
        // Create asset info
        AssetInfo info(assetId, package.metadata.id, asset.id, asset.type, 
                      getAssetPath(package, asset));
        
        assets[assetId] = std::move(info);
        assetIds.push_back(assetId);
    }
    
    packageAssets[package.metadata.id] = std::move(assetIds);
}

void AssetRegistry::unregisterPackageAssets(const std::string& packageId) {
    auto it = packageAssets.find(packageId);
    if (it != packageAssets.end()) {
        // Unload and remove assets
        for (AssetId assetId : it->second) {
            auto assetIt = assets.find(assetId);
            if (assetIt != assets.end()) {
                if (assetIt->second.isLoaded) {
                    unloadAssetData(assetIt->second);
                }
                assets.erase(assetIt);
            }
        }
        packageAssets.erase(it);
    }
}

bool AssetRegistry::loadAsset(AssetId assetId) {
    auto it = assets.find(assetId);
    if (it == assets.end()) {
        return false;
    }
    
    AssetInfo& info = it->second;
    if (info.isLoaded) {
        return true; // Already loaded
    }
    
    return loadAssetData(info);
}

void AssetRegistry::unloadAsset(AssetId assetId) {
    auto it = assets.find(assetId);
    if (it != assets.end() && it->second.isLoaded) {
        unloadAssetData(it->second);
    }
}

const AssetRegistry::AssetInfo* AssetRegistry::getAssetInfo(AssetId assetId) const {
    auto it = assets.find(assetId);
    return (it != assets.end()) ? &it->second : nullptr;
}

void* AssetRegistry::getAssetData(AssetId assetId) const {
    const auto* info = getAssetInfo(assetId);
    return (info && info->isLoaded) ? info->data : nullptr;
}

bool AssetRegistry::isAssetLoaded(AssetId assetId) const {
    const auto* info = getAssetInfo(assetId);
    return info && info->isLoaded;
}

std::optional<AssetId> AssetRegistry::resolveAssetReference(const std::string& packageId, 
                                                          const std::string& assetRef) const {
    auto it = packageAssets.find(packageId);
    if (it == packageAssets.end()) {
        return std::nullopt;
    }
    
    // Look for asset by name in the package
    for (AssetId assetId : it->second) {
        const auto* info = getAssetInfo(assetId);
        if (info && info->assetName == assetRef) {
            return assetId;
        }
    }
    
    return std::nullopt;
}

std::vector<AssetId> AssetRegistry::getAssetsByType(AssetType type) const {
    std::vector<AssetId> result;
    
    for (const auto& [id, info] : assets) {
        if (info.type == type) {
            result.push_back(id);
        }
    }
    
    return result;
}

std::vector<AssetId> AssetRegistry::getAssetsByPackage(const std::string& packageId) const {
    auto it = packageAssets.find(packageId);
    return (it != packageAssets.end()) ? it->second : std::vector<AssetId>{};
}

void AssetRegistry::registerAssetLoader(AssetType type, AssetLoadCallback loadCallback, 
                                       AssetUnloadCallback unloadCallback) {
    if (loadCallback) {
        loadCallbacks[type] = std::move(loadCallback);
    }
    if (unloadCallback) {
        unloadCallbacks[type] = std::move(unloadCallback);
    }
}

size_t AssetRegistry::preloadPackageAssets(const std::string& packageId) {
    auto assetIds = getAssetsByPackage(packageId);
    size_t loadedCount = 0;
    
    for (AssetId assetId : assetIds) {
        if (loadAsset(assetId)) {
            loadedCount++;
        }
    }
    
    return loadedCount;
}

void AssetRegistry::unloadPackageAssets(const std::string& packageId) {
    auto assetIds = getAssetsByPackage(packageId);
    
    for (AssetId assetId : assetIds) {
        unloadAsset(assetId);
    }
}

AssetRegistry::MemoryStats AssetRegistry::getMemoryStats() const {
    MemoryStats stats;
    stats.totalAssets = assets.size();
    
    for (const auto& [id, info] : assets) {
        if (info.isLoaded) {
            stats.loadedAssets++;
            stats.totalMemoryUsage += info.dataSize;
            stats.memoryByType[info.type] += info.dataSize;
        }
    }
    
    return stats;
}

size_t AssetRegistry::garbageCollect() {
    // In a real implementation, this would check reference counts
    // For now, we'll just return 0 since we don't have reference tracking
    return 0;
}

bool AssetRegistry::loadAssetData(AssetInfo& assetInfo) {
    auto it = loadCallbacks.find(assetInfo.type);
    if (it == loadCallbacks.end()) {
        return false; // No loader registered for this type
    }
    
    try {
        size_t dataSize = 0;
        void* data = it->second(assetInfo.filePath, dataSize);
        
        if (data) {
            assetInfo.data = data;
            assetInfo.dataSize = dataSize;
            assetInfo.isLoaded = true;
            return true;
        }
    } catch (const std::exception&) {
        // Loading failed
    }
    
    return false;
}

void AssetRegistry::unloadAssetData(AssetInfo& assetInfo) {
    if (!assetInfo.isLoaded || !assetInfo.data) {
        return;
    }
    
    auto it = unloadCallbacks.find(assetInfo.type);
    if (it != unloadCallbacks.end()) {
        try {
            it->second(assetInfo.data, assetInfo.type);
        } catch (const std::exception&) {
            // Cleanup failed, but continue anyway
        }
    }
    
    assetInfo.data = nullptr;
    assetInfo.dataSize = 0;
    assetInfo.isLoaded = false;
}

std::string AssetRegistry::getAssetPath(const Package& package, const AssetDefinition& asset) const {
    // Construct path relative to package directory
    std::filesystem::path packageDir = std::filesystem::path(package.metadata.packagePath).parent_path();
    std::filesystem::path assetPath = packageDir / asset.path;
    return assetPath.string();
}

} // namespace Assets
