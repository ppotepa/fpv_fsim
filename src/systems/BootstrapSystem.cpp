#include "BootstrapSystem.h"
#include "events/WorldGenEvents.h"
#include "../assets/AssetCompilerService.h"
#include <iostream>
#include <filesystem>

BootstrapSystem::BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), assetLoader_(assetLoader), initialized(false)
{
}

void BootstrapSystem::update(World &world, float deltaTime)
{
    // Bootstrap system doesn't need continuous updates
}

void BootstrapSystem::Init()
{
    if (initialized)
        return;

    std::cout << "Initializing bootstrap system..." << std::endl;

    // Initialize and run asset compilation
    InitializeAssetCompilation();

    // Try to load available packages
    bool packagesLoaded = LoadAvailablePackages();

    if (!packagesLoaded)
    {
        std::cout << "No asset packages found, triggering default world generation..." << std::endl;
        eventBus.publish(NoPackagesFoundEvent{});
    }
    else
    {
        std::cout << "Asset packages loaded successfully. Available packages:" << std::endl;
        for (const auto &package : assetRegistry_.getLoadedPackages())
        {
            std::cout << "  - " << package << std::endl;
        }

        // Check if we have a default scene configuration to use for world generation
        const std::string *defaultScene = assetRegistry_.getDefaultScene();
        if (defaultScene != nullptr)
        {
            std::cout << "Found default scene configuration, triggering world generation from XML..." << std::endl;
            // Trigger world generation with the loaded scene configuration
            eventBus.publish(DefaultWorldGeneratedEvent{});
        }
        else
        {
            std::cout << "No default scene found in loaded packages, falling back to default world generation..." << std::endl;
            eventBus.publish(NoPackagesFoundEvent{});
        }
    }

    initialized = true;
}

void BootstrapSystem::PostFrameUpdate()
{
    // Could handle hot-reloading here in the future
}

bool BootstrapSystem::CheckForAssetPackages()
{
    // Check if assets/packages directory exists and has package files
    std::filesystem::path packagesDir = "assets/packages";

    if (!std::filesystem::exists(packagesDir))
    {
        return false;
    }

    // Check for any .xml package files
    for (const auto &entry : std::filesystem::recursive_directory_iterator(packagesDir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".xml")
        {
            return true;
        }
    }

    // Check runtime/data/packs for .pak files
    std::filesystem::path packsDir = "assets/runtime/data/packs";

    if (std::filesystem::exists(packsDir))
    {
        for (const auto &entry : std::filesystem::directory_iterator(packsDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".pak")
            {
                return true;
            }
        }
    }

    return false;
}

bool BootstrapSystem::LoadAvailablePackages()
{
    std::filesystem::path packagesDir = "assets/packages";

    if (!std::filesystem::exists(packagesDir))
    {
        return false;
    }

    bool loadedAny = false;

    // Load DeveloperPackage first (fallback package)
    std::filesystem::path devPackagePath = packagesDir / "DeveloperPackage" / "package.xml";
    if (std::filesystem::exists(devPackagePath))
    {
        if (assetLoader_.loadPackage(devPackagePath.string()))
        {
            loadedAny = true;
        }
    }

    // Load other packages
    for (const auto &entry : std::filesystem::directory_iterator(packagesDir))
    {
        if (entry.is_directory() && entry.path().filename() != "DeveloperPackage")
        {
            std::filesystem::path packageXml = entry.path() / "package.xml";
            if (std::filesystem::exists(packageXml))
            {
                if (assetLoader_.loadPackage(packageXml.string()))
                {
                    loadedAny = true;
                }
            }
        }
    }

    return loadedAny;
}

void BootstrapSystem::InitializeAssetCompilation()
{
    std::cout << "Initializing asset compilation pipeline..." << std::endl;

    try
    {
        // Create asset compiler service
        AssetCompilation::AssetCompilerService compiler;
        compiler.setDebugMode(true);
        compiler.setOptimizationLevel(1);
        compiler.setOutputDirectory("runtime/data/compiled");

        // Compile assets from main assets directory
        if (std::filesystem::exists("assets"))
        {
            std::cout << "Compiling assets from 'assets' directory..." << std::endl;
            auto results = compiler.compileDirectory("assets", true);

            int successful = 0;
            int failed = 0;
            int skipped = 0;

            for (const auto &result : results)
            {
                if (result.success)
                {
                    if (result.errorMessage.find("skipped") != std::string::npos)
                    {
                        skipped++;
                    }
                    else
                    {
                        successful++;
                    }
                }
                else
                {
                    failed++;
                    std::cerr << "Asset compilation failed: " << result.errorMessage << std::endl;
                }
            }

            std::cout << "Asset compilation completed: "
                      << successful << " compiled, "
                      << skipped << " skipped, "
                      << failed << " failed" << std::endl;
        }

        // Compile assets from packages
        std::string packagesDir = "assets/packages";
        if (std::filesystem::exists(packagesDir))
        {
            std::cout << "Compiling package assets..." << std::endl;

            for (const auto &entry : std::filesystem::directory_iterator(packagesDir))
            {
                if (entry.is_directory())
                {
                    std::string packagePath = entry.path().string();
                    std::cout << "Compiling package: " << packagePath << std::endl;

                    auto results = compiler.compileAssetPackage(packagePath);

                    for (const auto &result : results)
                    {
                        if (!result.success && result.errorMessage.find("skipped") == std::string::npos)
                        {
                            std::cerr << "Package asset compilation failed: " << result.errorMessage << std::endl;
                        }
                    }
                }
            }
        }

        // Print compilation statistics
        const auto &stats = compiler.getStatistics();
        std::cout << "Asset compilation statistics:" << std::endl;
        std::cout << "  Assets compiled: " << stats.assetsCompiled << std::endl;
        std::cout << "  Assets skipped: " << stats.assetsSkipped << std::endl;
        std::cout << "  Total compilation time: " << stats.totalCompilationTime << "ms" << std::endl;

        if (stats.totalInputSize > 0)
        {
            double compressionRatio = (double)stats.totalOutputSize / stats.totalInputSize;
            std::cout << "  Compression ratio: " << (compressionRatio * 100.0) << "%" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during asset compilation: " << e.what() << std::endl;
    }
}
