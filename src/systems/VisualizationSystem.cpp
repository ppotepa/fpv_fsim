#include "VisualizationSystem.h"
#include "../core/AssetIds.h"
#include "../debug.h"
#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <unordered_map>

// Component definitions
#include "core/IComponent.h"

struct TransformC : public IComponent
{
    struct Vector3
    {
        float x, y, z;
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    };

    struct Quaternion
    {
        float x, y, z, w;
        Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
        static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }
    };

    Vector3 position;
    Quaternion orientation;
    Vector3 scale;

    TransformC(Vector3 pos = Vector3(), Quaternion rot = Quaternion::Identity(), Vector3 scl = Vector3(1, 1, 1))
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

VisualizationSystem::VisualizationSystem(EventBus &eventBus, World &world, HWND windowHandle, Material::MaterialManager &materialManager, const Render::RenderConfiguration &renderConfig)
    : eventBus(eventBus), worldRef(world), hwnd(windowHandle), materialManager_(materialManager), renderConfig_(renderConfig),
      debugModeActive(false), displayNoPackagesMessage(false), consoleVisible(false), rotationAngle(0.0f)
{
    DEBUG_LOG("Initializing VisualizationSystem with OpenGL rendering...");

    // Initialize OpenGL context
    if (!glContext.Initialize(hwnd))
    {
        std::cerr << "Failed to initialize OpenGL context!" << std::endl;
        return;
    }

    // Initialize OpenGL renderer
    if (!glRenderer.Initialize())
    {
        std::cerr << "Failed to initialize OpenGL renderer!" << std::endl;
        return;
    }

    // Initialize camera
    camera = std::make_shared<CameraConfig>();
    camera->position = {0.0f, 5.0f, 15.0f};  // Position camera higher and further back
    camera->direction = {0.0f, 0.0f, -1.0f}; // Look forward (toward negative Z)
    camera->up = {0.0f, 1.0f, 0.0f};         // Y-up orientation
    camera->fov = 45.0f;
    camera->nearPlane = 0.1f;
    camera->farPlane = 1000.0f;

    DEBUG_LOG("Camera initialized at position (" + std::to_string(camera->position.x) + ", " +
              std::to_string(camera->position.y) + ", " + std::to_string(camera->position.z) + ")");

    // Initialize debug camera
    debugCamera = std::make_unique<DebugCamera>(eventBus);
    debugCamera->setCameraState(
        DebugCamera::Vector3(camera->position.x, camera->position.y, camera->position.z),
        DebugCamera::Vector3(camera->direction.x, camera->direction.y, camera->direction.z),
        DebugCamera::Vector3(camera->up.x, camera->up.y, camera->up.z)
    );

    DEBUG_LOG("Debug camera initialized");

    DEBUG_LOG("OpenGL-based VisualizationSystem initialized successfully");

    // Subscribe to events
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    eventBus.subscribe(EventType::ConsoleVisibilityChanged, [this](const IEvent &event)
                       {
        const auto& visibilityEvent = static_cast<const ConsoleVisibilityChangedEvent&>(event);
        OnConsoleVisibilityChanged(visibilityEvent); });

    eventBus.subscribe(EventType::DebugModeToggled, [this](const IEvent &event)
                       {
        const auto& debugEvent = static_cast<const DebugModeToggled&>(event);
        OnDebugModeToggled(debugEvent); });
}

VisualizationSystem::~VisualizationSystem()
{
    // OpenGL context cleanup is handled by OpenGLContext destructor
}

