# DroneBuilder.h / DroneBuilder.cpp

## Constructors

- `DroneBuilder(IXmlParser &xmlParser)`

  **Summary:** Constructor taking XML parser reference.

## Public Methods

- `std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) override`

  **Summary:** Builds a drone entity from the configuration file (currently a stub).
