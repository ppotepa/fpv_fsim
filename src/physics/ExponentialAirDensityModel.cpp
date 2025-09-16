/**
 * @file ExpExponentialAirDensityModel::ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight)
    : seaLevelDensity_(seaLevelDensity), scaleHeight_(scaleHeight)
{
    DEBUG_LOG("Initializing ExponentialAirDensityModel with sea level density " + std::to_string(seaLevelDensity) + " and scale height " + std::to_string(scaleHeight));
}ialAirDensityModel.cpp
 * @brief Implementation of the exponential air density model.
 */

#include "ExponentialAirDensityModel.h"
#include <cmath>
#include "../debug.h"

/**
 * @brief Construct a new ExponentialAirDensityModel.
 *
 * Initializes the model with the given sea level density and scale height parameters.
 *
 * @param seaLevelDensity Air density at sea level in kg/m³ (typically ~1.225)
 * @param scaleHeight Atmospheric scale height in meters (typically ~8400)
 */
ExponentialAirDensityModel::ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight)
    : seaLevelDensity_(seaLevelDensity), scaleHeight_(scaleHeight)
{
    DEBUG_LOG("Initializing ExponentialAirDensityModel with sea level density " + std::to_string(seaLevelDensity) + " and scale height " + std::to_string(scaleHeight));
}

/**
 * @brief Calculate air density at a given altitude.
 *
 * Implements the exponential decay formula: ρ(h) = ρ₀ * exp(-h/H)
 * where ρ₀ is the sea level density and H is the scale height.
 *
 * @param altitude The altitude above sea level in meters
 * @return The air density in kg/m³ at the specified altitude
 */
float ExponentialAirDensityModel::getDensity(float altitude) const
{
    DEBUG_LOG("Calculating air density at altitude " + std::to_string(altitude));
    return seaLevelDensity_ * std::exp(-altitude / scaleHeight_);
}

