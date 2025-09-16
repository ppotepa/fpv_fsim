#include "core/Engine.h" // Essential for creating and managing the engine instance
#include <iostream>      // For standard input/output operations, particularly error reporting
#include <exception>     // For handling exceptions gracefully

/**
 * @brief Main entry point for the FPV Flight Simulator
 *
 * This function serves strictly as a bootstrap layer, establishing the minimal
 * runtime environment needed for the engine. Its responsibilities are:
 *
 * 1. Initialize the engine
 * 2. Trigger asset discovery
 * 3. Request asset resolution
 * 4. Request scene compilation and display
 * 5. Run the engine loop
 *
 * This keeps the entry point lean, stable, and framework-like, delegating
 * all specific functionality to the appropriate subsystems.
 *
 * @return int Exit code (0 for success)
 */
int main()
{
    try
    {
        // ====================================================================
        // Step 1: Start (Engine Initialization)
        // ====================================================================
        std::cout << "Starting FPV Flight Simulator engine initialization..." << std::endl;
        Engine engine; // Create the main engine instance

        // Initialize the engine with paths to configuration files.
        // These configurations dictate fundamental engine behaviors,
        // such as physics parameters, rendering settings, and input mappings.
        if (!engine.initialize(
                "configs/physics_config.xml", // Physics parameters like fixed timestep, air density model
                "configs/render_config.xml",  // Rendering settings like window title, dimensions, VSync
                "configs/input_config.xml"))  // Input mappings for various devices and actions
        {
            std::cerr << "Failed to initialize engine" << std::endl;
            return 1;
        }
        std::cout << "Engine initialized successfully." << std::endl;

        // ====================================================================
        // Step 2 & 3: Asset Resolution and Asset Compilation
        // ====================================================================
        // This phase involves discovering raw assets, compiling them into
        // optimized runtime formats, and then loading them into the asset registry.
        // The Engine delegates this complex process to its BootstrapSystem.
        std::cout << "Initiating asset discovery and compilation pipeline..." << std::endl;
        if (!engine.discoverAssets()) // Triggers BootstrapSystem::Init()
        {
            std::cerr << "Failed to discover assets" << std::endl;
            return 1;
        }
        std::cout << "Assets discovered and compiled into runtime formats." << std::endl;

        // The 'resolveAssets' step is currently handled internally by BootstrapSystem's Init().
        // This method serves as an explicit placeholder for potential future, more
        // complex asset resolution logic that might involve further processing
        // or dependency management after initial compilation and loading.
        std::cout << "Resolving assets into usable runtime resources..." << std::endl;
        if (!engine.resolveAssets())
        {
            std::cerr << "Failed to resolve assets" << std::endl;
            return 1;
        }
        std::cout << "Assets resolved for runtime use." << std::endl;

        // ====================================================================
        // Step 4 & 5: Loading and Rendering (Developer Scene)
        // ====================================================================
        // Instead of a generic compiled scene, we explicitly load the developer scene.
        // This demonstrates configuration-driven scene loading.
        std::cout << "Requesting 'DeveloperScene' compilation and display..." << std::endl;
        if (!engine.loadAndDisplayScene("DeveloperScene"))
        {
            std::cerr << "Failed to load and display 'DeveloperScene'" << std::endl;
            return 1;
        }
        std::cout << "'DeveloperScene' rendered successfully." << std::endl;

        // ====================================================================
        // Step 6: Looping (Engine Main Loop)
        // ====================================================================
        // This is the heart of the simulation, where the engine continuously
        // updates its state, processes input, runs physics, and renders frames.
        std::cout << "Entering engine's main loop..." << std::endl;
        return engine.run(); // Starts the game loop
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
