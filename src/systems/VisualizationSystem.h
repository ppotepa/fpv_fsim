#ifndef VISUALIZATION_SYSTEM_H
#define VISUALIZATION_SYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "events/InputEvents.h"
#include "events/WorldGenEvents.h"
#include <windows.h>
#include <string>
#include <vector>
#include <unordered_map>

class VisualizationSystem : public ISystem
{
public:
    VisualizationSystem(EventBus &eventBus, World &world, HWND hwnd);
    ~VisualizationSystem();

    void update(World &world, float deltaTime) override;

private:
    EventBus &eventBus;
    World &worldRef;
    HWND hwnd;
    HDC hdc;

    bool displayNoPackagesMessage;
    bool consoleVisible;
    float rotationAngle;

    // Precompiled material color lookup table
    std::unordered_map<std::string, COLORREF> materialColors;

    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event);

    void RenderEntities();
    void RenderConsole();
    void RenderNoPackagesMessage();
    void DrawSphere(float x, float y, float radius, COLORREF color);
    void DrawText(float x, float y, const std::string &text, COLORREF color);
};

#endif
