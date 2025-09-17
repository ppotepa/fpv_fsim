#pragma once

#include "EventBus.h"
#include "World.h"
#include "SimClock.h"
#include "AssetRegistry.h"
#include "AssetPackLoader.h"
#include "../config/PhysicsConfig.h"
#include "../config/RenderConfig.h"

#include <windows.h>
#include <memory>
#include <string>
#include <chrono>

// Forward declarations
class IInputDevice;
class BootstrapSystem;
class WorldGenSystem;
class VisualizationSystem;
class ConsoleSystem;
class AssetHotReloadSystem;
namespace Material
{
    class MaterialManager;
}

/**
 * @class Engine
 * @brief Core engine class that encapsulates the runtime environment.
 *
 * The Engine class provides a high-level interface for initializing,
 * configuring, and running the simulation. It handles system initialization,
 * asset discovery and resolution, and main loop execution while maintaining
 * a clean separation of responsibilities.
 */
class Engine
{
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
    bool initialize(const std::string &physicsConfigPath = "configs/physics_config.json",
                    const std::string &renderConfigPath = "configs/render_config.json",
                    const std::string &inputConfigPath = "configs/input_config.json");

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
     * @brief Load and display a specific scene by ID
     *
     * @param sceneId The ID of the scene to load (e.g., "DeveloperScene")
     * @return true if scene loading and display succeeded
     * @return false if scene loading or display failed
     */
    bool loadAndDisplayScene(const std::string &sceneId);

    /**
     * @brief Update the window title to reflect the current scene
     *
     * @param sceneName The name of the currently loaded scene
     */
    void updateWindowTitle(const std::string &sceneName);

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
    std::unique_ptr<IInputDevice> inputDevice_;

    // Frame timing
    std::chrono::high_resolution_clock::time_point lastFrameTime;
    std::chrono::high_resolution_clock::time_point lastFpsUpdateTime;
    int frameCount;
    float fpsUpdateInterval;

    // Private helper methods
    HWND createWindow();
    static LRESULT CALLBACK windowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT handleWindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Systems management
    void initializeSystems();
    void shutdownSystems();

    // Main loop helpers
    bool processWindowMessages();
    void updateFixedTimestep(float deltaTime);
    void updateVariableTimestep(float deltaTime);
    void updateFrameRate();

    // Error handling helpers
    void keepWindowAlive(const std::string &errorMessage);
};
