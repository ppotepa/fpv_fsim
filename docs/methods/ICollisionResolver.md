# ICollisionResolver.h

## Methods

- `virtual ~ICollisionResolver() = default;`

  **Summary:** Virtual destructor for collision resolver interface.

- `virtual void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) = 0;`

  **Summary:** Pure virtual method to resolve a collision by modifying velocity components based on surface normal and restitution.
