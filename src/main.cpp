#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>

#include "debug.h"
#include "core/PackageBootstrap.h"
#include "core/AssetManager.h"
#include "behaviors/SpinBehavior.h"
#include "behaviors/DebugOverlayBehavior.h"
#include "factory/BehaviorRegistry.h"
#include "core/Entity.h"
#include "core/World.h"

// OpenGL and Windows setup
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool setupOpenGL(HWND hwnd);

// Global variables
HDC hdc;
HGLRC hglrc;
bool running = true;
AssetManager assetManager;

// Include the SceneRenderer
#include "rendering/SceneRenderer.h"
SceneRenderer sceneRenderer;

/**
 * @brief Windows entry point with OpenGL window and package system
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    try
    {
        std::cout << "🚀 FPV Flight Simulator - Enhanced Package System with OpenGL" << std::endl;
        std::cout << "=============================================================" << std::endl;

        // Log current working directory for debugging
        std::filesystem::path currentPath = std::filesystem::current_path();
        DEBUG_LOG("Current working directory: " << currentPath.string());
        std::cout << "Working directory: " << currentPath.string() << std::endl;

        // ====================================================================
        // Step 1: Package System Initialization
        // ====================================================================
        std::cout << "\n📦 Initializing dual asset system..." << std::endl;

        // Initialize the asset manager with internal and user assets paths
        if (!assetManager.initialize("internal_assets", "assets"))
        {
            std::cerr << "❌ INTERNAL ASSETS NOT FOUND" << std::endl;
            std::cerr << "   The internal assets are required but not found." << std::endl;
            MessageBoxA(NULL, "INTERNAL ASSETS NOT FOUND - Required for core functionality", "Error", MB_OK);
            return 1;
        }

        DEBUG_LOG("✅ Dual asset system initialized successfully!");
        DEBUG_LOG("   - Internal assets path: internal_assets");
        DEBUG_LOG("   - User assets path: assets");

        // Initialize the scene renderer with our green cubes scene
        if (!sceneRenderer.initialize("scene.green_cubes", assetManager))
        {
            ERROR_LOG("Failed to initialize scene renderer");
            std::cerr << "❌ Failed to initialize scene renderer" << std::endl;
            return 1;
        }

        std::cout << "\n📦 Initializing package system..." << std::endl;
        DEBUG_LOG("Initializing package system...");

        Core::PackageBootstrap bootstrap;
        Core::PackageBootstrap::BootstrapConfig config;
        config.packagesDirectory = "assets/packages";
        config.requiredPackages = {"core"};
        config.enableHotReload = true;

        DEBUG_LOG("Package configuration:");
        DEBUG_LOG("  - packagesDirectory: " << config.packagesDirectory);
        DEBUG_LOG("  - requiredPackages: core");
        DEBUG_LOG("  - enableHotReload: " << (config.enableHotReload ? "true" : "false"));

        if (!bootstrap.initialize(config))
        {
            ERROR_LOG("CODE PACKAGE NOT PRESENT - core package required");
            ERROR_LOG("The KERNEL package 'core' is required but not found in: " << config.packagesDirectory);
            std::cerr << "❌ CODE PACKAGE NOT PRESENT" << std::endl;
            std::cerr << "   The KERNEL package 'core' is required but not found." << std::endl;
            MessageBoxA(NULL, "CODE PACKAGE NOT PRESENT - core package required", "Error", MB_OK);
            return 1;
        }

        auto stats = bootstrap.getStats();
        DEBUG_LOG("✅ KERNEL package system initialized successfully!");
        DEBUG_LOG("   - Packages loaded: " << stats.packagesLoaded);

        // ====================================================================
        // Step 2: Register Enhanced Behaviors
        // ====================================================================
        DEBUG_LOG("\n📦 Registering enhanced behaviors...");

        auto &behaviorRegistry = Factory::BehaviorRegistry::instance();
        behaviorRegistry.registerBehavior("SpinBehavior", []()
                                          { return std::make_unique<Behaviors::SpinBehavior>(); });
        behaviorRegistry.registerBehavior("DebugOverlayBehavior", []()
                                          { return std::make_unique<DebugOverlayBehavior>(); });

        DEBUG_LOG("✅ SpinBehavior registered successfully!");
        DEBUG_LOG("✅ DebugOverlayBehavior registered successfully!");

        // ====================================================================
        // Step 3: Create OpenGL Window
        // ====================================================================
        std::cout << "\n🖥️ Creating OpenGL window..." << std::endl;

        // Register window class
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = "FPVSimWindow";
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc))
        {
            MessageBoxA(NULL, "Failed to register window class", "Error", MB_OK);
            return 1;
        }

        // Create window
        HWND hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            "FPVSimWindow",
            "FPV Flight Simulator - JSON Package System",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            800, 600,
            NULL, NULL, hInstance, NULL);

        if (!hwnd)
        {
            MessageBoxA(NULL, "Failed to create window", "Error", MB_OK);
            return 1;
        }

        // Setup OpenGL
        if (!setupOpenGL(hwnd))
        {
            MessageBoxA(NULL, "Failed to setup OpenGL", "Error", MB_OK);
            return 1;
        }

        ShowWindow(hwnd, nShowCmd);
        UpdateWindow(hwnd);

        std::cout << "✅ OpenGL window created successfully!" << std::endl;

        // ====================================================================
        // Step 4: Initialize World and Event System
        // ====================================================================
        std::cout << "\n� Initializing world and event system..." << std::endl;

        EventBus eventBus;
        World world(eventBus);

        // All entities should now come from the JSON packages through the WorldGenSystem
        // The SceneRenderer is now configured to load entities from package data
        std::cout << "✅ World and event system initialized - entities will be loaded from packages!" << std::endl;

        // ====================================================================
        // Step 5: Main Loop
        // ====================================================================
        std::cout << "\n🎮 Starting main loop..." << std::endl;
        std::cout << "   🖥️  OpenGL window should now be visible with entities from JSON packages" << std::endl;
        std::cout << "   📦  Red cube and violet cube loaded from assets/packages/core/package.json" << std::endl;
        std::cout << "   ⌨️  Close window to exit" << std::endl;

        MSG msg = {};
        auto lastTime = std::chrono::steady_clock::now();

        while (running)
        {
            // Process Windows messages
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

            // Calculate delta time
            auto currentTime = std::chrono::steady_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

            // Update behavior system (this will update SpinBehavior)
            auto &behaviorSystem = bootstrap.getBehaviorSystem();
            behaviorSystem.update(deltaTime);

            // Update the scene renderer
            sceneRenderer.update(deltaTime);

            // Render the scene
            sceneRenderer.render();

            // Cap frame rate
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
        }

        // ====================================================================
        // Cleanup
        // ====================================================================
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
        ReleaseDC(hwnd, hdc);

        std::cout << "\n✅ Simulation completed successfully!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "\n❌ Fatal error: " << e.what() << std::endl;
        MessageBoxA(NULL, ("Fatal error: " + std::string(e.what())).c_str(), "Error", MB_OK);
        return 1;
    }
    catch (...)
    {
        std::cerr << "\n❌ Unknown fatal error occurred" << std::endl;
        MessageBoxA(NULL, "Unknown fatal error occurred", "Error", MB_OK);
        return 1;
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        running = false;
        PostQuitMessage(0);
        break;
    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        glViewport(0, 0, rect.right, rect.bottom);
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool setupOpenGL(HWND hwnd)
{
    hdc = GetDC(hwnd);
    if (!hdc)
        return false;

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (!pixelFormat)
        return false;

    if (!SetPixelFormat(hdc, pixelFormat, &pfd))
        return false;

    hglrc = wglCreateContext(hdc);
    if (!hglrc)
        return false;

    if (!wglMakeCurrent(hdc, hglrc))
        return false;

    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dark blue background

    return true;
}
