# World.h / World.cpp

## Constructors

- `World(EventBus &eventBus)`

  **Summary:** Constructor that takes a reference to the event bus for communication.

## Public Methods

- `void addEntity(std::unique_ptr<Entity> entity)`

  **Summary:** Adds an entity to the world.

- `void addSystem(std::unique_ptr<ISystem> system)`

  **Summary:** Adds a system to the world.

- `void update(float dt)`

  **Summary:** Updates all systems in the world with the given delta time.

- `const std::vector<std::unique_ptr<ISystem>> &getSystems() const`

  **Summary:** Returns a reference to the list of systems in the world.

- `const std::vector<std::unique_ptr<Entity>> &getEntities() const`

  **Summary:** Returns a reference to the list of entities in the world.
