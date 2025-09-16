#pragma once

#include "EventBus.h"
#include "World.h"
#include "SimClock.h"
#include "AssetRegistry.h"
#include "AssetPackLoader.h"
#include "../systems/BootstrapSystem.h"
#include "../systems/WorldGenSystem.h"
#include "../systems/VisualizationSystem.h"
#include "../systems/ConsoleSystem.h"
#include "../systems/AssetHotReloadSystem.h"
#include "../systems/MaterialManager.h"
#include "../physics/IAirDensityModel.h"
#include "../physics/IWindModel.h"
#include "../physics/ICollisionResolver.h"
#include "../platform/IInputDevice.h"
#include "../utils/IXmlParserUnified.h"
#include "../config/PhysicsConfig.h"
#include "../config/RenderConfig.h"

#include <windows.h>
#include <memory>

/**
 * @class Engine
 * @brief Core engine class that encapsulates the runtime environment.
 * 
 * The Engine class provides a high-level interface for initializing,
 * configuring, and running the simulation. It handles system initialization,
 * asset discovery and resolution, and main loop execution while maintaining
 * a clean separation of responsibilities.
 */
class Engine {
public:
    /**
     * @brief Construct a new Engine instance
     */
    Engine();

    /**
     * @brief Destroy the Engine instance and clean up resources
     */
    ~Engine();

    /**
     * @brief Initialize the engine with configuration files
     * 
     * @param physicsConfigPath Path to physics configuration file
     * @param renderConfigPath Path to render configuration file
     * @param inputConfigPath Path to input configuration file
     * @return true if initialization succeeded
     * @return false if initialization failed
     */
    bool initialize(const std::string& physicsConfigPath = "configs/physics_config.xml",
                   const std::string& renderConfigPath = "configs/render_config.xml",
                   const std::string& inputConfigPath = "configs/input_config.xml");

    /**
     * @brief Discover and load assets from development directories
     * 
     * @return true if asset discovery succeeded
     * @return false if asset discovery failed
     */
    bool discoverAssets();

    /**
     * @brief Resolve assets into usable runtime resources
     * 
     * @return true if asset resolution succeeded
     * @return false if asset resolution failed
     */
    bool resolveAssets();

    /**
     * @brief Request and display a compiled scene
     * 
     * @return true if scene compilation and display succeeded
     * @return false if scene compilation or display failed
     */
    bool displayCompiledScene();

    /**
     * @brief Run the engine's main loop
     * 
     * @return Exit code (0 for success)
     */
    int run();

private:
    // Core systems
    EventBus eventBus;
    World world;
    SimClock simClock;
    AssetRegistry assetRegistry;
    AssetPackLoader assetLoader;

    // Configuration
    Physics::PhysicsConfig physicsConfig;
    Render::RenderConfiguration renderConfig;

    // Platform components
    HWND windowHandle;
    bool running;

    // Private helper methods
    HWND createWindow();
    static LRESULT CALLBACK windowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT handleWindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Systems management
    void initializeSystems();
    void shutdownSystems();
};
