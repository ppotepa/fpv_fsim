#include "ConsoleSystem.h"
#include "../core/World.h"
#include <iostream>

ConsoleSystem::ConsoleSystem(EventBus &eventBus)
    : eventBus(eventBus), isVisible(false)
{
    // Subscribe to console toggle events
    eventBus.subscribe(EventType::ConsoleToggle, [this](const IEvent &event)
                       {
        const auto& toggleEvent = static_cast<const ConsoleToggleEvent&>(event);
        OnConsoleToggle(toggleEvent); });

    AddOutput("Console initialized. Press ~ to toggle visibility.");
}

void ConsoleSystem::update(World &world, float deltaTime)
{
    // Console system doesn't need continuous updates
}

void ConsoleSystem::AddOutput(const std::string &message)
{
    outputBuffer.push_back(message);
    if (outputBuffer.size() > 100) // Limit buffer size
    {
        outputBuffer.erase(outputBuffer.begin());
    }
}

void ConsoleSystem::ExecuteCommand(const std::string &command)
{
    AddOutput("> " + command);

    // TODO: Implement command parsing and execution
    if (command == "help")
    {
        AddOutput("Available commands:");
        AddOutput("  help - Show this help");
        AddOutput("  clear - Clear console");
        AddOutput("  quit - Exit application");
    }
    else if (command == "clear")
    {
        outputBuffer.clear();
        AddOutput("Console cleared.");
    }
    else if (command == "quit")
    {
        AddOutput("Quitting application...");
        // TODO: Publish quit event
    }
    else
    {
        AddOutput("Unknown command: " + command);
    }
}

void ConsoleSystem::ToggleVisibility()
{
    isVisible = !isVisible;
    // TODO: Publish visibility changed event
}

void ConsoleSystem::OnConsoleToggle(const ConsoleToggleEvent &event)
{
    ToggleVisibility();
}

const std::vector<std::string> &ConsoleSystem::GetOutputBuffer() const
{
    return outputBuffer;
}

bool ConsoleSystem::IsVisible() const
{
    return isVisible;
}