void VisualizationSystem::update(World &world, float deltaTime)
{
    // Ensure OpenGL context is current
    glContext.MakeCurrent();

    // Update debug camera if active
    if (debugCamera) {
        debugCamera->update(deltaTime);
    }

    // Get window dimensions for camera setup
    RECT rect;
    GetClientRect(hwnd, &rect);
    float aspect = static_cast<float>(rect.right - rect.left) / static_cast<float>(rect.bottom - rect.top);

    // Debug output window size every 600 frames
    static int frameCount = 0;
    if (frameCount++ % 600 == 0)
    {
        DEBUG_LOG("Window dimensions: " + std::to_string(rect.right - rect.left) + "x" +
                  std::to_string(rect.bottom - rect.top) + " (aspect: " + std::to_string(aspect) + ")");
    }

    // Setup 3D camera - use debug camera if debug mode is active, otherwise use normal camera
    if (camera)
    {
        glRenderer.SetupCamera(camera->fov, aspect, camera->nearPlane, camera->farPlane);

        // Use debug camera coordinates if debug mode is active
        if (debugModeActive && debugCamera) {
            const auto& debugState = debugCamera->getCameraState();
            
            // Calculate look-at point based on debug camera position and direction
            float lookAtX = debugState.position.x + debugState.direction.x;
            float lookAtY = debugState.position.y + debugState.direction.y;
            float lookAtZ = debugState.position.z + debugState.direction.z;

            glRenderer.SetCameraView(
                debugState.position.x, debugState.position.y, debugState.position.z,
                lookAtX, lookAtY, lookAtZ,
                debugState.up.x, debugState.up.y, debugState.up.z
            );

            // Debug output for debug camera
            if (frameCount % 300 == 0) {
                DEBUG_LOG("Debug Camera position: (" + std::to_string(debugState.position.x) + ", " +
                          std::to_string(debugState.position.y) + ", " + std::to_string(debugState.position.z) + ")");
                DEBUG_LOG("Debug Camera looking at: (" + std::to_string(lookAtX) + ", " + std::to_string(lookAtY) + ", " + std::to_string(lookAtZ) + ")");
            }
        } else {
            // Use normal camera
            // Calculate look-at point based on camera position and direction
            float lookAtX = camera->position.x + camera->direction.x;
            float lookAtY = camera->position.y + camera->direction.y;
            float lookAtZ = camera->position.z + camera->direction.z;

            glRenderer.SetCameraView(
                camera->position.x, camera->position.y, camera->position.z, // Eye position
                lookAtX, lookAtY, lookAtZ,                                  // Look at point
                camera->up.x, camera->up.y, camera->up.z                    // Up vector
            );

            // Debug output for normal camera
            if (frameCount % 300 == 0) {
                DEBUG_LOG("Camera position: (" + std::to_string(camera->position.x) + ", " +
                          std::to_string(camera->position.y) + ", " + std::to_string(camera->position.z) + ")");
                DEBUG_LOG("Looking at: (" + std::to_string(lookAtX) + ", " + std::to_string(lookAtY) + ", " + std::to_string(lookAtZ) + ")");
            }
        }
    }
    else
    {
        // Fallback camera setup if camera object isn't initialized
        glRenderer.SetupCamera(45.0f, aspect, 0.1f, 100.0f);
        glRenderer.SetCameraView(0.0f, 5.0f, 15.0f, // Eye position
                                 0.0f, 0.0f, 0.0f,  // Look at center
                                 0.0f, 1.0f, 0.0f); // Up vector
    }

    // Begin frame
    glRenderer.BeginFrame();

    // Render entities
    RenderEntities();

    // Render console if visible (simplified for OpenGL transition)
    if (consoleVisible)
    {
        RenderConsole();
    }

    // Render debug mode indicator if debug mode is active
    if (debugModeActive)
    {
        RenderDebugModeIndicator();
    }

    // Render no packages message if needed (simplified for OpenGL transition)
    if (displayNoPackagesMessage)
    {
        RenderNoPackagesMessage();
    }

    // End frame and swap buffers
    glRenderer.EndFrame();
    glContext.SwapBuffers();

    // Update rotation for animation
    rotationAngle += deltaTime * 0.1f;
}

void VisualizationSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    displayNoPackagesMessage = true;
}

void VisualizationSystem::OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event)
{
    consoleVisible = event.isVisible;
}

void VisualizationSystem::OnDebugModeToggled(const DebugModeToggled &event)
{
    debugModeActive = event.isActive;
    
    if (debugModeActive) {
        // Sync debug camera with current camera position when entering debug mode
        if (camera && debugCamera) {
            debugCamera->setCameraState(
                DebugCamera::Vector3(camera->position.x, camera->position.y, camera->position.z),
                DebugCamera::Vector3(camera->direction.x, camera->direction.y, camera->direction.z),
                DebugCamera::Vector3(camera->up.x, camera->up.y, camera->up.z)
            );
        }
        DEBUG_LOG("Debug mode activated - free camera enabled");
    } else {
        DEBUG_LOG("Debug mode deactivated - normal camera resumed");
    }
}

