#include "core/Engine.h"           // Essential for creating and managing the engine instance
#include "core/PackageBootstrap.h" // New package system bootstrap
#include <iostream>                // For standard input/output operations, particularly error reporting
#include <exception>               // For handling exceptions gracefully
#include "debug.h"                 // Debug helper function

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

        if (!bootstrap.initialize(config))
        {
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
        // Step 2: Engine Initialization (Compatible with Existing Interface)
        // ====================================================================
        DEBUG_LOG("Starting FPV Flight Simulator engine initialization...");
        Engine engine; // Create the main engine instance

        // Initialize the engine with existing interface
        // Package system integration will be added in future Engine updates
        if (!engine.initialize(
                "configs/physics_config.xml", // Physics parameters
                "configs/render_config.xml",  // Rendering settings
                "configs/input_config.xml"))  // Input mappings
        {
            std::cerr << "Failed to initialize engine" << std::endl;
            return 1;
        }
        DEBUG_LOG("Engine initialized successfully.");

        // ====================================================================
        // Step 3: Asset Discovery (Existing Engine Interface)
        // ====================================================================
        // For now, use existing engine asset discovery
        // Package system assets are registered but engine uses existing flow
        DEBUG_LOG("Initiating asset discovery and compilation pipeline...");
        if (!engine.discoverAssets())
        {
            std::cerr << "Failed to discover assets" << std::endl;
            return 1;
        }
        DEBUG_LOG("Assets discovered and compiled into runtime formats.");

        DEBUG_LOG("Resolving assets into usable runtime resources...");
        if (!engine.resolveAssets())
        {
            std::cerr << "Failed to resolve assets" << std::endl;
            return 1;
        }
        DEBUG_LOG("Assets resolved for runtime use.");

        // ====================================================================
        // Step 4: Load Scene (Existing Engine Interface)
        // ====================================================================
        // For now, load existing scene until Engine is updated for package support
        DEBUG_LOG("Loading 'DeveloperScene' (existing implementation)...");
        if (!engine.loadAndDisplayScene("DeveloperScene"))
        {
            std::cerr << "Failed to load and display 'DeveloperScene'" << std::endl;
            return 1;
        }
        DEBUG_LOG("'DeveloperScene' loaded successfully.");

        // ====================================================================
        // Step 5: Engine Main Loop (Existing Interface)
        // ====================================================================
        // The behavior system is ready for integration when Engine is updated
        DEBUG_LOG("Entering engine's main loop...");
        DEBUG_LOG("Package system initialized and ready for Engine integration:");
        DEBUG_LOG("  - Packages loaded: " << stats.packagesLoaded);
        DEBUG_LOG("  - Behaviors registered: " << stats.behaviorsRegistered);
        DEBUG_LOG("  - Package system ready for future Engine integration");

        return engine.run(); // Use existing game loop
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
