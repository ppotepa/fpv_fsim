#include "Engine.h"
#include "../config/PhysicsConfigParser.h"
#include "../config/RenderConfigParser.h"
#include "../config/InputConfigParser.h"
#include "../physics/ExponentialAirDensityModel.h"
#include "../physics/PerlinWindModel.h"
#include "../physics/ImpulseCollisionResolver.h"
#include "../systems/PhysicsSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/VehicleControlSystem.h"
#include "../systems/BootstrapSystem.h"
#include "../systems/WorldGenSystem.h"
#include "../systems/VisualizationSystem.h"
#include "../systems/ConsoleSystem.h"
#include "../systems/AssetHotReloadSystem.h"
#include "../systems/MaterialManager.h"
#include "../platform/WinInputDevice.h"
#include "../platform/PugiXmlParser.h"
#include "../debug.h"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

Engine::Engine()
    : eventBus(),
      world(eventBus),
      simClock(0.016667f), // Default 60Hz
      assetRegistry(),
      assetLoader(assetRegistry),
      windowHandle(nullptr),
      running(false),
      frameCount(0),
      fpsUpdateInterval(1.0f)
{
}

Engine::~Engine()
{
    shutdownSystems();

    // Clean up window
    if (windowHandle != nullptr)
    {
        DestroyWindow(windowHandle);
    }
}

bool Engine::initialize(const std::string &physicsConfigPath,
                        const std::string &renderConfigPath,
                        const std::string &inputConfigPath)
{
    DEBUG_LOG("Initializing FPV Flight Simulator Engine...");

    // Load configuration files
    DEBUG_LOG("Loading physics config from " + physicsConfigPath);
    physicsConfig = PhysicsConfigParser::loadFromFile(physicsConfigPath);
    DEBUG_LOG("Loading render config from " + renderConfigPath);
    renderConfig = Render::RenderConfigParser::loadFromFile(renderConfigPath);

    // Initialize simulation clock with physics timestep
    simClock = SimClock(physicsConfig.fixedTimestep);

    // Create window
    DEBUG_LOG("Creating window");
    windowHandle = createWindow();
    if (windowHandle == nullptr)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    // Initialize systems
    DEBUG_LOG("Initializing systems");
    initializeSystems();

    // Load input configuration
    DEBUG_LOG("Loading input configuration from " + inputConfigPath);
    InputSystem *inputSystem = world.getSystem<InputSystem>();
    if (inputSystem)
    {
        if (!inputSystem->loadConfiguration(inputConfigPath))
        {
            DEBUG_LOG("Warning: Could not load input configuration, using defaults");
        }
    }

    return true;
}

bool Engine::discoverAssets()
{
    DEBUG_LOG("Discovering assets...");

    // Delegate asset discovery to the BootstrapSystem
    BootstrapSystem *bootstrapSys = world.getSystem<BootstrapSystem>();
    if (!bootstrapSys)
    {
        std::cerr << "Error: BootstrapSystem not found in world!" << std::endl;
        return false;
    }

    // Initialize bootstrap system which handles asset discovery
    bootstrapSys->Init();

    // Setup asset hot-reload
    AssetHotReloadSystem *hotReloadSys = world.getSystem<AssetHotReloadSystem>();
    if (hotReloadSys)
    {
        int discoveredPackages = hotReloadSys->watchAllPackages();
        if (discoveredPackages == 0)
        {
            DEBUG_LOG("No packages found for hot-reload monitoring. You can add packages to assets/packages/ directory.");
        }
    }

    // Force-check for DeveloperPackage specifically
    std::filesystem::path devPackagePath = std::filesystem::path("assets/packages/DeveloperPackage/package.xml");
    if (std::filesystem::exists(devPackagePath))
    {
        DEBUG_LOG("DeveloperPackage found at: " + devPackagePath.string() + ". Make sure this package is properly loaded and its scenes are compiled.");
    }
    else
    {
        std::cerr << "Warning: DeveloperPackage not found at expected path: " << devPackagePath << std::endl;
    }

    return true;
}

bool Engine::resolveAssets()
{
    DEBUG_LOG("Resolving assets...");
    // Asset resolution is currently handled by the BootstrapSystem during Init()
    // This separate method allows for future extension of the resolution pipeline
    return true;
}

bool Engine::displayCompiledScene()
{
    DEBUG_LOG("Displaying compiled scene...");
    // Scene compilation and display is delegated to the WorldGenSystem and VisualizationSystem
    // These are triggered by events from the BootstrapSystem
    return true;
}

