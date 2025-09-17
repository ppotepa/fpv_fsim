# DroneBuilder.h / DroneBuilder.cpp

## Constructors

- `DroneBuilder(IJsonParser &jsonParser)`

  **Summary:** Constructor taking JSON parser reference.

## Public Methods

- `std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) override`

  **Summary:** Builds a drone entity from the configuration file (currently a stub).
