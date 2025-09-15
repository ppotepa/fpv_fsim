# IWindModel.h

## Methods

- `virtual ~IWindModel() = default;`

  **Summary:** Virtual destructor for wind model interface.

- `virtual void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const = 0;`

  **Summary:** Pure virtual method to get wind velocity components at a given position.
