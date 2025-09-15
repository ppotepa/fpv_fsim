# IAirDensityModel.h

## Methods

- `virtual ~IAirDensityModel() = default;`

  **Summary:** Virtual destructor for air density model interface.

- `virtual float getDensity(float altitude) const = 0;`

  **Summary:** Pure virtual method to get air density at a given altitude.
