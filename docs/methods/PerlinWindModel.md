# PerlinWindModel.h / PerlinWindModel.cpp

## Constructors

- `PerlinWindModel(float strength, float frequency, float amplitude, int seed)`

  **Summary:** Constructor taking wind strength, frequency, amplitude, and seed parameters.

## Public Methods

- `void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const override`

  **Summary:** Gets wind velocity at a position (currently returns constant wind in x-direction).