bool Engine::loadAndDisplayScene(const std::string &sceneId)
{
    DEBUG_LOG("Loading and displaying scene: " + sceneId);
    // Find the WorldGenSystem which is responsible for scene loading
    WorldGenSystem *worldGenSys = world.getSystem<WorldGenSystem>();
    if (!worldGenSys)
    {
        std::cerr << "Error: WorldGenSystem not found in world for scene loading!" << std::endl;
        return false;
    }

    DEBUG_LOG("Attempting to load scene: " + sceneId);

    // Call the WorldGenSystem's LoadScene method with the specified scene ID
    bool success = worldGenSys->LoadScene(sceneId);

    if (!success)
    {
        DEBUG_LOG("Failed to load scene: " + sceneId + ". Falling back to default scene generation...");
        // Attempt to use the default scene as a fallback
        worldGenSys->GenerateDefaultSphereWorld();
    }

    return true; // Even if scene loading failed, we return true because we've fallen back to a default scene
}

int Engine::run()
{
    DEBUG_LOG("Running engine main loop...");

    if (windowHandle == nullptr)
    {
        std::cerr << "ERROR: Cannot run main loop - window handle is nullptr!" << std::endl;
        return 1;
    }

    // Show window and initialize timing
    DEBUG_LOG("Showing window...");
    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);

    running = true;
    lastFrameTime = std::chrono::high_resolution_clock::now();
    lastFpsUpdateTime = lastFrameTime;

    DEBUG_LOG("=== ENTERING MAIN GAME LOOP ===");

    try
    {
        while (running)
        {
            // Process Windows messages
            if (!processWindowMessages())
                break;

            // Calculate delta time
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
            lastFrameTime = currentTime;

            // Cap delta time to prevent spiral of death
            if (deltaTime > 0.25f)
                deltaTime = 0.25f;

            // Update simulation clock
            simClock.tick(deltaTime);

            // Fixed timestep updates (physics)
            updateFixedTimestep(deltaTime);

            // Variable timestep updates (input, rendering)
            updateVariableTimestep(deltaTime);

            // Update frame rate display
            updateFrameRate();

            // Small delay for first few frames
            if (frameCount < 10)
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "FATAL ERROR in main game loop: " << e.what() << std::endl;
        keepWindowAlive("Fatal error in main game loop: " + std::string(e.what()));
        return 1;
    }
    catch (...)
    {
        std::cerr << "UNKNOWN FATAL ERROR in main game loop" << std::endl;
        keepWindowAlive("Unknown fatal error occurred in the game loop");
        return 1;
    }

    DEBUG_LOG("=== MAIN LOOP EXITED ===");
    return 0;
}

HWND Engine::createWindow()
{
    const char CLASS_NAME[] = "FPV_FlightSimWindow";

    // Register window class
    WNDCLASSA wc = {};
    wc.lpfnWndProc = Engine::windowProcStatic;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        std::cerr << "ERROR: Failed to register window class! Error code: " << GetLastError() << std::endl;
        return nullptr;
    }

    DEBUG_LOG("Creating window with title: " + renderConfig.getWindowTitle() + ", width: " + std::to_string(renderConfig.getWindowWidth()) + ", height: " + std::to_string(renderConfig.getWindowHeight()));

    // Create window
    HWND hwnd = CreateWindowExA(
        0,                                     // Optional window styles
        CLASS_NAME,                            // Window class
        renderConfig.getWindowTitle().c_str(), // Window text from config
        WS_OVERLAPPEDWINDOW,                   // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,          // Position
        renderConfig.getWindowWidth(),         // Width from config
        renderConfig.getWindowHeight(),        // Height from config
        NULL,                                  // Parent window
        NULL,                                  // Menu
        GetModuleHandle(NULL),                 // Instance handle
        this                                   // Additional data - pass this pointer
    );

    if (hwnd == nullptr)
    {
        std::cerr << "ERROR: Failed to create window! Error code: " << GetLastError() << std::endl;
    }

    return hwnd;
}

