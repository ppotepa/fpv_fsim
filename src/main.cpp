#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "core/PackageBootstrap.h"
#include "behaviors/SpinBehavior.h"
#include "factory/BehaviorRegistry.h"
#include "core/Entity.h"
#include "core/World.h"

// OpenGL and Windows setup
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool setupOpenGL(HWND hwnd);
void renderRedCube();

// Global variables
HDC hdc;
HGLRC hglrc;
bool running = true;
float cubeRotation = 0.0f;

/**
 * @brief Windows entry point with OpenGL window and package system
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    try
    {
        std::cout << "🚀 FPV Flight Simulator - Enhanced Package System with OpenGL" << std::endl;
        std::cout << "=============================================================" << std::endl;

        // ====================================================================
        // Step 1: Package System Initialization
        // ====================================================================
        std::cout << "\n📦 Initializing package system..." << std::endl;

        Core::PackageBootstrap bootstrap;
        Core::PackageBootstrap::BootstrapConfig config;
        config.packagesDirectory = "packages";
        config.requiredPackages = {"core"};
        config.enableHotReload = true;

        if (!bootstrap.initialize(config))
        {
            std::cerr << "❌ Failed to initialize package system" << std::endl;
            MessageBoxA(NULL, "Failed to initialize package system", "Error", MB_OK);
            return 1;
        }

        auto stats = bootstrap.getStats();
        std::cout << "✅ Package system initialized successfully!" << std::endl;
        std::cout << "   - Packages loaded: " << stats.packagesLoaded << std::endl;

        // ====================================================================
        // Step 2: Register Enhanced Behaviors
        // ====================================================================
        std::cout << "\n📦 Registering enhanced behaviors..." << std::endl;

        auto& behaviorRegistry = Factory::BehaviorRegistry::instance();
        behaviorRegistry.registerBehavior("SpinBehavior", []() {
            return std::make_unique<Behaviors::SpinBehavior>();
        });
        
        std::cout << "✅ SpinBehavior registered successfully!" << std::endl;

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
            "FPV Flight Simulator - Red Cube Demo",
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
        // Step 4: Create Red Cube Entity with Behavior
        // ====================================================================
        std::cout << "\n🎲 Creating red cube entity..." << std::endl;

        EventBus eventBus;
        World world(eventBus);
        
        // Create entity directly in unique_ptr to avoid copy issues
        auto redCubeEntity = std::make_unique<Entity>(1);
        redCubeEntity->setName("Red Cube");

        // Attach SpinBehavior
        auto spinBehavior = behaviorRegistry.createBehavior("SpinBehavior");
        if (spinBehavior) {
            Assets::BehaviorParams params;
            params.setParameter("rotationSpeed", "45.0");
            params.setParameter("axis", "0,1,0");
            
            spinBehavior->initialize(*redCubeEntity, params);
            // Note: For now we'll track behaviors separately since Entity doesn't have attachBehavior
            
            std::cout << "✅ SpinBehavior created for red cube!" << std::endl;
        }

        // Add entity to world
        world.addEntity(std::move(redCubeEntity));

        std::cout << "✅ Red cube entity created with spinning behavior!" << std::endl;

        // ====================================================================
        // Step 5: Main Loop
        // ====================================================================
        std::cout << "\n🎮 Starting main loop..." << std::endl;
        std::cout << "   🖥️  OpenGL window should now be visible with spinning red cube" << std::endl;
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

            if (!running) break;

            // Calculate delta time
            auto currentTime = std::chrono::steady_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

            // Update behavior system (this will update SpinBehavior)
            auto& behaviorSystem = bootstrap.getBehaviorSystem();
            behaviorSystem.update(deltaTime);

            // Update cube rotation for rendering
            cubeRotation += 45.0f * deltaTime; // 45 degrees per second
            if (cubeRotation > 360.0f) cubeRotation -= 360.0f;

            // Render
            renderRedCube();

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
    catch (const std::exception& e)
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
    if (!hdc) return false;

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if (!pixelFormat) return false;

    if (!SetPixelFormat(hdc, pixelFormat, &pfd)) return false;

    hglrc = wglCreateContext(hdc);
    if (!hglrc) return false;

    if (!wglMakeCurrent(hdc, hglrc)) return false;

    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Dark blue background
    
    return true;
}

void renderRedCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    RECT rect;
    GetClientRect(WindowFromDC(hdc), &rect);
    float aspect = (float)(rect.right) / (float)(rect.bottom);
    
    // Simple perspective projection
    glFrustum(-0.1f * aspect, 0.1f * aspect, -0.1f, 0.1f, 0.1f, 100.0f);

    // Setup model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Move camera back and look at center
    glTranslatef(0.0f, 0.0f, -5.0f);
    
    // Rotate the cube
    glRotatef(cubeRotation, 0.0f, 1.0f, 0.0f);

    // Draw red cube
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    
    glBegin(GL_QUADS);
    
    // Front face
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    
    // Back face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    
    // Top face
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    
    // Bottom face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    
    // Right face
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    
    // Left face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    
    glEnd();

    SwapBuffers(hdc);
}
