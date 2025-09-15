#include "PerlinWindModel.h"

PerlinWindModel::PerlinWindModel(float strength, float frequency, float amplitude, int seed)
    : strength_(strength), frequency_(frequency), amplitude_(amplitude), seed_(seed) {}

void PerlinWindModel::getWind(float x, float y, float z, float &wx, float &wy, float &wz) const
{
    // Stub: return constant wind
    wx = strength_;
    wy = 0.0f;
    wz = 0.0f;
}
