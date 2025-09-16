#include "core/Engine.h"           // Essential for creating and managing the engine instance
#include "core/PackageBootstrap.h" // New package system bootstrap
#include <iostream>              // For standard input/output operations, particularly error reporting
#include <exception>             // For handling exceptions gracefully
#include "debug.h"               // Debug helper function

/**
 * @brief Main entry point for the FPV Flight Simulator
 *
 * Enhanced with the new package modularity architecture. This function now:
 *
 * 1. Initialize the package system and IoC container
 * 2. Discover and load packages (core, developer, etc.)
 * 3. Initialize the engine with package support
 * 4. Load scenes from packages
 * 5. Run the engine loop with behavior system
 *
 * The package system provides XML-driven scene authoring with C++ code-behind behaviors,
 * modular asset management, and hot-reload capabilities for rapid development iteration.
 *
 * @return int Exit code (0 for success)
 */
int main()
{
    try
    {
        // ====================================================================
        // Step 1: Package System Initialization
        // ====================================================================
        DEBUG_LOG("Starting package system initialization...");
        
        Core::PackageBootstrap bootstrap;
        Core::PackageBootstrap::BootstrapConfig config;
        config.packagesDirectory = "packages";
        config.requiredPackages = {"core", "developer"};
        config.enableHotReload = true;
        config.preloadAssets = false; // Load assets on-demand for better startup performance
        
        if (!bootstrap.initialize(config)) {
            std::cerr << "Failed to initialize package system" << std::endl;
            return 1;
        }
        
        auto stats = bootstrap.getStats();
        DEBUG_LOG("Package system initialized successfully:");
        DEBUG_LOG("  - Packages loaded: " << stats.packagesLoaded);
        DEBUG_LOG("  - Behaviors registered: " << stats.behaviorsRegistered);
        DEBUG_LOG("  - Assets registered: " << stats.assetsRegistered);
        DEBUG_LOG("  - Initialization time: " << stats.initializationTimeMs << "ms");

        // ====================================================================
        // Step 2: Engine Initialization with Package Support
        // ====================================================================
        DEBUG_LOG("Starting FPV Flight Simulator engine initialization...");
        Engine engine; // Create the main engine instance

        // Initialize the engine with package system integration
        // The engine now receives the IoC container and can access package services
        if (!engine.initializeWithPackages(
                bootstrap.getContainer(),
                "configs/physics_config.xml", // Physics parameters
                "configs/render_config.xml",  // Rendering settings
                "configs/input_config.xml"))  // Input mappings
        {
            std::cerr << "Failed to initialize engine with package support" << std::endl;
            return 1;
        }
        DEBUG_LOG("Engine initialized successfully with package system integration.");

        // ====================================================================
        // Step 3: Package-Based Asset Discovery
        // ====================================================================
        // Assets are now automatically discovered and registered through the package system
        // No need for separate asset discovery - packages define their assets declaratively
        DEBUG_LOG("Package-based assets already registered during package loading.");

        // ====================================================================
        // Step 4: Load Scene from Developer Package
        // ====================================================================
        // Load the red cube scene from the developer package
        // This demonstrates XML-driven scene loading with behavior attachment
        DEBUG_LOG("Loading 'RedCubeScene' from developer package...");
        
        auto& packageManager = bootstrap.getPackageManager();
        auto& behaviorSystem = bootstrap.getBehaviorSystem();
        
        // Get the developer package
        const auto* developerPackage = packageManager.getPackage("developer");
        if (!developerPackage) {
            std::cerr << "Developer package not found" << std::endl;
            return 1;
        }
        
        // Load the red cube scene
        if (!engine.loadPackageScene(*developerPackage, "RedCubeScene")) {
            std::cerr << "Failed to load 'RedCubeScene' from developer package" << std::endl;
            return 1;
        }
        DEBUG_LOG("'RedCubeScene' loaded successfully with spinning behavior.");

        // ====================================================================
        // Step 5: Engine Main Loop with Behavior System
        // ====================================================================
        // The engine loop now includes behavior system updates
        DEBUG_LOG("Entering engine's main loop with behavior system...");
        return engine.runWithBehaviors(behaviorSystem); // Enhanced game loop
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}


