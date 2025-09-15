#include "ExponentialAirDensityModel.h"
#include <cmath>

ExponentialAirDensityModel::ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight)
    : seaLevelDensity_(seaLevelDensity), scaleHeight_(scaleHeight) {}

float ExponentialAirDensityModel::getDensity(float altitude) const {
    return seaLevelDensity_ * std::exp(-altitude / scaleHeight_);
}
