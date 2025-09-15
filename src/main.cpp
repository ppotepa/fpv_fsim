#include "core/EventBus.h"
#include "core/World.h"
#include "core/SimClock.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
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
#include "platform/WinInputDevice.h"
#include "utils/PugiXmlParser.h"
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

// Create a proper Windows window
HWND CreateSimulationWindow()
{
    const char CLASS_NAME[] = "FPV_FlightSimWindow";
    
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        return NULL;
    }

    HWND hwnd = CreateWindowExA(
        0,                      // Optional window styles
        CLASS_NAME,             // Window class
        "FPV Flight Sim - Procedural Earth World",    // Window text
        WS_OVERLAPPEDWINDOW,    // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,        // Size and position
        NULL,       // Parent window    
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
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
    SimClock simClock(1.0f / 60.0f); // 60Hz physics
    World world(eventBus);

    // Asset system initialization
    AssetRegistry assetRegistry;
    AssetPackLoader assetLoader(assetRegistry);

    // Concrete implementations of physics models
    std::unique_ptr<IAirDensityModel> airDensityModel = std::make_unique<ExponentialAirDensityModel>(1.225f, 8500.0f);
    std::unique_ptr<IWindModel> windModel = std::make_unique<PerlinWindModel>(5.0f, 100.0f, 10.0f, 12345);
    std::unique_ptr<ICollisionResolver> collisionResolver = std::make_unique<ImpulseCollisionResolver>(0.2f, 0.8f);

    // Concrete implementation of input device
    std::unique_ptr<IInputDevice> inputDevice = std::make_unique<WinInputDevice>();

    // Concrete implementation of XML parser
    std::unique_ptr<IXmlParser> xmlParser = std::make_unique<PugiXmlParser>();

    // Instantiate and inject systems
    world.addSystem(std::make_unique<PhysicsSystem>(eventBus, *airDensityModel, *windModel, *collisionResolver));
    world.addSystem(std::make_unique<InputSystem>(eventBus, *inputDevice));
    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));

    // Create proper window for visualization
    HWND hwnd = CreateSimulationWindow();
    if (hwnd == NULL)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }

    // Asset and bootstrap systems
    auto bootstrapSystem = std::make_unique<BootstrapSystem>(eventBus, world, assetRegistry, assetLoader);
    auto worldGenSystem = std::make_unique<WorldGenSystem>(eventBus, world, assetRegistry);
    auto consoleSystem = std::make_unique<ConsoleSystem>(eventBus);
    auto visualizationSystem = std::make_unique<VisualizationSystem>(eventBus, world, hwnd);
    auto hotReloadSystem = std::make_unique<AssetHotReloadSystem>(assetRegistry, assetLoader);

    world.addSystem(std::move(bootstrapSystem));
    world.addSystem(std::move(worldGenSystem));
    world.addSystem(std::move(consoleSystem));
    world.addSystem(std::move(visualizationSystem));
    world.addSystem(std::move(hotReloadSystem));

    // Initialize bootstrap system (BootstrapSystem is at index 3)
    static_cast<BootstrapSystem *>(world.getSystems()[3].get())->Init();

    // Setup hot reload watching (AssetHotReloadSystem is at index 7)
    static_cast<AssetHotReloadSystem *>(world.getSystems()[7].get())->watchPackage("assets/packages/DeveloperPackage/package.xml");

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
        
        if (!running) break;

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
