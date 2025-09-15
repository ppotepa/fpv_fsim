# IEvent.h

## Enums

- `EventType`: Enumeration of possible event types including BatteryLow, Collision, ConsoleToggle, ConsoleVisibilityChanged, NoPackagesFound, DefaultWorldGenerated.

## Methods

- `virtual ~IEvent() = default;`

  **Summary:** Virtual destructor for the event interface.

- `virtual EventType getType() const = 0;`

  **Summary:** Pure virtual method that returns the type of the event.
