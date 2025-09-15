# ConsoleSystem.h / ConsoleSystem.cpp

## Constructors

- `ConsoleSystem(EventBus &eventBus)`

  **Summary:** Constructor taking reference to event bus.

## Destructors

- `virtual ~ConsoleSystem() = default;`

  **Summary:** Virtual destructor.

## Public Methods

- `void update(World &world, float deltaTime) override`

  **Summary:** Updates the console system (no continuous updates needed).

- `void AddOutput(const std::string &message)`

  **Summary:** Adds a message to the console output buffer.

- `void ExecuteCommand(const std::string &command)`

  **Summary:** Executes a console command and adds output.

- `void ToggleVisibility()`

  **Summary:** Toggles the visibility of the console.

- `const std::vector<std::string> &GetOutputBuffer() const`

  **Summary:** Returns the console output buffer.

- `bool IsVisible() const`

  **Summary:** Returns whether the console is currently visible.

## Private Methods

- `void OnConsoleToggle(const ConsoleToggleEvent &event)`

  **Summary:** Event handler for console toggle events.
