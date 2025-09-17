#ifndef VISUALIZATION_SYSTEM_H
#define VISUALIZATION_SYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "events/InputEvents.h"
#include "events/WorldGenEvents.h"
#include "MaterialManager.h"
#include "config/RenderConfig.h"
#include "platform/OpenGLContext.h"
#include "platform/OpenGLRenderer.h"
#include "DebugCamera.h"
#include <windows.h>
#include <string>
#include <vector>
#include <unordered_map>

class VisualizationSystem : public ISystem
{
public:
    VisualizationSystem(EventBus &eventBus, World &world, HWND hwnd, Material::MaterialManager &materialManager, const Render::RenderConfiguration &renderConfig);
    ~VisualizationSystem();

    void update(World &world, float deltaTime) override;

private:
    EventBus &eventBus;
    World &worldRef;
    HWND hwnd;
    Material::MaterialManager &materialManager_;
    const Render::RenderConfiguration &renderConfig_;

    // OpenGL components
    OpenGLContext glContext;
    OpenGLRenderer glRenderer;

    // Camera configuration
    struct CameraConfig
    {
        struct Vector3
        {
            float x, y, z;
            Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
        };

        Vector3 position;  // Camera position
        Vector3 direction; // Look direction
        Vector3 up;        // Up vector
        float fov;         // Field of view in degrees
        float nearPlane;   // Near clipping plane
        float farPlane;    // Far clipping plane
    };

    std::shared_ptr<CameraConfig> camera;
    std::unique_ptr<DebugCamera> debugCamera;
    bool debugModeActive;

    bool displayNoPackagesMessage;
    bool consoleVisible;
    float rotationAngle;

    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event);
    void OnDebugModeToggled(const DebugModeToggled &event);

    void RenderEntities();
    void RenderConsole();
    void RenderDebugModeIndicator();
    void RenderNoPackagesMessage();
    void DrawSphere(float x, float y, float z, float radius, float r, float g, float b);
    void DrawCube(float x, float y, float z, float size, float r, float g, float b);

    /**
     * @brief Get RGB color from material properties loaded from JSON.
     *
     * @param materialId The material ID to look up
     * @return Color components as vec3 (r, g, b) in range 0.0-1.0
     */
    struct Color
    {
        float r, g, b;
    };
    Color GetMaterialColor(const std::string &materialId);
};

#endif
