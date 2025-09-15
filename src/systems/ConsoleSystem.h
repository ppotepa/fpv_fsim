#pragma once
#include "../core/ISystem.h"
#include "../core/EventBus.h"
#include "../events/InputEvents.h"
#include <string>
#include <vector>
#include <functional>

class World;

/**
 * Console system for managing developer console state and command processing.
 */
class ConsoleSystem : public ISystem
{
public:
    ConsoleSystem(EventBus &eventBus);
    virtual ~ConsoleSystem() = default;

    void update(World &world, float deltaTime) override;

    void AddOutput(const std::string &message);
    void ExecuteCommand(const std::string &command);
    void ToggleVisibility();

    const std::vector<std::string> &GetOutputBuffer() const;
    bool IsVisible() const;

private:
    EventBus &eventBus;
    bool isVisible;
    std::vector<std::string> outputBuffer;

    void OnConsoleToggle(const ConsoleToggleEvent &event);
};