void VisualizationSystem::RenderEntities()
{
    // Debug information - print entity count
    static int frameCount = 0;
    if (frameCount++ % 60 == 0)
    { // Print more frequently for debugging
        DEBUG_LOG("VisualizationSystem: Rendering " + std::to_string(worldRef.getEntities().size()) + " entities");

        // Count entities with required rendering components
        int entitiesWithRenderComponents = 0;
        for (const auto &entity : worldRef.getEntities())
        {
            if (entity->getComponent<TransformC>() && entity->getComponent<RenderableC>())
            {
                entitiesWithRenderComponents++;
            }
        }
        DEBUG_LOG("Entities with rendering components: " + std::to_string(entitiesWithRenderComponents));

        // Output camera position for debugging
        if (camera)
        {
            DEBUG_LOG("Camera position: (" + std::to_string(camera->position.x) + ", " +
                      std::to_string(camera->position.y) + ", " + std::to_string(camera->position.z) + ")");
            DEBUG_LOG("Camera direction: (" + std::to_string(camera->direction.x) + ", " +
                      std::to_string(camera->direction.y) + ", " + std::to_string(camera->direction.z) + ")");
        }
        else
        {
            DEBUG_LOG("WARNING: Camera not initialized!");
        }
    }

    // If no entities to render, show a warning and draw debug shapes
    if (worldRef.getEntities().empty())
    {
        if (frameCount % 60 == 0)
        { // Print more frequently for debugging
            DEBUG_LOG("WARNING: No entities to render in the scene!");
        }
        // Draw a simple debug sphere in the center just to show something
        DrawSphere(0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f); // Red sphere
        DrawSphere(5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f); // Green sphere at X=5
        DrawSphere(0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f); // Blue sphere at Y=5
        return;
    }

    // Render all entities using OpenGL 3D rendering
    for (const auto &entity : worldRef.getEntities())
    {
        auto transform = entity->getComponent<TransformC>();
        auto renderable = entity->getComponent<RenderableC>();

        // Debug output for missing components
        if (!transform && frameCount % 300 == 0)
        {
            DEBUG_LOG("Entity " + std::to_string(entity->getId()) + " missing TransformC component");
        }
        if (!renderable && frameCount % 300 == 0)
        {
            DEBUG_LOG("Entity " + std::to_string(entity->getId()) + " missing RenderableC component");
        }
        if (renderable && !renderable->isVisible && frameCount % 300 == 0)
        {
            DEBUG_LOG("Entity " + std::to_string(entity->getId()) + " has invisible RenderableC");
        }

        if (transform && renderable && renderable->isVisible)
        {
            // Use 3D world coordinates directly
            float x = transform->position.x;
            float y = transform->position.y;
            float z = transform->position.z;
            float radius = 1.0f; // Default radius

            // Load color dynamically from MaterialManager using XML-defined material properties
            Color color = GetMaterialColor(renderable->materialId);

            // Debug output for rendered entities (occasional)
            if (frameCount % 600 == 0)
            {
                DEBUG_LOG("Rendering entity: " + entity->getName() +
                          " at (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")" +
                          " with material: " + renderable->materialId);
            }

            // Draw 3D sphere at world position
            DrawSphere(x, y, z, radius, color.r, color.g, color.b);
        }
        else if (frameCount % 300 == 0)
        {
            // Debug for entities missing components
            std::string missing = "Entity " + entity->getName() + " is missing ";
            if (!transform)
                missing += "transform ";
            if (!renderable)
                missing += "renderable ";
            if (renderable && !renderable->isVisible)
                missing += "(not visible) ";
            DEBUG_LOG(missing);
        }
    }
}

void VisualizationSystem::RenderConsole()
{
    // Console rendering - simplified for OpenGL transition
    // For now, just indicate console is visible
    DEBUG_LOG("Console visible (OpenGL text rendering to be implemented)");
}

