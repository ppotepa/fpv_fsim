#include "VisualizationSystem.h"
#include <iostream>
#include <string>
#include <cmath>
#include <memory>

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

VisualizationSystem::VisualizationSystem(EventBus &eventBus, World &world, HWND windowHandle)
    : eventBus(eventBus), worldRef(world), hwnd(windowHandle),
      displayNoPackagesMessage(false), consoleVisible(false), rotationAngle(0.0f)
{
    hdc = GetDC(hwnd);

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
    ReleaseDC(hwnd, hdc);
}

void VisualizationSystem::update(World &world, float deltaTime)
{
    // Get a fresh device context for this frame
    HDC frameDC = GetDC(hwnd);
    
    // Clear the screen
    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(frameDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // Temporarily switch to frame DC for rendering
    HDC oldDC = hdc;
    hdc = frameDC;

    // Render entities
    RenderEntities();

    // Render console if visible
    if (consoleVisible)
    {
        RenderConsole();
    }

    // Render no packages message if needed
    if (displayNoPackagesMessage)
    {
        RenderNoPackagesMessage();
    }

    // Restore original DC and release frame DC
    hdc = oldDC;
    ReleaseDC(hwnd, frameDC);

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
    // Simple rendering of entities with TransformC and RenderableC
    for (const auto &entity : worldRef.getEntities())
    {
        auto transform = entity->getComponent<TransformC>();
        auto renderable = entity->getComponent<RenderableC>();

        if (transform && renderable && renderable->isVisible)
        {
            // Simple 2D projection for now - just draw circles at positions
            float screenX = 400 + transform->position.x * 0.01f; // Simple scaling
            float screenY = 300 + transform->position.z * 0.01f;
            float radius = 50.0f; // Fixed radius for now

            // Color based on material ID (simple mapping)
            COLORREF color = RGB(0, 255, 0); // Default green
            if (renderable->materialId == "earth_material")
                color = RGB(0, 0, 255); // Blue for Earth
            else if (renderable->materialId.find("atmosphere_material") == 0)
                color = RGB(135, 206, 235); // Sky blue for atmosphere
            else if (renderable->materialId == "cloud_material")
                color = RGB(255, 255, 255); // White for clouds

            DrawSphere(screenX, screenY, radius, color);
        }
    }
}

void VisualizationSystem::RenderConsole()
{
    // Simple console rendering at the bottom of the screen
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Draw semi-transparent background
    HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT consoleRect = {0, rect.bottom - 200, rect.right, rect.bottom};
    FillRect(hdc, &consoleRect, bgBrush);
    DeleteObject(bgBrush);

    // Draw border
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    Rectangle(hdc, consoleRect.left, consoleRect.top, consoleRect.right, consoleRect.bottom);
    DeleteObject(pen);

    // Draw console text
    DrawText(10, rect.bottom - 180, "Developer Console", RGB(255, 255, 0));
    DrawText(10, rect.bottom - 160, "Press ~ to toggle", RGB(255, 255, 255));
}

void VisualizationSystem::RenderNoPackagesMessage()
{
    RECT rect;
    GetClientRect(hwnd, &rect);

    DrawText(rect.right / 2 - 100, rect.bottom / 2 - 50, "No Asset Packages Found", RGB(255, 0, 0));
    DrawText(rect.right / 2 - 150, rect.bottom / 2 - 20, "Generating Default Earth World...", RGB(255, 255, 0));
}

void VisualizationSystem::DrawSphere(float x, float y, float radius, COLORREF color)
{
    HPEN pen = CreatePen(PS_SOLID, 2, color);
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

    DeleteObject(pen);
    DeleteObject(brush);
}

void VisualizationSystem::DrawText(float x, float y, const std::string &text, COLORREF color)
{
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    TextOutA(hdc, x, y, text.c_str(), text.length());
}
