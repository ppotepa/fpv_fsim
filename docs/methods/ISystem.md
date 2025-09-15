# ISystem.h

## Methods

- `virtual ~ISystem() = default;`

  **Summary:** Virtual destructor for the system interface.

- `virtual void update(World &world, float dt) = 0;`

  **Summary:** Pure virtual update method called each frame with a reference to the world and the delta time since the last update.
