# SimClock.h / SimClock.cpp

## Constructors

- `SimClock(float fixedTimestep)`

  **Summary:** Constructor that sets the fixed timestep for physics simulation.

## Public Methods

- `void tick(float deltaTime)`

  **Summary:** Advances the simulation clock by the given delta time, accumulating for fixed timestep physics.

- `bool shouldStepPhysics()`

  **Summary:** Checks if enough time has accumulated to perform a physics step, consuming the accumulated time if so.

- `float getFixedTimestep()`

  **Summary:** Returns the fixed timestep value used for physics simulation.
