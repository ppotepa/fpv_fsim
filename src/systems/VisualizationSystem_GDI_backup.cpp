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
    hdc = GetDC(hwnd);

    // Subscribe to events
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent) });

    eventBus.subscribe(EventType::ConsoleVisibilityChanged, [this](const IEvent &event)
                       {
        const auto& visibilityEvent = static_cast<const ConsoleVisibilityChangedEvent&>(event);
        OnConsoleVisibilityChanged(visibilityEvent) });
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
    // Efficient rendering using precompiled material color lookup
    for (const auto &entity : worldRef.getEntities())
    {
        auto transform = entity->getComponent<TransformC>();
        auto renderable = entity->getComponent<RenderableC>();

        if (transform && renderable && renderable->isVisible)
        {
            // Use configurable 2D projection parameters instead of hardcoded values
            float screenX = renderConfig_.getScreenCenterX() + transform->position.x * renderConfig_.getWorldToScreenScale();
            float screenY = renderConfig_.getScreenCenterY() + transform->position.z * renderConfig_.getWorldToScreenScale();
            float radius = renderConfig_.getDefaultEntityRadius();

            // Load color dynamically from MaterialManager using XML-defined material properties
            COLORREF color = GetMaterialColor(renderable->materialId);

            DrawSphere(screenX, screenY, radius, color);
        }
    }
}

void VisualizationSystem::RenderConsole()
{
    // Console rendering using configurable parameters from render_config.xml
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Draw semi-transparent background using configured colors
    const auto &bgColor = renderConfig_.getConsoleBackgroundColor();
    HBRUSH bgBrush = CreateSolidBrush(RGB(bgColor.r, bgColor.g, bgColor.b));
    RECT consoleRect = {0, rect.bottom - renderConfig_.getConsoleHeight(), rect.right, rect.bottom};
    FillRect(hdc, &consoleRect, bgBrush);
    DeleteObject(bgBrush);

    // Draw border using configured color and width
    const auto &borderColor = renderConfig_.getConsoleBorderColor();
    HPEN pen = CreatePen(PS_SOLID, renderConfig_.getConsoleBorderWidth(), RGB(borderColor.r, borderColor.g, borderColor.b));
    SelectObject(hdc, pen);
    Rectangle(hdc, consoleRect.left, consoleRect.top, consoleRect.right, consoleRect.bottom);
    DeleteObject(pen);

    // Draw console text using configured colors and margins
    const auto &titleColor = renderConfig_.getConsoleTitleColor();
    const auto &textColor = renderConfig_.getConsoleTextColor();
    int marginX = renderConfig_.getConsoleMarginX();
    int marginY = renderConfig_.getConsoleMarginY();

    DrawText(marginX, rect.bottom - renderConfig_.getConsoleHeight() + marginY,
             "Developer Console", RGB(titleColor.r, titleColor.g, titleColor.b));
    DrawText(marginX, rect.bottom - renderConfig_.getConsoleHeight() + marginY * 2,
             "Press ~ to toggle", RGB(textColor.r, textColor.g, textColor.b));
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

/**
 * @brief Get RGB color from material properties loaded from XML.
 *
 * Dynamically retrieves material color from MaterialManager instead of
 * using hardcoded lookup table. This allows colors to be configured via XML.
 *
 * @param materialId The material ID to look up
 * @return COLORREF color value, or default green if material not found
 */
COLORREF VisualizationSystem::GetMaterialColor(const std::string &materialId)
{
    // Try to get material from MaterialManager
    auto materialOpt = materialManager_.GetMaterial(materialId);
    if (materialOpt.has_value())
    {
        const auto &material = materialOpt.value();
        const auto &albedo = material.properties.albedo;

        // Convert from normalized float RGB (0.0-1.0) to Windows COLORREF (0-255)
        int r = static_cast<int>(albedo.x * 255.0f);
        int g = static_cast<int>(albedo.y * 255.0f);
        int b = static_cast<int>(albedo.z * 255.0f);

        // Clamp values to valid range (using Windows macros since std::min/max conflict)
        r = (r < 0) ? 0 : (r > 255) ? 255
                                    : r;
        g = (g < 0) ? 0 : (g > 255) ? 255
                                    : g;
        b = (b < 0) ? 0 : (b > 255) ? 255
                                    : b;

        return RGB(r, g, b);
    }

    // Fallback to default green if material not found
    DEBUG_LOG("Warning: Material '" << materialId << "' not found, using default green color");
    return RGB(0, 255, 0);
}


