#include "AssetHotReloadSystem.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

AssetHotReloadSystem::AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader)
    : registry_(registry), loader_(loader)
{
}

AssetHotReloadSystem::~AssetHotReloadSystem() {}

void AssetHotReloadSystem::update(World &world, float deltaTime)
{
    if (checkForChanges())
    {
        reloadChangedPackages();
    }
}

void AssetHotReloadSystem::watchPackage(const std::string &packagePath)
{
    WatchedFile watched;
    watched.path = packagePath;
    watched.lastModified = getFileModifiedTime(packagePath);
    watched.needsReload = false;

    watchedFiles_[packagePath] = watched;
    std::cout << "Watching package for changes: " << packagePath << std::endl;
}

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
