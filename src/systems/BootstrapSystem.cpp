#include "BootstrapSystem.h"
#include "events/WorldGenEvents.h"
#include "../assets/AssetCompilerService.h"
#include <iostream>
#include <filesystem>
#include "../debug.h"

BootstrapSystem::BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), assetLoader_(assetLoader), initialized(false)
{
    DEBUG_LOG("Initializing BootstrapSystem");
}

void BootstrapSystem::update(World &world, float deltaTime)
{
    // Bootstrap system doesn't need continuous updates
}

void BootstrapSystem::Init()
{
    DEBUG_LOG("Initializing bootstrap system");
    if (initialized)
        return;

    DEBUG_LOG("Initializing bootstrap system...");

    // Initialize and run asset compilation
    InitializeAssetCompilation();

    // Try to load available packages
    bool packagesLoaded = LoadAvailablePackages();

    if (!packagesLoaded)
    {
        DEBUG_LOG("No asset packages found, triggering default world generation...");
        eventBus.publish(NoPackagesFoundEvent{});
    }
    else
    {
        DEBUG_LOG("Asset packages loaded successfully. Available packages:");
        for (const auto &package : assetRegistry_.getLoadedPackages())
        {
            DEBUG_LOG("  - " << package);
        }

        // Check if we have a default scene configuration to use for world generation
        const std::string *defaultScene = assetRegistry_.getDefaultScene();
        if (defaultScene != nullptr)
        {
            DEBUG_LOG("Found default scene configuration, triggering world generation from XML...");
            // Trigger world generation with the loaded scene configuration
            eventBus.publish(DefaultWorldGeneratedEvent{});
        }
        else
        {
            DEBUG_LOG("No default scene found in loaded packages, falling back to default world generation...");
            eventBus.publish(NoPackagesFoundEvent{});
        }
    }

    initialized = true;
}

void BootstrapSystem::PostFrameUpdate()
{
    DEBUG_LOG("Post-frame update in BootstrapSystem");
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
    DEBUG_LOG("Loading available packages");
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
    DEBUG_LOG("Initializing asset compilation pipeline");
    DEBUG_LOG("Initializing asset compilation pipeline...");

    try
    {
        // Create asset compiler service
        AssetCompilation::AssetCompilerService compiler;
        compiler.setDebugMode(true);
        compiler.setOptimizationLevel(1);
        compiler.setOutputDirectory("runtime/data/compiled");

        // Compile assets from packages directory only
        if (std::filesystem::exists("assets/packages"))
        {
            DEBUG_LOG("Compiling assets from 'assets/packages' directory...");
            auto results = compiler.compileDirectory("assets/packages", true);

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

            DEBUG_LOG("Asset compilation completed: "
                      << successful << " compiled, "
                      << skipped << " skipped, "
                      << failed << " failed");
        }

        // Compile assets from packages
        std::string packagesDir = "assets/packages";
        if (std::filesystem::exists(packagesDir))
        {
            DEBUG_LOG("Compiling package assets...");

            for (const auto &entry : std::filesystem::directory_iterator(packagesDir))
            {
                if (entry.is_directory())
                {
                    std::string packagePath = entry.path().string();
                    DEBUG_LOG("Compiling package: " << packagePath);

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
        DEBUG_LOG("Asset compilation statistics:");
        DEBUG_LOG("  Assets compiled: " << stats.assetsCompiled);
        DEBUG_LOG("  Assets skipped: " << stats.assetsSkipped);
        DEBUG_LOG("  Total compilation time: " << stats.totalCompilationTime << "ms");

        if (stats.totalInputSize > 0)
        {
            double compressionRatio = (double)stats.totalOutputSize / stats.totalInputSize;
            DEBUG_LOG("  Compression ratio: " << (compressionRatio * 100.0) << "%");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during asset compilation: " << e.what() << std::endl;
    }
}
