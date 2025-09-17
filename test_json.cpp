#include "assets/PackageJsonParser.h"
#include "assets/PackageManager.h"
#include <iostream>

int main()
{
    std::cout << "Testing JSON Package System..." << std::endl;

    // Test the JSON parser directly
    Assets::PackageJsonParser parser;
    auto result = parser.loadPackage("assets/packages/TestPackage/package.json");

    if (result.success)
    {
        std::cout << "✅ Successfully loaded JSON package!" << std::endl;
        std::cout << "Package ID: " << result.package.metadata.id << std::endl;
        std::cout << "Package Name: " << result.package.metadata.name << std::endl;
        std::cout << "Version: " << result.package.metadata.version << std::endl;
        std::cout << "Assets count: " << result.package.assets.size() << std::endl;
        std::cout << "Scenes count: " << result.package.scenes.size() << std::endl;

        // List assets
        for (const auto &asset : result.package.assets)
        {
            std::cout << "Asset: " << asset.id << " (type: " << static_cast<int>(asset.type) << ")" << std::endl;
        }

        // List scenes
        for (const auto &scene : result.package.scenes)
        {
            std::cout << "Scene: " << scene.id << " (" << scene.name << ")" << std::endl;
            std::cout << "  Entities: " << scene.entities.size() << std::endl;
        }
    }
    else
    {
        std::cout << "❌ Failed to load JSON package!" << std::endl;
        for (const auto &error : result.errors)
        {
            std::cout << "Error: " << error << std::endl;
        }
    }

    // Test package manager
    std::cout << "\nTesting PackageManager..." << std::endl;
    Assets::PackageManager manager;
    auto discovery = manager.discoverPackages("assets/packages");

    std::cout << "Found " << discovery.packagePaths.size() << " packages:" << std::endl;
    for (const auto &path : discovery.packagePaths)
    {
        std::cout << "  " << path << std::endl;
    }

    return 0;
}
