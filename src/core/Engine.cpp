#include "Engine.h"
#include "../config/PhysicsConfigParser.h"
#include "../config/RenderConfigParser.h"
#include "../config/InputConfigParser.h"
#include "../physics/ExponentialAirDensityModel.h"
#include "../physics/PerlinWindModel.h"
#include "../physics/ImpulseCollisionResolver.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <iomanip>

// Track frame rateinclude "../physics/PerlinWindModel.h"
#include "../physics/ImpulseCollisionResolver.h"
#include "../systems/PhysicsSystem.h"
#include "../systems/InputSystem.h"
#include "../systems/VehicleControlSystem.h"
#include "../platform/WinInputDevice.h"
#include "../platform/PugiXmlParser.h"

#include <iostream>
#include <chrono>
#include <thread>

Engine::Engine()
    : eventBus(),
      world(eventBus),
      simClock(0.016667f), // Default 60Hz
      assetRegistry(),
      assetLoader(assetRegistry),
      windowHandle(nullptr),
      running(false)
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
    std::cout << "Initializing FPV Flight Simulator Engine..." << std::endl;

    // Load configuration files
    physicsConfig = PhysicsConfigParser::loadFromFile(physicsConfigPath);
    renderConfig = Render::RenderConfigParser::loadFromFile(renderConfigPath);

    // Initialize simulation clock with physics timestep
    simClock = SimClock(physicsConfig.fixedTimestep);

    // Create window
    windowHandle = createWindow();
    if (windowHandle == nullptr)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    // Initialize systems
    initializeSystems();

    // Load input configuration
    InputSystem *inputSystem = world.getSystem<InputSystem>();
    if (inputSystem)
    {
        if (!inputSystem->loadConfiguration(inputConfigPath))
        {
            std::cout << "Warning: Could not load input configuration, using defaults" << std::endl;
        }
    }

    return true;
}

bool Engine::discoverAssets()
{
    std::cout << "Discovering assets..." << std::endl;

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
            std::cout << "No packages found for hot-reload monitoring. "
                      << "You can add packages to assets/packages/ directory." << std::endl;
        }
    }

    // Force-check for DeveloperPackage specifically
    std::filesystem::path devPackagePath = std::filesystem::path("assets/packages/DeveloperPackage/package.xml");
    if (std::filesystem::exists(devPackagePath))
    {
        std::cout << "DeveloperPackage found at: " << devPackagePath << std::endl;
        std::cout << "Make sure this package is properly loaded and its scenes are compiled." << std::endl;
    }
    else
    {
        std::cerr << "Warning: DeveloperPackage not found at expected path: " << devPackagePath << std::endl;
    }

    return true;
}

bool Engine::resolveAssets()
{
    // Asset resolution is currently handled by the BootstrapSystem during Init()
    // This separate method allows for future extension of the resolution pipeline
    return true;
}

bool Engine::displayCompiledScene()
{
    // Scene compilation and display is delegated to the WorldGenSystem and VisualizationSystem
    // These are triggered by events from the BootstrapSystem
    return true;
}

bool Engine::loadAndDisplayScene(const std::string &sceneId)
{
    // Find the WorldGenSystem which is responsible for scene loading
    WorldGenSystem *worldGenSys = world.getSystem<WorldGenSystem>();
    if (!worldGenSys)
    {
        std::cerr << "Error: WorldGenSystem not found in world for scene loading!" << std::endl;
        return false;
    }

    std::cout << "Attempting to load scene: " << sceneId << std::endl;

    // Call the WorldGenSystem's LoadScene method with the specified scene ID
    bool success = worldGenSys->LoadScene(sceneId);

    if (!success)
    {
        std::cerr << "Failed to load scene: " << sceneId << std::endl;
        std::cout << "Falling back to default scene generation..." << std::endl;
        // Attempt to use the default scene as a fallback
        worldGenSys->GenerateDefaultSphereWorld();
    }

    return true; // Even if scene loading failed, we return true because we've fallen back to a default scene
}

