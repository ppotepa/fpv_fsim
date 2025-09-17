#include "PackageBootstrap.h"
#include "../debug.h"
#include <chrono>
#include <algorithm>
#include <iostream>

namespace Core
{

    PackageBootstrap::PackageBootstrap() = default;
    PackageBootstrap::~PackageBootstrap()
    {
        if (initialized)
        {
            shutdown();
        }
    }

    bool PackageBootstrap::initialize(const BootstrapConfig &config)
    {
        if (initialized)
        {
            return true;
        }

        auto startTime = std::chrono::steady_clock::now();
        currentConfig = config;

        try
        {
            std::cout << "🔧 Creating main IoC container..." << std::endl;
            // Create main IoC container
            mainContainer = std::make_unique<IoContainer>();

            std::cout << "🔧 Setting up core services..." << std::endl;
            // Setup core services
            setupCoreServices();

            std::cout << "🔧 Resolving core systems..." << std::endl;
            // Initialize core systems
            packageManager = mainContainer->resolve<Assets::PackageManager>();
            assetRegistry = mainContainer->resolve<Assets::AssetRegistry>();
            behaviorSystem = mainContainer->resolve<Systems::BehaviorSystem>();
            behaviorRegistry = mainContainer->resolve<Factory::BehaviorRegistry>();

            if (!packageManager || !assetRegistry || !behaviorSystem || !behaviorRegistry)
            {
                std::cout << "❌ Failed to resolve core systems:" << std::endl;
                std::cout << "   PackageManager: " << (packageManager ? "OK" : "FAILED") << std::endl;
                std::cout << "   AssetRegistry: " << (assetRegistry ? "OK" : "FAILED") << std::endl;
                std::cout << "   BehaviorSystem: " << (behaviorSystem ? "OK" : "FAILED") << std::endl;
                std::cout << "   BehaviorRegistry: " << (behaviorRegistry ? "OK" : "FAILED") << std::endl;
                return false;
            }

            std::cout << "🔧 Initializing systems..." << std::endl;

            // Initialize systems
            assetRegistry->initialize();
            behaviorSystem->initialize();

            std::cout << "🔧 Registering asset loaders..." << std::endl;
            // Register asset loaders
            registerAssetLoaders();

            std::cout << "🔧 Loading initial packages..." << std::endl;
            // Load initial packages
            if (!loadInitialPackages())
            {
                std::cout << "❌ Failed to load initial packages" << std::endl;
                return false;
            }

            std::cout << "🔧 Registering package behaviors..." << std::endl;
            // Register behaviors from packages
            registerPackageBehaviors();

            std::cout << "🔧 Setting up package containers..." << std::endl;
            // Setup package-specific containers
            setupPackageContainers();

            initialized = true;

            auto endTime = std::chrono::steady_clock::now();
            stats.initializationTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                                             endTime - startTime)
                                             .count();

            return true;
        }
        catch (const std::exception &)
        {
            shutdown();
            return false;
        }
    }

    void PackageBootstrap::shutdown()
    {
        if (!initialized)
        {
            return;
        }

        // Shutdown systems in reverse order
        if (behaviorSystem)
        {
            behaviorSystem->shutdown();
        }

        if (assetRegistry)
        {
            assetRegistry->shutdown();
        }

        // Clear container
        if (mainContainer)
        {
            mainContainer->clear();
        }

        // Reset pointers
        behaviorRegistry.reset();
        behaviorSystem.reset();
        assetRegistry.reset();
        packageManager.reset();
        mainContainer.reset();

        initialized = false;
        stats = BootstrapStats{};
    }

    size_t PackageBootstrap::loadPackages(const std::vector<std::string> &packagePaths)
    {
        // Remove the initialized check since we're still in the initialization process
        size_t loadedCount = 0;

        for (const auto &path : packagePaths)
        {
            DEBUG_LOG("Loading package: " << path);
            std::cout << "🔍 Loading package: " << path << std::endl;
            auto result = packageManager->loadPackage(path);
            if (result.success)
            {
                DEBUG_LOG("Successfully loaded package: " << result.package.metadata.id);
                std::cout << "✅ Successfully loaded package: " << result.package.metadata.id << std::endl;
                // Register assets from the package
                assetRegistry->registerPackageAssets(result.package);

                // Preload assets if configured
                if (currentConfig.preloadAssets)
                {
                    assetRegistry->preloadPackageAssets(result.package.metadata.id);
                }

                loadedCount++;
                stats.packagesLoaded++;
            }
            else
            {
                ERROR_LOG("Failed to load package: " << path);
                std::cout << "❌ Failed to load package: " << path << std::endl;
                for (const auto &error : result.errors)
                {
                    ERROR_LOG("  - " << error);
                    std::cout << "   - " << error << std::endl;
                }
            }
        }

        return loadedCount;
    }

    bool PackageBootstrap::unloadPackage(const std::string &packageId)
    {
        if (!initialized)
        {
            return false;
        }

        // Unregister assets first
        assetRegistry->unregisterPackageAssets(packageId);

        // Unload package
        bool success = packageManager->unloadPackage(packageId);

        if (success)
        {
            stats.packagesLoaded = std::max(0, static_cast<int>(stats.packagesLoaded) - 1);
        }

        return success;
    }

    bool PackageBootstrap::reloadPackage(const std::string &packageId)
    {
        if (!initialized)
        {
            return false;
        }

        // Get the package to find its path
        const auto *package = packageManager->getPackage(packageId);
        if (!package)
        {
            return false;
        }

        std::string packagePath = package->metadata.packagePath;

        // Unload current version
        if (!unloadPackage(packageId))
        {
            return false;
        }

        // Reload from path
        auto result = packageManager->loadPackage(packagePath);
        if (result.success)
        {
            assetRegistry->registerPackageAssets(result.package);
            if (currentConfig.preloadAssets)
            {
                assetRegistry->preloadPackageAssets(result.package.metadata.id);
            }
            stats.packagesLoaded++;
            return true;
        }

        return false;
    }

    PackageBootstrap::BootstrapStats PackageBootstrap::getStats() const
    {
        BootstrapStats currentStats = stats;

        if (initialized)
        {
            currentStats.packagesLoaded = packageManager->getAllPackages().size();
            currentStats.behaviorsRegistered = behaviorRegistry->getRegisteredBehaviors().size();
            currentStats.assetsRegistered = assetRegistry->getMemoryStats().totalAssets;
        }

        return currentStats;
    }

    void PackageBootstrap::setupCoreServices()
    {
        // Register core services as singletons
        mainContainer->register_<Assets::PackageManager, Assets::PackageManager>(
            IoContainer::Lifetime::Singleton);

        mainContainer->register_<Assets::AssetRegistry, Assets::AssetRegistry>(
            IoContainer::Lifetime::Singleton);

        mainContainer->register_<Systems::BehaviorSystem, Systems::BehaviorSystem>(
            IoContainer::Lifetime::Singleton);

        // Register behavior registry as singleton reference
        mainContainer->registerInstance<Factory::BehaviorRegistry>(
            std::shared_ptr<Factory::BehaviorRegistry>(&Factory::BehaviorRegistry::instance(), [](Factory::BehaviorRegistry *) {}));
    }

    void PackageBootstrap::registerAssetLoaders()
    {
        // Register default asset loaders
        // In a real implementation, these would load actual file formats

        // Mesh loader
        assetRegistry->registerAssetLoader(Assets::AssetType::Mesh, [](const std::string &filePath, size_t &outSize) -> void *
                                           {
                                               // Placeholder: load mesh from file
                                               outSize = 1024;           // Dummy size
                                               return new char[outSize]; // Dummy data
                                           },
                                           [](void *data, Assets::AssetType type)
                                           { delete[] static_cast<char *>(data); });

        // Texture loader
        assetRegistry->registerAssetLoader(Assets::AssetType::Texture, [](const std::string &filePath, size_t &outSize) -> void *
                                           {
                                               // Placeholder: load texture from file
                                               outSize = 2048;           // Dummy size
                                               return new char[outSize]; // Dummy data
                                           },
                                           [](void *data, Assets::AssetType type)
                                           { delete[] static_cast<char *>(data); });

        // Audio loader
        assetRegistry->registerAssetLoader(Assets::AssetType::Audio, [](const std::string &filePath, size_t &outSize) -> void *
                                           {
                                               // Placeholder: load audio from file
                                               outSize = 4096;           // Dummy size
                                               return new char[outSize]; // Dummy data
                                           },
                                           [](void *data, Assets::AssetType type)
                                           { delete[] static_cast<char *>(data); });

        // Material loader
        assetRegistry->registerAssetLoader(Assets::AssetType::Material, [](const std::string &filePath, size_t &outSize) -> void *
                                           {
                                               // Placeholder: load material from file
                                               outSize = 512;            // Dummy size
                                               return new char[outSize]; // Dummy data
                                           },
                                           [](void *data, Assets::AssetType type)
                                           { delete[] static_cast<char *>(data); });
    }

    bool PackageBootstrap::loadInitialPackages()
    {
        DEBUG_LOG("Starting package discovery in directory: " << currentConfig.packagesDirectory);
        std::cout << "🔍 Discovering packages in directory: " << currentConfig.packagesDirectory << std::endl;

        // Discover packages in the packages directory
        auto discoveryResult = packageManager->discoverPackages(currentConfig.packagesDirectory);
        if (!discoveryResult.errors.empty())
        {
            ERROR_LOG("Package discovery errors found:");
            std::cout << "❌ Package discovery errors:" << std::endl;
            for (const auto &error : discoveryResult.errors)
            {
                ERROR_LOG("  - " << error);
                std::cout << "   - " << error << std::endl;
            }
            return false;
        }

        DEBUG_LOG("Found " << discoveryResult.packagePaths.size() << " package paths");
        std::cout << "✅ Found " << discoveryResult.packagePaths.size() << " package paths:" << std::endl;
        for (const auto &path : discoveryResult.packagePaths)
        {
            DEBUG_LOG("  - " << path);
            std::cout << "   - " << path << std::endl;
        }

        std::cout << "🔍 Validating package dependencies..." << std::endl;
        // Validate dependencies
        if (!validatePackageDependencies(discoveryResult.packagePaths))
        {
            ERROR_LOG("Package dependency validation failed");
            std::cout << "❌ Package dependency validation failed" << std::endl;
            return false;
        }

        std::cout << "🔍 Loading packages..." << std::endl;
        // Load packages in dependency order
        size_t loadedCount = loadPackages(discoveryResult.packagePaths);
        DEBUG_LOG("Loaded " << loadedCount << " packages");
        std::cout << "✅ Loaded " << loadedCount << " packages" << std::endl;

        std::cout << "🔍 Checking required packages..." << std::endl;

        // Check if all required packages were loaded
        for (const auto &requiredPackage : currentConfig.requiredPackages)
        {
            bool isLoaded = packageManager->isPackageLoaded(requiredPackage);
            DEBUG_LOG("Required package '" << requiredPackage << "': " << (isLoaded ? "LOADED" : "NOT FOUND"));
            if (!isLoaded)
            {
                ERROR_LOG("Required package '" << requiredPackage << "' was not loaded!");
                return false;
            }
        }

        stats.packagesLoaded = loadedCount;
        return loadedCount > 0;
    }

    bool PackageBootstrap::validatePackageDependencies(const std::vector<std::string> &packagePaths)
    {
        // For now, just return true - full dependency validation would require
        // parsing all packages first to build the dependency graph
        return true;
    }

    void PackageBootstrap::registerPackageBehaviors()
    {
        // Register built-in behaviors
        // In a real implementation, this would scan loaded packages for behavior definitions
        // and dynamically load them, but for now we'll rely on static registration
        // via the REGISTER_BEHAVIOR macro in behavior implementation files
    }

    void PackageBootstrap::setupPackageContainers()
    {
        // Create child containers for each loaded package
        // This allows package-specific services and configurations
        auto packages = packageManager->getAllPackages();

        for (const auto *package : packages)
        {
            auto childContainer = mainContainer->createChild();
            // In a real implementation, register package-specific services here
        }
    }

} // namespace Core
