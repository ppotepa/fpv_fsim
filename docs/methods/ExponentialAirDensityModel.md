# ExponentialAirDensityModel.h / ExponentialAirDensityModel.cpp

## Constructors

- `ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight)`

  **Summary:** Constructor taking sea level density and scale height parameters.

## Public Methods

- `float getDensity(float altitude) const override`

  **Summary:** Calculates air density using exponential decay formula based on altitude.
