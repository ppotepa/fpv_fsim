#ifndef VISUALIZATION_SYSTEM_H
#define VISUALIZATION_SYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "events/InputEvents.h"
#include "events/WorldGenEvents.h"
#include "MaterialManager.h"
#include "config/RenderConfig.h"
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
    HDC hdc;
    Material::MaterialManager &materialManager_;
    const Render::RenderConfiguration &renderConfig_;

    bool displayNoPackagesMessage;
    bool consoleVisible;
    float rotationAngle;

    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event);

    void RenderEntities();
    void RenderConsole();
    void RenderNoPackagesMessage();
    void DrawSphere(float x, float y, float radius, COLORREF color);
    void DrawText(float x, float y, const std::string &text, COLORREF color);

    /**
     * @brief Get RGB color from material properties loaded from XML.
     *
     * @param materialId The material ID to look up
     * @return COLORREF color value, or default green if material not found
     */
    COLORREF GetMaterialColor(const std::string &materialId);
};

#endif

