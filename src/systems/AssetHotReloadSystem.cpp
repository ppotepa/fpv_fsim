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
    : registry_(registry), loader_(loader)
{
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
    if (checkForChanges())
    {
        reloadChangedPackages();
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
 * Processes all watched files marked for reload. Currently performs a
 * full registry clear and reload, but a more sophisticated implementation
 * would reload only the changed assets.
 */
void AssetHotReloadSystem::reloadChangedPackages()
{
    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;

        if (watched.needsReload)
        {
            std::cout << "Reloading package: " << watched.path << std::endl;

            // Clear existing assets from this package
            // In a real implementation, we'd track which assets belong to which package
            // For now, we'll do a full reload
            registry_.clear();

            // Reload the package
            if (loader_.loadPackage(watched.path))
            {
                std::cout << "Successfully reloaded: " << watched.path << std::endl;
            }
            else
            {
                std::cerr << "Failed to reload: " << watched.path << std::endl;
            }

            watched.needsReload = false;
        }
    }
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
