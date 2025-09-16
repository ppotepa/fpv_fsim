/**
 * @file ExponentialAirDensityModel.h
 * @brief Implementation of an exponential air density model.
 *
 * This file implements an exponential decay model for atmospheric density,
 * commonly used in aviation and atmospheric physics. The model assumes
 * density decreases exponentially with altitude.
 */

#ifndef EXPONENTIALAIRDENSITYMODEL_H
#define EXPONENTIALAIRDENSITYMODEL_H

#include "IAirDensityModel.h"

/**
 * @class ExponentialAirDensityModel
 * @brief Air density model using exponential decay with altitude.
 *
 * This implementation uses the standard atmospheric model where air density
 * decreases exponentially with height according to the formula:
 * ρ(h) = ρ₀ * exp(-h/H)
 * where ρ₀ is sea level density and H is the scale height.
 */
class ExponentialAirDensityModel : public IAirDensityModel
{
public:
    /**
     * @brief Construct a new ExponentialAirDensityModel.
     *
     * @param seaLevelDensity Air density at sea level in kg/m³ (typically ~1.225)
     * @param scaleHeight Atmospheric scale height in meters (typically ~8400)
     */
    ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight);

    /**
     * @brief Calculate air density at a given altitude.
     *
     * Uses the exponential decay formula: ρ(h) = ρ₀ * exp(-h/H)
     *
     * @param altitude The altitude above sea level in meters
     * @return The air density in kg/m³ at the specified altitude
     */
    float getDensity(float altitude) const override;

private:
    /** @brief Air density at sea level in kg/m³ */
    float seaLevelDensity_;

    /** @brief Atmospheric scale height in meters */
    float scaleHeight_;
};

#endif

