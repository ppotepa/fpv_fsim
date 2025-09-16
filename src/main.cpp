#include "core/Engine.h"
#include <iostream>
#include <exception>

/**
 * @brief Main entry point for the FPV Flight Simulator
 * 
 * This function serves strictly as a bootstrap layer, establishing the minimal
 * runtime environment needed for the engine. Its only responsibilities are:
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
    try {
        // Create the engine instance
        Engine engine;
        
        // Initialize the engine with default config paths
        if (!engine.initialize("configs/physics_config.xml", 
                              "configs/render_config.xml", 
                              "configs/input_config.xml")) {
            std::cerr << "Failed to initialize engine" << std::endl;
            return 1;
        }
        
        // Discover assets from development directories
        if (!engine.discoverAssets()) {
            std::cerr << "Failed to discover assets" << std::endl;
            return 1;
        }
        
        // Resolve assets into runtime resources
        if (!engine.resolveAssets()) {
            std::cerr << "Failed to resolve assets" << std::endl;
            return 1;
        }
        
        // Request scene compilation and display
        if (!engine.displayCompiledScene()) {
            std::cerr << "Failed to display compiled scene" << std::endl;
            return 1;
        }
        
        // Run the engine's main loop
        return engine.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}
