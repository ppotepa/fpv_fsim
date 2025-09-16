#include "VisualizationSystem.h"
#include "../core/AssetIds.h"
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
      displayNoPackagesMessage(false), consoleVisible(false), rotationAngle(0.0f)
{
    std::cout << "Initializing VisualizationSystem with OpenGL rendering..." << std::endl;

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

    std::cout << "Camera initialized at position (" << camera->position.x << ", "
              << camera->position.y << ", " << camera->position.z << ")" << std::endl;

    std::cout << "OpenGL-based VisualizationSystem initialized successfully" << std::endl;

    // Subscribe to events
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    eventBus.subscribe(EventType::ConsoleVisibilityChanged, [this](const IEvent &event)
                       {
        const auto& visibilityEvent = static_cast<const ConsoleVisibilityChangedEvent&>(event);
        OnConsoleVisibilityChanged(visibilityEvent); });
}

VisualizationSystem::~VisualizationSystem()
{
    // OpenGL context cleanup is handled by OpenGLContext destructor
}

void VisualizationSystem::update(World &world, float deltaTime)
{
    // Ensure OpenGL context is current
    glContext.MakeCurrent();

    // Get window dimensions for camera setup
    RECT rect;
    GetClientRect(hwnd, &rect);
    float aspect = static_cast<float>(rect.right - rect.left) / static_cast<float>(rect.bottom - rect.top);

    // Debug output window size every 600 frames
    static int frameCount = 0;
    if (frameCount++ % 600 == 0)
    {
        std::cout << "Window dimensions: " << (rect.right - rect.left) << "x"
                  << (rect.bottom - rect.top) << " (aspect: " << aspect << ")" << std::endl;
    }

    // Setup 3D camera using our camera object
    if (camera)
    {
        glRenderer.SetupCamera(camera->fov, aspect, camera->nearPlane, camera->farPlane);

        // Calculate look-at point based on camera position and direction
        float lookAtX = camera->position.x + camera->direction.x;
        float lookAtY = camera->position.y + camera->direction.y;
        float lookAtZ = camera->position.z + camera->direction.z;

        glRenderer.SetCameraView(
            camera->position.x, camera->position.y, camera->position.z, // Eye position
            lookAtX, lookAtY, lookAtZ,                                  // Look at point
            camera->up.x, camera->up.y, camera->up.z                    // Up vector
        );

        // Every 300 frames, output camera debug info
        if (frameCount % 300 == 0)
        {
            std::cout << "Camera position: (" << camera->position.x << ", "
                      << camera->position.y << ", " << camera->position.z << ")" << std::endl;
            std::cout << "Looking at: (" << lookAtX << ", " << lookAtY << ", " << lookAtZ << ")" << std::endl;
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

void VisualizationSystem::RenderEntities()
{
    // Debug information - print entity count
    static int frameCount = 0;
    if (frameCount++ % 60 == 0)
    { // Print more frequently for debugging
        std::cout << "VisualizationSystem: Rendering " << worldRef.getEntities().size() << " entities" << std::endl;

        // Count entities with required rendering components
        int entitiesWithRenderComponents = 0;
        for (const auto &entity : worldRef.getEntities())
        {
            if (entity->getComponent<TransformC>() && entity->getComponent<RenderableC>())
            {
                entitiesWithRenderComponents++;
            }
        }
        std::cout << "Entities with rendering components: " << entitiesWithRenderComponents << std::endl;

        // Output camera position for debugging
        if (camera)
        {
            std::cout << "Camera position: (" << camera->position.x << ", "
                      << camera->position.y << ", " << camera->position.z << ")" << std::endl;
            std::cout << "Camera direction: (" << camera->direction.x << ", "
                      << camera->direction.y << ", " << camera->direction.z << ")" << std::endl;
        }
        else
        {
            std::cout << "WARNING: Camera not initialized!" << std::endl;
        }
    }

    // If no entities to render, show a warning and draw debug shapes
    if (worldRef.getEntities().empty())
    {
        if (frameCount % 60 == 0)
        { // Print more frequently for debugging
            std::cout << "WARNING: No entities to render in the scene!" << std::endl;
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
            std::cout << "Entity " << entity->getId() << " missing TransformC component" << std::endl;
        }
        if (!renderable && frameCount % 300 == 0)
        {
            std::cout << "Entity " << entity->getId() << " missing RenderableC component" << std::endl;
        }
        if (renderable && !renderable->isVisible && frameCount % 300 == 0)
        {
            std::cout << "Entity " << entity->getId() << " has invisible RenderableC" << std::endl;
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
                std::cout << "Rendering entity: " << entity->getName()
                          << " at (" << x << ", " << y << ", " << z << ")"
                          << " with material: " << renderable->materialId << std::endl;
            }

            // Draw 3D sphere at world position
            DrawSphere(x, y, z, radius, color.r, color.g, color.b);
        }
        else if (frameCount % 300 == 0)
        {
            // Debug for entities missing components
            std::cout << "Entity " << entity->getName() << " is missing ";
            if (!transform)
                std::cout << "transform ";
            if (!renderable)
                std::cout << "renderable ";
            if (renderable && !renderable->isVisible)
                std::cout << "(not visible) ";
            std::cout << std::endl;
        }
    }
}

void VisualizationSystem::RenderConsole()
{
    // Console rendering - simplified for OpenGL transition
    // For now, just indicate console is visible
    std::cout << "Console visible (OpenGL text rendering to be implemented)" << std::endl;
}

void VisualizationSystem::RenderNoPackagesMessage()
{
    // No packages message - simplified for OpenGL transition
    std::cout << "No Asset Packages Found - Generating Default Earth World..." << std::endl;
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
            std::cout << "Drawing entity at position (" << x << ", " << y << ", " << z
                      << ") with radius " << radius << std::endl;

            // If we have a camera, calculate distance from camera
            if (camera)
            {
                float dx = camera->position.x - x;
                float dy = camera->position.y - y;
                float dz = camera->position.z - z;
                float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
                std::cout << "  Distance from camera: " << distance << std::endl;
            }
        }
    }

    // Draw the sphere using the OpenGL renderer
    glRenderer.DrawSphere(x, y, z, radius, r, g, b);
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
    std::cout << "Warning: Material '" << materialId << "' not found, using default green color" << std::endl;
    return {0.0f, 1.0f, 0.0f};
}
