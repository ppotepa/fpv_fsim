# InputEvents.h

## Struct ConsoleToggleEvent

### Constructors

- `ConsoleToggleEvent() = default;`

  **Summary:** Default constructor for console toggle event.

### Methods

- `EventType getType() const override`

  **Summary:** Returns EventType::ConsoleToggle.

## Struct ConsoleVisibilityChangedEvent

### Constructors

- `ConsoleVisibilityChangedEvent(bool visible)`

  **Summary:** Constructor taking the visibility state.

### Methods

- `EventType getType() const override`

  **Summary:** Returns EventType::ConsoleVisibilityChanged.

### Members

- `bool isVisible;`

  **Summary:** The new visibility state of the console.
