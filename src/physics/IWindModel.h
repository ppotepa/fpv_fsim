/**
 * @file IWindModel.h
 * @brief Interface for wind models used in aerodynamic calculations.
 *
 * This interface defines the contract for wind models that calculate
 * wind velocity vectors at different positions in 3D space. Different
 * implementations can provide various wind patterns (constant, turbulent, etc.).
 */

#ifndef IWINDMODEL_H
#define IWINDMODEL_H

/**
 * @class IWindModel
 * @brief Abstract interface for calculating wind velocity at spatial positions.
 *
 * This interface provides a standardized way to calculate wind velocity
 * vectors at any point in 3D space. Implementations can model different
 * types of wind conditions including steady winds, turbulence, and weather systems.
 */
class IWindModel
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IWindModel() = default;

    /**
     * @brief Calculate wind velocity at a given position.
     *
     * @param x X coordinate of the position
     * @param y Y coordinate of the position
     * @param z Z coordinate of the position
     * @param wx [out] X component of wind velocity at the position
     * @param wy [out] Y component of wind velocity at the position
     * @param wz [out] Z component of wind velocity at the position
     */
    virtual void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const = 0;
};

#endif