void VisualizationSystem::RenderDebugModeIndicator()
{
    // Render debug mode indicator in upper right corner
    // Since text rendering is not fully implemented, we'll draw a simple colored rectangle
    
    // Get window dimensions
    RECT rect;
    GetClientRect(hwnd, &rect);
    float screenWidth = static_cast<float>(rect.right - rect.left);
    float screenHeight = static_cast<float>(rect.bottom - rect.top);
    
    // Switch to 2D rendering mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, screenWidth, screenHeight, 0.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Disable depth testing for UI overlay
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw a red rectangle in the upper right corner as debug indicator
    float indicatorWidth = 120.0f;
    float indicatorHeight = 30.0f;
    float margin = 10.0f;
    
    float x = screenWidth - indicatorWidth - margin;
    float y = margin;
    
    glColor4f(1.0f, 0.0f, 0.0f, 0.7f); // Semi-transparent red
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + indicatorWidth, y);
        glVertex2f(x + indicatorWidth, y + indicatorHeight);
        glVertex2f(x, y + indicatorHeight);
    glEnd();
    
    // Draw border
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // White border
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + indicatorWidth, y);
        glVertex2f(x + indicatorWidth, y + indicatorHeight);
        glVertex2f(x, y + indicatorHeight);
    glEnd();
    
    // Restore 3D rendering mode
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Render the debug cube at origin (0, 0, 0) in 3D world space
    DrawCube(0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f); // White cube with 2 unit size
    
    // Log debug info occasionally
    static int frameCount = 0;
    if (frameCount++ % 300 == 0) // Log every 5 seconds at 60fps
    {
        DEBUG_LOG("DEBUG_MODE indicator rendered in upper right corner at (" << x << ", " << y << ")");
        DEBUG_LOG("Debug white cube rendered at origin (0, 0, 0)");
    }
}

void VisualizationSystem::RenderNoPackagesMessage()
{
    // No packages message - simplified for OpenGL transition
    DEBUG_LOG("No Asset Packages Found - Generating Default Earth World...");
}

void VisualizationSystem::DrawSphere(float x, float y, float z, float radius, float r, float g, float b)
{
    // Debug output entity positions occasionally to help diagnose camera/entity positioning issues
    static int debugCounter = 0;
    if (debugCounter++ % 500 == 0)
    {
        // Only show a few entities to avoid spamming the console
        if (debugCounter < 10000)
        {
            DEBUG_LOG("Drawing entity at position (" << x << ", " << y << ", " << z
                                                     << ") with radius " << radius);

            // If we have a camera, calculate distance from camera
            if (camera)
            {
                float dx = camera->position.x - x;
                float dy = camera->position.y - y;
                float dz = camera->position.z - z;
                float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
                DEBUG_LOG("  Distance from camera: " << distance);
            }
        }
    }

    // Draw the sphere using the OpenGL renderer
    glRenderer.DrawSphere(x, y, z, radius, r, g, b);
}

void VisualizationSystem::DrawCube(float x, float y, float z, float size, float r, float g, float b)
{
    // Debug output cube positions occasionally
    static int debugCounter = 0;
    if (debugCounter++ % 300 == 0)
    {
        DEBUG_LOG("Drawing debug cube at position (" << x << ", " << y << ", " << z
                                                     << ") with size " << size);
    }

    // Draw the cube using OpenGL immediate mode
    float halfSize = size * 0.5f;
    
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    
    // Front face
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    
    // Back face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    
    // Top face
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    
    // Bottom face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    
    // Right face
    glVertex3f(x + halfSize, y - halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z - halfSize);
    glVertex3f(x + halfSize, y + halfSize, z + halfSize);
    glVertex3f(x + halfSize, y - halfSize, z + halfSize);
    
    // Left face
    glVertex3f(x - halfSize, y - halfSize, z - halfSize);
    glVertex3f(x - halfSize, y - halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z + halfSize);
    glVertex3f(x - halfSize, y + halfSize, z - halfSize);
    
    glEnd();
}

/**
 * @brief Get RGB color from material properties loaded from XML.
 *
 * Dynamically retrieves material color from MaterialManager instead of
 * using hardcoded lookup table. This allows colors to be configured via XML.
 *
 * @param materialId The material ID to look up
 * @return Color struct with r, g, b components in range 0.0-1.0
 */
VisualizationSystem::Color VisualizationSystem::GetMaterialColor(const std::string &materialId)
{
    // Try to get material from MaterialManager
    auto materialOpt = materialManager_.GetMaterial(materialId);
    if (materialOpt.has_value())
    {
        const auto &material = materialOpt.value();
        const auto &albedo = material.properties.albedo;

        // Return normalized float RGB (0.0-1.0) directly for OpenGL
        return {albedo.x, albedo.y, albedo.z};
    }

    // Fallback to default green if material not found
    DEBUG_LOG("Warning: Material '" << materialId << "' not found, using default green color");
    return {0.0f, 1.0f, 0.0f};
}
