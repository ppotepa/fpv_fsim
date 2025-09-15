# InputSystem.h / InputSystem.cpp

## Constructors

- `InputSystem(EventBus &eventBus, IInputDevice &inputDevice)`

  **Summary:** Constructor taking event bus and input device references.

## Public Methods

- `void update(World &world, float dt) override`

  **Summary:** Updates the input system by polling the input device.
