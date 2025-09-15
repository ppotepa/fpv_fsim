#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "platform/IInputDevice.h"

class InputSystem : public ISystem {
public:
    InputSystem(EventBus& eventBus, IInputDevice& inputDevice);
    void update(World& world, float dt) override;
private:
    EventBus& eventBus_;
    IInputDevice& inputDevice_;
};

#endif
