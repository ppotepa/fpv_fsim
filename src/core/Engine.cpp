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
      running(false) {
}

Engine::~Engine() {
    shutdownSystems();
    
    // Clean up window
    if (windowHandle != nullptr) {
        DestroyWindow(windowHandle);
    }
}

bool Engine::initialize(const std::string& physicsConfigPath,
                      const std::string& renderConfigPath,
                      const std::string& inputConfigPath) {
    std::cout << "Initializing FPV Flight Simulator Engine..." << std::endl;

    // Load configuration files
    physicsConfig = PhysicsConfigParser::loadFromFile(physicsConfigPath);
    renderConfig = Render::RenderConfigParser::loadFromFile(renderConfigPath);

    // Initialize simulation clock with physics timestep
    simClock = SimClock(physicsConfig.fixedTimestep);
    
    // Create window
    windowHandle = createWindow();
    if (windowHandle == nullptr) {
        std::cerr << "Failed to create window!" << std::endl;
        return false;
    }

    // Initialize systems
    initializeSystems();
    
    // Load input configuration
    InputSystem* inputSystem = world.getSystem<InputSystem>();
    if (inputSystem) {
        if (!inputSystem->loadConfiguration(inputConfigPath)) {
            std::cout << "Warning: Could not load input configuration, using defaults" << std::endl;
        }
    }
    
    return true;
}

bool Engine::discoverAssets() {
    std::cout << "Discovering assets..." << std::endl;
    
    // Delegate asset discovery to the BootstrapSystem
    BootstrapSystem* bootstrapSys = world.getSystem<BootstrapSystem>();
    if (!bootstrapSys) {
        std::cerr << "Error: BootstrapSystem not found in world!" << std::endl;
        return false;
    }
    
    // Initialize bootstrap system which handles asset discovery
    bootstrapSys->Init();
    
    // Setup asset hot-reload
    AssetHotReloadSystem* hotReloadSys = world.getSystem<AssetHotReloadSystem>();
    if (hotReloadSys) {
        int discoveredPackages = hotReloadSys->watchAllPackages();
        if (discoveredPackages == 0) {
            std::cout << "No packages found for hot-reload monitoring. "
                      << "You can add packages to assets/packages/ directory." << std::endl;
        }
    }
    
    return true;
}

bool Engine::resolveAssets() {
    // Asset resolution is currently handled by the BootstrapSystem during Init()
    // This separate method allows for future extension of the resolution pipeline
    return true;
}

bool Engine::displayCompiledScene() {
    // Scene compilation and display is delegated to the WorldGenSystem and VisualizationSystem
    // These are triggered by events from the BootstrapSystem
    return true;
}

int Engine::run() {
    std::cout << "Running engine main loop..." << std::endl;
    
    // Validate window handle
    if (windowHandle == nullptr) {
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
    
    // Simple message-only loop to get us running
    std::cout << "Starting simple message loop..." << std::endl;
    while (running) {
        // Handle Windows messages
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                std::cout << "Received WM_QUIT message, exiting..." << std::endl;
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // Minimal processing - just sleep to prevent CPU usage
        Sleep(16); // About 60 frames per second
    }
    
    std::cout << "Main loop exited normally" << std::endl;
    return 0;
}

HWND Engine::createWindow() {
    const char CLASS_NAME[] = "FPV_FlightSimWindow";

    // Register window class
    WNDCLASSA wc = {};
    wc.lpfnWndProc = Engine::windowProcStatic;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc)) {
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
    
    if (hwnd == nullptr) {
        std::cerr << "ERROR: Failed to create window! Error code: " << GetLastError() << std::endl;
    }

    return hwnd;
}

LRESULT CALLBACK Engine::windowProcStatic(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Get the Engine instance
    if (uMsg == WM_CREATE) {
        CREATESTRUCTA* createStruct = reinterpret_cast<CREATESTRUCTA*>(lParam);
        SetWindowLongPtrA(hwnd, GWLP_USERDATA, 
            reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
    }
    
    // Forward to instance method
    Engine* engine = reinterpret_cast<Engine*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
    if (engine) {
        return engine->handleWindowMessage(hwnd, uMsg, wParam, lParam);
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Engine::handleWindowMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
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

void Engine::initializeSystems() {
    // Create physics models
    std::unique_ptr<IAirDensityModel> airDensityModel = std::make_unique<ExponentialAirDensityModel>(
        physicsConfig.seaLevelDensity, physicsConfig.scaleHeight);
    std::unique_ptr<IWindModel> windModel = std::make_unique<PerlinWindModel>(
        physicsConfig.baseWindSpeed, physicsConfig.turbulenceScale,
        physicsConfig.turbulenceIntensity, physicsConfig.randomSeed);
    std::unique_ptr<ICollisionResolver> collisionResolver = std::make_unique<ImpulseCollisionResolver>(
        physicsConfig.restitution, physicsConfig.friction);

    // Add core systems
    world.addSystem(std::make_unique<PhysicsSystem>(
        eventBus, *airDensityModel, *windModel, *collisionResolver));
    world.addSystem(std::make_unique<InputSystem>(
        eventBus, *std::make_unique<WinInputDevice>()));
    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));

    // Create material manager (referenced by multiple systems)
    auto materialManager = std::make_unique<Material::MaterialManager>();
    materialManager->LoadDefaultMaterials();
    Material::MaterialManager* materialManagerPtr = materialManager.get();

    // Add asset pipeline and rendering systems
    auto bootstrapSystem = std::make_unique<BootstrapSystem>(
        eventBus, world, assetRegistry, assetLoader);
    auto worldGenSystem = std::make_unique<WorldGenSystem>(
        eventBus, world, assetRegistry, *materialManagerPtr);
    auto consoleSystem = std::make_unique<ConsoleSystem>(eventBus);
    auto visualizationSystem = std::make_unique<VisualizationSystem>(
        eventBus, world, windowHandle, *materialManagerPtr, renderConfig);
    auto hotReloadSystem = std::make_unique<AssetHotReloadSystem>(
        assetRegistry, assetLoader);

    // Add systems to world
    world.addSystem(std::move(bootstrapSystem));
    world.addSystem(std::move(worldGenSystem));
    world.addSystem(std::move(consoleSystem));
    world.addSystem(std::move(visualizationSystem));
    world.addSystem(std::move(hotReloadSystem));
    
    // Store MaterialManager as a member variable to keep it alive
    world.storeSharedResource("MaterialManager", std::move(materialManager));
}

void Engine::shutdownSystems() {
    // World destructor will handle system shutdown
}
