/**
 * @file IAirDensityModel.h
 * @brief Interface for air density models used in physics calculations.
 *
 * This interface defines the contract for air density models that calculate
 * atmospheric density as a function of altitude. Different implementations
 * can provide various atmospheric models (exponential, tabulated, etc.).
 */

#ifndef IAIRDENSITYMODEL_H
#define IAIRDENSITYMODEL_H

/**
 * @class IAirDensityModel
 * @brief Abstract interface for calculating air density at different altitudes.
 *
 * This interface provides a standardized way to calculate atmospheric density
 * based on altitude. Implementations can use different mathematical models
 * such as exponential decay, lookup tables, or complex atmospheric simulations.
 */
class IAirDensityModel
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IAirDensityModel() = default;

    /**
     * @brief Calculate air density at a given altitude.
     *
     * @param altitude The altitude above sea level in meters
     * @return The air density in kg/m³ at the specified altitude
     */
    virtual float getDensity(float altitude) const = 0;
};

#endif
