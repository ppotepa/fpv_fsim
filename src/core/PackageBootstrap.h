#pragma once
#include "IoContainer.h"
#include "../assets/PackageManager.h"
#include "../assets/AssetRegistry.h"
#include "../systems/BehaviorSystem.h"
#include "../factory/BehaviorRegistry.h"
#include <string>
#include <vector>

namespace Core {

/**
 * Bootstrap system that initializes the application with package support.
 * Sets up IoC container, loads packages, and initializes all systems.
 */
class PackageBootstrap {
public:
    struct BootstrapConfig {
        std::string packagesDirectory = "packages";
        std::vector<std::string> requiredPackages = {"core"};
        bool enableHotReload = true;
        bool preloadAssets = false;
    };
    
    PackageBootstrap();
    ~PackageBootstrap();
    
    /**
     * Initialize the application with package support
     * @param config Bootstrap configuration
     * @return True if initialization was successful
     */
    bool initialize(const BootstrapConfig& config);
    
    /**
     * Shutdown the application and cleanup all resources
     */
    void shutdown();
    
    /**
     * Get the main IoC container
     */
    IoContainer& getContainer() { return *mainContainer; }
    
    /**
     * Get the package manager
     */
    Assets::PackageManager& getPackageManager() { return *packageManager; }
    
    /**
     * Get the asset registry
     */
    Assets::AssetRegistry& getAssetRegistry() { return *assetRegistry; }
    
    /**
     * Get the behavior system
     */
    Systems::BehaviorSystem& getBehaviorSystem() { return *behaviorSystem; }
    
    /**
     * Load additional packages at runtime
     * @param packagePaths Paths to package.xml files to load
     * @return Number of packages successfully loaded
     */
    size_t loadPackages(const std::vector<std::string>& packagePaths);
    
    /**
     * Unload a package at runtime
     * @param packageId ID of the package to unload
     * @return True if package was successfully unloaded
     */
    bool unloadPackage(const std::string& packageId);
    
    /**
     * Reload a package (for hot-reload scenarios)
     * @param packageId ID of the package to reload
     * @return True if package was successfully reloaded
     */
    bool reloadPackage(const std::string& packageId);
    
    /**
     * Check if the bootstrap system is initialized
     */
    bool isInitialized() const { return initialized; }
    
    /**
     * Get bootstrap statistics
     */
    struct BootstrapStats {
        size_t packagesLoaded = 0;
        size_t behaviorsRegistered = 0;
        size_t assetsRegistered = 0;
        size_t initializationTimeMs = 0;
    };
    
    BootstrapStats getStats() const;
    
private:
    std::unique_ptr<IoContainer> mainContainer;
    std::shared_ptr<Assets::PackageManager> packageManager;
    std::shared_ptr<Assets::AssetRegistry> assetRegistry;
    std::shared_ptr<Systems::BehaviorSystem> behaviorSystem;
    std::shared_ptr<Factory::BehaviorRegistry> behaviorRegistry;
    
    BootstrapConfig currentConfig;
    bool initialized = false;
    BootstrapStats stats;
    
    /**
     * Setup core services in the IoC container
     */
    void setupCoreServices();
    
    /**
     * Register core asset loaders
     */
    void registerAssetLoaders();
    
    /**
     * Load and initialize packages
     */
    bool loadInitialPackages();
    
    /**
     * Validate package dependencies
     */
    bool validatePackageDependencies(const std::vector<std::string>& packagePaths);
    
    /**
     * Register behaviors from loaded packages
     */
    void registerPackageBehaviors();
    
    /**
     * Setup package-specific IoC containers
     */
    void setupPackageContainers();
};

} // namespace Core
