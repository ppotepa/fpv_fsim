# PhysicsSystem.h / PhysicsSystem.cpp

## Constructors

- `PhysicsSystem(EventBus &eventBus, IAirDensityModel &airDensityModel, IWindModel &windModel, ICollisionResolver &collisionResolver)`

  **Summary:** Constructor taking event bus and physics model references.

## Public Methods

- `void update(World &world, float dt) override`

  **Summary:** Updates physics for entities in the world (currently a stub).
