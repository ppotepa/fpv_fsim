/**
 * @file AssetHotReloadSystem.cpp
 * @brief Implementation of the asset hot-reload system.
 */

#include "AssetHotReloadSystem.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Construct a new AssetHotReloadSystem.
 *
 * Initializes the system with references to the asset registry and loader.
 * The system starts with no watched packages.
 *
 * @param registry Reference to the asset registry for reloading assets
 * @param loader Reference to the asset pack loader for loading packages
 */
AssetHotReloadSystem::AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader)
    : registry_(registry), loader_(loader), hasPendingAssets_(false), commitRequested_(false)
{
    // Initialize double-buffering system
    pendingRegistry_ = std::make_unique<AssetRegistry>();
    pendingLoader_ = std::make_unique<AssetPackLoader>(*pendingRegistry_);
}

/** @brief Destructor - currently no cleanup needed */
AssetHotReloadSystem::~AssetHotReloadSystem() {}

/**
 * @brief Update the system and check for asset file changes.
 *
 * Called each frame to monitor watched asset packages. Checks for file
 * modifications and reloads changed packages automatically.
 *
 * @param world Reference to the game world (unused in this system)
 * @param deltaTime Time elapsed since last update in seconds (unused)
 */
void AssetHotReloadSystem::update(World &world, float deltaTime)
{
    // Check for changes at regular intervals
    if (checkForChanges())
    {
        // Start loading changed packages into pending registry
        loadPendingAssets();
    }

    // Commit pending assets at frame boundary if ready
    if (commitRequested_ && hasPendingAssets_)
    {
        commitPendingAssets();
        commitRequested_ = false;
        hasPendingAssets_ = false;
    }
}

/**
 * @brief Add a package to the watch list for change monitoring.
 *
 * Registers an asset package file to be monitored for changes. Records
 * the initial modification time and adds it to the watch list.
 *
 * @param packagePath Path to the asset package file to watch
 */
void AssetHotReloadSystem::watchPackage(const std::string &packagePath)
{
    WatchedFile watched;
    watched.path = packagePath;
    watched.lastModified = getFileModifiedTime(packagePath);
    watched.needsReload = false;

    watchedFiles_[packagePath] = watched;
    std::cout << "Watching package for changes: " << packagePath << std::endl;
}

/**
 * @brief Automatically discover and watch all packages in the packages directory.
 *
 * Scans the packages directory for package.xml files and automatically
 * adds them to the watch list, making the engine package-agnostic.
 *
 * @param packagesDirectory Path to the packages directory
 * @return Number of packages discovered and added to watch list
 */
int AssetHotReloadSystem::watchAllPackages(const std::string &packagesDirectory)
{
    int packageCount = 0;

    try
    {
        if (!std::filesystem::exists(packagesDirectory))
        {
            std::cout << "Packages directory not found: " << packagesDirectory << std::endl;
            return 0;
        }

        // Iterate through all subdirectories in the packages directory
        for (const auto &entry : std::filesystem::directory_iterator(packagesDirectory))
        {
            if (entry.is_directory())
            {
                // Look for package.xml in each subdirectory
                std::string packagePath = entry.path().string() + "/package.xml";
                if (std::filesystem::exists(packagePath))
                {
                    watchPackage(packagePath);
                    packageCount++;
                    std::cout << "Auto-discovered package: " << packagePath << std::endl;
                }
            }
        }

        std::cout << "Auto-discovered " << packageCount << " packages for hot-reload monitoring" << std::endl;
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error discovering packages: " << e.what() << std::endl;
    }

    return packageCount;
}

/**
 * @brief Check if any watched files have been modified.
 *
 * Iterates through all watched files and compares their current modification
 * times with the last recorded times. Files that have changed are marked
 * for reload.
 *
 * @return true if any files have changed since last check, false otherwise
 */
bool AssetHotReloadSystem::checkForChanges()
{
    bool hasChanges = false;

    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;
        auto currentTime = getFileModifiedTime(watched.path);

        if (currentTime > watched.lastModified)
        {
            watched.lastModified = currentTime;
            watched.needsReload = true;
            hasChanges = true;
            std::cout << "Detected change in: " << watched.path << std::endl;
        }
    }

    return hasChanges;
}

/**
 * @brief Reload all packages that have been marked as changed.
 *
 * Now delegates to the deterministic double-buffering system to ensure
 * frame-boundary commits without mid-frame asset swapping.
 */
void AssetHotReloadSystem::reloadChangedPackages()
{
    // Legacy method - now delegates to deterministic system
    if (checkForChanges())
    {
        loadPendingAssets();
        if (hasPendingAssets_)
        {
            commitRequested_ = true;
        }
    }
}

/**
 * @brief Load changed packages into pending registry for deterministic commit.
 *
 * Loads assets into a secondary registry without affecting the active one.
 * This allows for atomic swapping at frame boundaries.
 */
void AssetHotReloadSystem::loadPendingAssets()
{
    bool hasChanges = false;

    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;

        if (watched.needsReload)
        {
            std::cout << "Loading pending assets from: " << watched.path << std::endl;

            // Copy current registry state to pending registry first
            // This ensures we don't lose non-changed assets
            if (!hasChanges)
            {
                // Reset pending registry and copy existing assets
                pendingRegistry_ = std::make_unique<AssetRegistry>();
                pendingLoader_ = std::make_unique<AssetPackLoader>(*pendingRegistry_);

                // TODO: Copy existing assets from active registry to pending registry
                // For now, we reload all packages which is less efficient but safer
                hasChanges = true;
            }

            // Load the changed package into pending registry
            if (pendingLoader_->loadPackage(watched.path))
            {
                std::cout << "Successfully loaded pending assets from: " << watched.path << std::endl;
            }
            else
            {
                std::cerr << "Failed to load pending assets from: " << watched.path << std::endl;
            }

            watched.needsReload = false;
        }
    }

    if (hasChanges)
    {
        hasPendingAssets_ = true;
        commitRequested_ = true;
    }
}

/**
 * @brief Commit pending assets by swapping registries.
 *
 * Atomically swaps the pending registry with the active one,
 * ensuring deterministic asset updates at frame boundaries.
 */
void AssetHotReloadSystem::commitPendingAssets()
{
    if (!hasPendingAssets_)
        return;

    std::cout << "Committing asset changes at frame boundary" << std::endl;

    // Atomic swap: move pending registry contents to active registry
    // This is a simplified implementation - in production this would need
    // more sophisticated handle repointing and indirection table updates

    // Clear active registry and copy from pending
    registry_.clear();

    // For now, reload all packages into the active registry
    // TODO: Implement proper asset handle repointing and indirection tables
    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;
        if (loader_.loadPackage(watched.path))
        {
            std::cout << "Reloaded package: " << watched.path << " into active registry" << std::endl;
        }
    }

    std::cout << "Asset hot-reload commit completed" << std::endl;
}

/**
 * @brief Get the last modification time of a file.
 *
 * Uses the C++ filesystem library to get the last write time of a file.
 * Handles errors gracefully by returning the minimum time point.
 *
 * @param path Path to the file
 * @return The file's last modification time, or minimum time if file doesn't exist or error occurs
 */
std::chrono::system_clock::time_point AssetHotReloadSystem::getFileModifiedTime(const std::string &path)
{
    try
    {
        if (fs::exists(path))
        {
            auto fileTime = fs::last_write_time(path);
            return std::chrono::system_clock::time_point(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                    fileTime.time_since_epoch()));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error checking file time for " << path << ": " << e.what() << std::endl;
    }

    return std::chrono::system_clock::time_point::min();
}