LRESULT CALLBACK Engine::windowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Get the Engine instance
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCTA *createStruct = reinterpret_cast<CREATESTRUCTA *>(lParam);
        SetWindowLongPtrA(hwnd, GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
    }

    // Forward to instance method
    Engine *engine = reinterpret_cast<Engine *>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
    if (engine)
    {
        return engine->handleWindowMessage(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Engine::handleWindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        // For OpenGL rendering, we don't need to do anything here
        // Just validate the update region to prevent Windows from sending more WM_PAINT messages
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_SIZE:
    {
        // Handle window resize - important for OpenGL viewport
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // Store the new dimensions for the rendering system
        DEBUG_LOG("Window resized to " + std::to_string(width) + "x" + std::to_string(height));

        // Let the game loop handle the resize during the next update cycle
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Engine::initializeSystems()
{
    DEBUG_LOG("Initializing simulation systems...");

    // Initialize physics models
    auto airDensityModel = std::make_unique<ExponentialAirDensityModel>(
        physicsConfig.seaLevelDensity, physicsConfig.scaleHeight);
    auto windModel = std::make_unique<PerlinWindModel>(
        physicsConfig.baseWindSpeed, physicsConfig.turbulenceScale,
        physicsConfig.turbulenceIntensity, physicsConfig.randomSeed);
    auto collisionResolver = std::make_unique<ImpulseCollisionResolver>(
        physicsConfig.restitution, physicsConfig.friction);

    // Initialize material manager
    auto materialManager = std::make_unique<Material::MaterialManager>();
    materialManager->LoadDefaultMaterials();
    Material::MaterialManager *materialManagerPtr = materialManager.get();
    DEBUG_LOG("Material manager initialized with default materials");

    // Add core systems
    world.addSystem(std::make_unique<PhysicsSystem>(
        eventBus, *airDensityModel, *windModel, *collisionResolver));

    inputDevice_ = std::make_unique<WinInputDevice>();
    world.addSystem(std::make_unique<InputSystem>(eventBus, *inputDevice_));

    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));
    DEBUG_LOG("Core simulation systems initialized");

    // Add asset pipeline systems
    world.addSystem(std::make_unique<BootstrapSystem>(
        eventBus, world, assetRegistry, assetLoader));
    world.addSystem(std::make_unique<AssetHotReloadSystem>(
        assetRegistry, assetLoader));
    DEBUG_LOG("Asset pipeline systems initialized");

    // Add world generation system
    world.addSystem(std::make_unique<WorldGenSystem>(
        eventBus, world, assetRegistry, *materialManagerPtr));
    DEBUG_LOG("World generation system initialized");

    // Add UI and visualization systems
    world.addSystem(std::make_unique<ConsoleSystem>(eventBus));
    world.addSystem(std::make_unique<VisualizationSystem>(
        eventBus, world, windowHandle, *materialManagerPtr, renderConfig));
    DEBUG_LOG("Visualization systems initialized");

    // Store MaterialManager to keep it alive
    world.storeSharedResource("MaterialManager", std::move(materialManager));

    DEBUG_LOG("All systems initialized successfully");
}

void Engine::shutdownSystems()
{
    // World destructor will handle system shutdown
}

void Engine::keepWindowAlive(const std::string &errorMessage)
{
    // Show error dialog
    MessageBoxA(windowHandle, errorMessage.c_str(), "Error in Simulation", MB_ICONERROR | MB_OK);

    // Keep processing messages to prevent window from appearing to freeze
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            break;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Engine::processWindowMessages()
{
    MSG msg = {};
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            DEBUG_LOG("WM_QUIT received - exiting main loop");
            running = false;
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

void Engine::updateFixedTimestep(float deltaTime)
{
    // Get system references
    PhysicsSystem *physicsSystem = world.getSystem<PhysicsSystem>();
    VehicleControlSystem *vehicleControlSystem = world.getSystem<VehicleControlSystem>();

    const float fixedTimestep = simClock.getFixedTimestep();
    int physicsSteps = 0;

    // Run physics updates at fixed timestep
    while (simClock.shouldStepPhysics())
    {
        physicsSteps++;

        try
        {
            if (physicsSystem)
                physicsSystem->update(world, fixedTimestep);

            if (vehicleControlSystem)
                vehicleControlSystem->update(world, fixedTimestep);
        }
        catch (const std::exception &e)
        {
            std::cerr << "ERROR in fixed timestep update: " << e.what() << std::endl;
        }
    }
}

void Engine::updateVariableTimestep(float deltaTime)
{
    // Get system references
    InputSystem *inputSystem = world.getSystem<InputSystem>();
    VisualizationSystem *visualSystem = world.getSystem<VisualizationSystem>();
    AssetHotReloadSystem *hotReloadSystem = world.getSystem<AssetHotReloadSystem>();

    try
    {
        // Update input system
        if (inputSystem)
            inputSystem->update(world, deltaTime);

        // Update visualization system
        if (visualSystem)
        {
            auto startTime = std::chrono::high_resolution_clock::now();
            visualSystem->update(world, deltaTime);
            auto endTime = std::chrono::high_resolution_clock::now();

            float duration = std::chrono::duration<float>(endTime - startTime).count();
            if (frameCount % 60 == 0) // Log occasionally
                DEBUG_LOG("Visualization update: " + std::to_string(duration * 1000.0f) + "ms");
        }

        // Update asset hot reload system
        if (hotReloadSystem)
            hotReloadSystem->update(world, deltaTime);
    }
    catch (const std::exception &e)
    {
        std::cerr << "ERROR in variable timestep update: " << e.what() << std::endl;
    }
}

void Engine::updateFrameRate()
{
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    float timeSinceLastFpsUpdate = std::chrono::duration<float>(currentTime - lastFpsUpdateTime).count();

    if (timeSinceLastFpsUpdate >= fpsUpdateInterval)
    {
        float fps = frameCount / timeSinceLastFpsUpdate;
        std::ostringstream oss;
        oss << renderConfig.getWindowTitle() << " - FPS: " << std::fixed << std::setprecision(0) << fps;
        SetWindowTextA(windowHandle, oss.str().c_str());

        frameCount = 0;
        lastFpsUpdateTime = currentTime;
    }
}
