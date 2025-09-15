# ImpulseCollisionResolver.h / ImpulseCollisionResolver.cpp

## Constructors

- `ImpulseCollisionResolver(float friction, float restitution)`

  **Summary:** Constructor taking friction and restitution coefficients.

## Public Methods

- `void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) override`

  **Summary:** Resolves collision by applying impulse to velocity components based on surface normal and restitution (currently a simple implementation).
