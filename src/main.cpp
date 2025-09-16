#include "core/EventBus.h"
#include "core/World.h"
#include "core/SimClock.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include "config/PhysicsConfigParser.h"
#include "config/RenderConfigParser.h"
#include "config/InputConfigParser.h"
#include "physics/ExponentialAirDensityModel.h"
#include "physics/PerlinWindModel.h"
#include "physics/ImpulseCollisionResolver.h"
#include "systems/PhysicsSystem.h"
#include "systems/InputSystem.h"
#include "systems/VehicleControlSystem.h"
#include "systems/BootstrapSystem.h"
#include "systems/WorldGenSystem.h"
#include "systems/ConsoleSystem.h"
#include "systems/VisualizationSystem.h"
#include "systems/AssetHotReloadSystem.h"
#include "systems/MaterialManager.h"
#include "platform/WinInputDevice.h"
#include "platform/PugiXmlParser.h"
#include "utils/IXmlParserUnified.h"
#include "vehicles/DroneBuilder.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

// Window procedure for handling messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // Fill with dark blue background
        HBRUSH brush = CreateSolidBrush(RGB(20, 30, 50));
        FillRect(hdc, &ps.rcPaint, brush);
        DeleteObject(brush);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Create a proper Windows window using configurable parameters
HWND CreateSimulationWindow(const Render::RenderConfiguration &renderConfig)
{
    const char CLASS_NAME[] = "FPV_FlightSimWindow";

    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        return NULL;
    }

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
        NULL                                   // Additional application data
    );

    if (hwnd != NULL)
    {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }

    return hwnd;
}

int main()
{
    // Simulation init
    EventBus eventBus;

    // Load configuration from XML files
    PhysicsConfig physicsConfig = PhysicsConfigParser::loadFromFile("configs/physics_config.xml");
    Render::RenderConfiguration renderConfig = Render::RenderConfigParser::loadFromFile("configs/render_config.xml");

    SimClock simClock(physicsConfig.fixedTimestep);
    World world(eventBus);

    // Asset system initialization
    AssetRegistry assetRegistry;
    AssetPackLoader assetLoader(assetRegistry);

    // Concrete implementations of physics models using configuration
    std::unique_ptr<IAirDensityModel> airDensityModel = std::make_unique<ExponentialAirDensityModel>(
        physicsConfig.seaLevelDensity, physicsConfig.scaleHeight);
    std::unique_ptr<IWindModel> windModel = std::make_unique<PerlinWindModel>(
        physicsConfig.baseWindSpeed, physicsConfig.turbulenceScale,
        physicsConfig.turbulenceIntensity, physicsConfig.randomSeed);
    std::unique_ptr<ICollisionResolver> collisionResolver = std::make_unique<ImpulseCollisionResolver>(
        physicsConfig.restitution, physicsConfig.friction);

    // Concrete implementation of input device
    std::unique_ptr<IInputDevice> inputDevice = std::make_unique<WinInputDevice>();

    // Concrete implementation of XML parser
    std::unique_ptr<IXmlParserUnified> xmlParser = std::make_unique<PugiXmlParser>();

    // Instantiate and inject systems
    world.addSystem(std::make_unique<PhysicsSystem>(eventBus, *airDensityModel, *windModel, *collisionResolver));

    // Create and configure input system
    auto inputSystem = std::make_unique<InputSystem>(eventBus, *inputDevice);

    // Load input configuration
    if (!inputSystem->loadConfiguration("configs/input_config.xml"))
    {
        std::cout << "Warning: Could not load input configuration, using defaults" << std::endl;
    }

    world.addSystem(std::move(inputSystem));
    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));

    // Create proper window for visualization using configurable parameters
    HWND hwnd = CreateSimulationWindow(renderConfig);
    if (hwnd == NULL)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }

    // Asset and bootstrap systems
    auto materialManager = std::make_unique<Material::MaterialManager>();
    materialManager->LoadDefaultMaterials();

    // Keep reference to MaterialManager before moving systems to world
    Material::MaterialManager *materialManagerPtr = materialManager.get();

    auto bootstrapSystem = std::make_unique<BootstrapSystem>(eventBus, world, assetRegistry, assetLoader);
    auto worldGenSystem = std::make_unique<WorldGenSystem>(eventBus, world, assetRegistry, *materialManagerPtr);
    auto consoleSystem = std::make_unique<ConsoleSystem>(eventBus);
    auto visualizationSystem = std::make_unique<VisualizationSystem>(eventBus, world, hwnd, *materialManagerPtr, renderConfig);
    auto hotReloadSystem = std::make_unique<AssetHotReloadSystem>(assetRegistry, assetLoader);

    world.addSystem(std::move(bootstrapSystem));
    world.addSystem(std::move(worldGenSystem));
    world.addSystem(std::move(consoleSystem));
    world.addSystem(std::move(visualizationSystem));
    world.addSystem(std::move(hotReloadSystem));

    // Store MaterialManager separately to ensure it stays alive
    auto sharedMaterialManager = std::move(materialManager);

    // Initialize bootstrap system using type-safe system retrieval
    BootstrapSystem *bootstrapSys = world.getSystem<BootstrapSystem>();
    if (bootstrapSys)
    {
        bootstrapSys->Init();
    }
    else
    {
        std::cerr << "Error: BootstrapSystem not found in world!" << std::endl;
        return 1;
    }

    // Setup hot reload watching - auto-discover all packages instead of hardcoding specific paths
    AssetHotReloadSystem *hotReloadSys = world.getSystem<AssetHotReloadSystem>();
    if (hotReloadSys)
    {
        int discoveredPackages = hotReloadSys->watchAllPackages();
        if (discoveredPackages == 0)
        {
            std::cout << "No packages found for hot-reload monitoring. You can add packages to assets/packages/ directory." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: AssetHotReloadSystem not found in world!" << std::endl;
        return 1;
    }

    // Use builder to create entity
    // DroneBuilder droneBuilder(*xmlParser);
    // std::unique_ptr<Entity> drone = droneBuilder.build("configs/drone_default.xml", eventBus);
    // world.addEntity(std::move(drone));

    // Main simulation loop
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    float angle = 0.0f;
    MSG msg = {};
    bool running = true;

    while (running)
    {
        // Handle Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (!running)
            break;

        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        simClock.tick(frameDeltaTime.count());
        while (simClock.shouldStepPhysics())
        {
            world.update(simClock.getFixedTimestep());
        }

        // Rendering simulation of rotating Earth sphere
        std::cout << "Earth sphere rotating at angle " << angle << " degrees" << std::endl;
        angle += 1.0f;

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    return 0;
}