int Engine::run()
{
    std::cout << "Running engine main loop..." << std::endl;

    // Validate window handle
    if (windowHandle == nullptr)
    {
        std::cerr << "ERROR: Cannot run main loop - window handle is nullptr!" << std::endl;
        return 1;
    }

    // Show the window
    std::cout << "Showing window..." << std::endl;
    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);

    // Main loop setup - keep it simple
    std::cout << "Initializing main loop..." << std::endl;
    running = true;
    MSG msg = {};

    // Full game loop with proper timing and system updates
    std::cout << "Starting game loop..." << std::endl;

    // Time tracking for variable and fixed timestep
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    auto lastFpsUpdateTime = lastFrameTime;
    float deltaTime = 0.016667f; // Initial delta time (60 FPS)
    int frameCount = 0;
    float fpsUpdateInterval = 1.0f; // Update FPS display every second
    float accumulator = 0.0f;       // For physics fixed timestep

    // Fixed timestep for simulation (already set in constructor)
    const float fixedTimestep = simClock.getFixedTimestep();

    // Get references to important systems
    InputSystem *inputSystem = world.getSystem<InputSystem>();
    PhysicsSystem *physicsSystem = world.getSystem<PhysicsSystem>();
    VisualizationSystem *visualSystem = world.getSystem<VisualizationSystem>();
    AssetHotReloadSystem *hotReloadSystem = world.getSystem<AssetHotReloadSystem>();

    if (!inputSystem || !physicsSystem || !visualSystem || !hotReloadSystem)
    {
        std::cerr << "ERROR: One or more critical systems not found in world!" << std::endl;
        return 1;
    }

    std::cout << "Engine: Starting game loop..." << std::endl;

    // Add a debug flag to track first frame execution
    bool firstFrameCompleted = false;

    try
    {
        while (running)
        {
            // 1. Handle Windows messages (variable timestep)
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    std::cout << "Received WM_QUIT message, exiting..." << std::endl;
                    running = false;
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            // Calculate delta time since last frame
            auto currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
            lastFrameTime = currentTime;

            // Cap the maximum delta time to prevent spiral of death
            if (deltaTime > 0.25f)
                deltaTime = 0.25f;

            // Update simulation clock
            simClock.tick(deltaTime);

            // 2. Fixed Timestep Physics Update Loop (Deterministic Logic)
            try
            {
                while (simClock.shouldStepPhysics())
                {
                    // Update systems that require fixed timestep updates
                    try
                    {
                        // Physics related updates happen in fixed steps
                        physicsSystem->update(world, fixedTimestep);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "ERROR in physics update: " << e.what() << std::endl;
                    }
                    catch (...)
                    {
                        std::cerr << "UNKNOWN ERROR in physics update" << std::endl;
                    }

                    try
                    {
                        // VehicleControlSystem should also run in fixed steps if it depends on physics
                        if (auto vehicleControlSystem = world.getSystem<VehicleControlSystem>())
                        {
                            vehicleControlSystem->update(world, fixedTimestep);
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "ERROR in vehicle control update: " << e.what() << std::endl;
                    }
                    catch (...)
                    {
                        std::cerr << "UNKNOWN ERROR in vehicle control update" << std::endl;
                    }

                    // Any other systems that need fixed-step updates would go here
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "ERROR in fixed timestep loop: " << e.what() << std::endl;
            }
            catch (...)
            {
                std::cerr << "UNKNOWN ERROR in fixed timestep loop" << std::endl;
            }

            // 3. Variable Timestep Updates (Input, Rendering, Non-critical animations)
            try
            {
                // Process input first to ensure responsiveness
                inputSystem->update(world, deltaTime);
            }
            catch (const std::exception &e)
            {
                std::cerr << "ERROR in input system update: " << e.what() << std::endl;
            }
            catch (...)
            {
                std::cerr << "UNKNOWN ERROR in input system update" << std::endl;
            }

            // 4. Render the scene (Variable Timestep)
            try
            {
                // Only update the visualization system separately, not all systems
                std::cout << "Frame " << frameCount << ": Starting visualization update..." << std::endl;

                if (frameCount == 0)
                {
                    // Special handling for the critical first frame
                    std::cout << "FIRST FRAME - Extra debugging:" << std::endl;
                    std::cout << "Visualization system address: " << visualSystem << std::endl;
                    std::cout << "Window handle: " << windowHandle << std::endl;

                    // Add a small delay to make sure window is fully created
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    // Force window to redraw
                    InvalidateRect(windowHandle, NULL, TRUE);
                    UpdateWindow(windowHandle);
                }

                // Call update with detailed error reporting
                std::cout << "Calling visualSystem->update with deltaTime=" << deltaTime << std::endl;

                if (frameCount == 0)
                {
                    // Special handling for first frame - try simpler rendering first
                    std::cout << "Using simplified first frame rendering..." << std::endl;

                    // Just clear the window to show something
                    HDC hdc = GetDC(windowHandle);
                    RECT rect;
                    GetClientRect(windowHandle, &rect);

                    // Fill with blue color to indicate success
                    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 128)); // Dark blue
                    FillRect(hdc, &rect, brush);
                    DeleteObject(brush);
                    ReleaseDC(windowHandle, hdc);

                    // Set success flag to allow engine to continue
                    firstFrameCompleted = true;
                    std::cout << "First frame rendered using GDI fallback" << std::endl;

                    // Add a small delay to show the blue screen
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                else
                {
                    try
                    {
                        // Normal rendering for subsequent frames
                        auto startUpdateTime = std::chrono::high_resolution_clock::now();
                        visualSystem->update(world, deltaTime);
                        auto endUpdateTime = std::chrono::high_resolution_clock::now();
                        float updateDuration = std::chrono::duration<float>(endUpdateTime - startUpdateTime).count();

                        std::cout << "Visualization update completed in " << updateDuration * 1000.0f << "ms!" << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "WARNING: Visualization update inner exception: " << e.what() << std::endl;
                        std::cerr << "Continuing without rendering this frame" << std::endl;
                    }
                    catch (...)
                    {
                        std::cerr << "WARNING: Unknown visualization update inner exception" << std::endl;
                        std::cerr << "Continuing without rendering this frame" << std::endl;
                    }
                }

                if (!firstFrameCompleted)
                {
                    std::cout << "First frame rendered successfully!" << std::endl;
                    firstFrameCompleted = true;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "ERROR in visualization update: " << e.what() << std::endl;
                // Keep running even if visualization fails
                if (!firstFrameCompleted)
                {
                    firstFrameCompleted = true; // Mark as completed to avoid repeated errors
                    std::cerr << "First frame failed, but continuing execution" << std::endl;
                }
            }
            catch (...)
            {
                std::cerr << "UNKNOWN ERROR in visualization update" << std::endl;
                if (!firstFrameCompleted)
                {
                    firstFrameCompleted = true; // Mark as completed to avoid repeated errors
                    std::cerr << "First frame failed with unknown error, but continuing execution" << std::endl;
                }
            }

            // 5. Asset Hot Reloading (End of Frame)
            try
            {
                // This should happen after rendering to maintain determinism
                hotReloadSystem->update(world, deltaTime);
            }
            catch (const std::exception &e)
            {
                std::cerr << "ERROR in hot reload system update: " << e.what() << std::endl;
            }
            catch (...)
            {
                std::cerr << "UNKNOWN ERROR in hot reload system update" << std::endl;
            }

            // Track frame rate and update window title
            frameCount++;
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

            // Add a small delay to prevent CPU thrashing if there's an issue
            if (frameCount < 10)
            {
                // Only add significant delay in the first few frames
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "FATAL ERROR in main game loop: " << e.what() << std::endl;
        // Keep the window open so error can be seen
        keepWindowAlive("Fatal error in main game loop: " + std::string(e.what()));
        return 1;
    }
    catch (...)
    {
        std::cerr << "UNKNOWN FATAL ERROR in main game loop" << std::endl;
        // Keep the window open so error can be seen
        keepWindowAlive("Unknown fatal error occurred in the game loop");
        return 1;
    }

    std::cout << "Main loop exited normally" << std::endl;
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

    std::cout << "Creating window with title: " << renderConfig.getWindowTitle()
              << ", width: " << renderConfig.getWindowWidth()
              << ", height: " << renderConfig.getWindowHeight() << std::endl;

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
        std::cout << "Window resized to " << width << "x" << height << std::endl;

        // Let the game loop handle the resize during the next update cycle
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Engine::initializeSystems()
{
    std::cout << "Initializing simulation systems..." << std::endl;

    // Create physics models
    std::unique_ptr<IAirDensityModel> airDensityModel = std::make_unique<ExponentialAirDensityModel>(
        physicsConfig.seaLevelDensity, physicsConfig.scaleHeight);
    std::unique_ptr<IWindModel> windModel = std::make_unique<PerlinWindModel>(
        physicsConfig.baseWindSpeed, physicsConfig.turbulenceScale,
        physicsConfig.turbulenceIntensity, physicsConfig.randomSeed);
    std::unique_ptr<ICollisionResolver> collisionResolver = std::make_unique<ImpulseCollisionResolver>(
        physicsConfig.restitution, physicsConfig.friction);

    // Create material manager (referenced by multiple systems)
    auto materialManager = std::make_unique<Material::MaterialManager>();
    materialManager->LoadDefaultMaterials();
    Material::MaterialManager *materialManagerPtr = materialManager.get();
    std::cout << "Material manager initialized with default materials" << std::endl;

    // Add systems in the appropriate initialization order
    // 1. First add core systems
    world.addSystem(std::make_unique<PhysicsSystem>(
        eventBus, *airDensityModel, *windModel, *collisionResolver));
    world.addSystem(std::make_unique<InputSystem>(
        eventBus, *std::make_unique<WinInputDevice>()));
    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));
    std::cout << "Core simulation systems initialized" << std::endl;

    // 2. Add asset pipeline systems
    auto bootstrapSystem = std::make_unique<BootstrapSystem>(
        eventBus, world, assetRegistry, assetLoader);
    world.addSystem(std::move(bootstrapSystem));

    auto hotReloadSystem = std::make_unique<AssetHotReloadSystem>(
        assetRegistry, assetLoader);
    world.addSystem(std::move(hotReloadSystem));
    std::cout << "Asset pipeline systems initialized" << std::endl;

    // 3. Add world generation system (depends on assets)
    auto worldGenSystem = std::make_unique<WorldGenSystem>(
        eventBus, world, assetRegistry, *materialManagerPtr);
    world.addSystem(std::move(worldGenSystem));
    std::cout << "World generation system initialized" << std::endl;

    // 4. Add visualization and UI systems (depends on world and material manager)
    auto consoleSystem = std::make_unique<ConsoleSystem>(eventBus);
    world.addSystem(std::move(consoleSystem));

    auto visualizationSystem = std::make_unique<VisualizationSystem>(
        eventBus, world, windowHandle, *materialManagerPtr, renderConfig);
    world.addSystem(std::move(visualizationSystem));
    std::cout << "Visualization systems initialized" << std::endl;

    // Store MaterialManager as a member variable to keep it alive
    world.storeSharedResource("MaterialManager", std::move(materialManager));

    std::cout << "All systems initialized successfully" << std::endl;
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
