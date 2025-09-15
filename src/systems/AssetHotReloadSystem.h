#ifndef ASSET_HOT_RELOAD_SYSTEM_H
#define ASSET_HOT_RELOAD_SYSTEM_H

#include "core/ISystem.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include <string>
#include <unordered_map>
#include <chrono>

class AssetHotReloadSystem : public ISystem
{
public:
    AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader);
    ~AssetHotReloadSystem();

    void update(World &world, float deltaTime) override;

    // Add a package to watch for changes
    void watchPackage(const std::string &packagePath);

    // Check if any watched files have changed
    bool checkForChanges();

    // Reload changed packages
    void reloadChangedPackages();

private:
    AssetRegistry &registry_;
    AssetPackLoader &loader_;

    struct WatchedFile
    {
        std::string path;
        std::chrono::system_clock::time_point lastModified;
        bool needsReload;
    };

    std::unordered_map<std::string, WatchedFile> watchedFiles_;

    std::chrono::system_clock::time_point getFileModifiedTime(const std::string &path);
};

#endif
