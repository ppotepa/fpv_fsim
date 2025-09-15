#include "InputSystem.h"
#include "core/World.h"

InputSystem::InputSystem(EventBus &eventBus, IInputDevice &inputDevice)
    : eventBus_(eventBus), inputDevice_(inputDevice) {}

void InputSystem::update(World &world, float dt)
{
    inputDevice_.poll();
    // Process input
}
