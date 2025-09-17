/**
 * @file AssetHotReloadSystem.h
 * @brief System for monitoring and hot-reloading asset packages during development.
 *
 * This system provides live asset reloading capabilities for development workflows.
 * It monitors asset package files for changes and automatically reloads them
 * when modifications are detected, allowing for rapid iteration during development.
 */

#ifndef ASSET_HOT_RELOAD_SYSTEM_H
#define ASSET_HOT_RELOAD_SYSTEM_H

#include "core/ISystem.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include <string>
#include <unordered_map>
#include <chrono>
#include <memory>

/**
 * @class AssetHotReloadSystem
 * @brief System that monitors asset files and reloads them when changed.
 *
 * This system implements hot-reloading of asset packages by monitoring file
 * modification times. When changes are detected, it automatically reloads
 * the affected packages, making development iteration faster and more efficient.
 */
class AssetHotReloadSystem : public ISystem
{
public:
    /**
     * @brief Construct a new AssetHotReloadSystem.
     *
     * @param registry Reference to the asset registry for reloading assets
     * @param loader Reference to the asset pack loader for loading packages
     */
    AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader);

    /** @brief Destructor */
    ~AssetHotReloadSystem();

    /**
     * @brief Update the system and check for asset file changes.
     *
     * Called each frame to monitor watched asset packages for changes.
     * When changes are detected, marks packages for reloading.
     *
     * @param world Reference to the game world
     * @param deltaTime Time elapsed since last update in seconds
     */
    void update(World &world, float deltaTime) override;

    /**
     * @brief Add a package to the watch list for change monitoring.
     *
     * Registers an asset package file to be monitored for changes.
     * The system will track the modification time of this file.
     *
     * @param packagePath Path to the asset package file to watch
     */
    void watchPackage(const std::string &packagePath);

    /**
     * @brief Automatically discover and watch all packages in the packages directory.
     *
     * Scans the packages directory for package.json files and automatically
     * adds them to the watch list. This makes the engine package-agnostic.
     *
     * @param packagesDirectory Path to the packages directory (default: "assets/packages")
     * @return Number of packages discovered and added to watch list
     */
    int watchAllPackages(const std::string &packagesDirectory = "assets/packages");

    /**
     * @brief Check if any watched files have been modified.
     *
     * Scans all watched files and updates their modification status.
     * Files that have changed since last check are marked for reload.
     *
     * @return true if any files have changed, false otherwise
     */
    bool checkForChanges();

    /**
     * @brief Reload all packages that have been marked as changed.
     *
     * Processes all watched files marked for reload and reloads
     * their corresponding asset packages through the asset loader.
     */
    void reloadChangedPackages();

private:
    /** @brief Reference to the asset registry */
    AssetRegistry &registry_;

    /** @brief Reference to the asset pack loader */
    AssetPackLoader &loader_;

    /**
     * @struct WatchedFile
     * @brief Information about a file being watched for changes.
     */
    struct WatchedFile
    {
        /** @brief Path to the watched file */
        std::string path;

        /** @brief Last modification time of the file */
        std::chrono::system_clock::time_point lastModified;

        /** @brief Whether this file needs to be reloaded */
        bool needsReload;
    };

    /** @brief Map of package paths to their watched file information */
    std::unordered_map<std::string, WatchedFile> watchedFiles_;

    /** @brief Secondary asset registry for double-buffering */
    std::unique_ptr<AssetRegistry> pendingRegistry_;

    /** @brief Secondary asset loader for loading into pending registry */
    std::unique_ptr<AssetPackLoader> pendingLoader_;

    /** @brief Flag indicating pending assets are ready for commit */
    bool hasPendingAssets_;

    /** @brief Flag to request commit at frame boundary */
    bool commitRequested_;

    /**
     * @brief Get the last modification time of a file.
     *
     * @param path Path to the file
     * @return The file's last modification time, or epoch time if file doesn't exist
     */
    std::chrono::system_clock::time_point getFileModifiedTime(const std::string &path);

    /**
     * @brief Load changed packages into pending registry for deterministic commit.
     *
     * Loads assets into a secondary registry without affecting the active one.
     * This allows for atomic swapping at frame boundaries.
     */
    void loadPendingAssets();

    /**
     * @brief Commit pending assets by swapping registries.
     *
     * Atomically swaps the pending registry with the active one,
     * ensuring deterministic asset updates at frame boundaries.
     */
    void commitPendingAssets();
};

#endif
