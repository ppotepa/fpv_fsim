# IVehicleBuilder.h

## Methods

- `virtual ~IVehicleBuilder() = default;`

  **Summary:** Virtual destructor for vehicle builder interface.

- `virtual std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) = 0;`

  **Summary:** Pure virtual method to build a vehicle entity from configuration file.
