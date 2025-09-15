# VisualizationSystem.h / VisualizationSystem.cpp

## Constructors

- `VisualizationSystem(EventBus &eventBus, World &world, HWND hwnd)`

  **Summary:** Constructor taking event bus, world, and window handle references.

## Destructors

- `~VisualizationSystem()`

  **Summary:** Destructor that releases the device context.

## Public Methods

- `void update(World &world, float deltaTime) override`

  **Summary:** Updates the visualization system, rendering entities and UI elements.

## Private Methods

- `void OnNoPackagesFound(const NoPackagesFoundEvent &event)`

  **Summary:** Event handler for no packages found event.

- `void OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event)`

  **Summary:** Event handler for console visibility change event.

- `void RenderEntities()`

  **Summary:** Renders all entities with TransformC and RenderableC components.

- `void RenderConsole()`

  **Summary:** Renders the developer console UI.

- `void RenderNoPackagesMessage()`

  **Summary:** Renders the no packages found message.

- `void DrawSphere(float x, float y, float radius, COLORREF color)`

  **Summary:** Draws a sphere (circle) at the specified position with given radius and color.

- `void DrawText(float x, float y, const std::string &text, COLORREF color)`

  **Summary:** Draws text at the specified position with given color.
