#pragma once

/**
 * @brief Simple quaternion class for representing 3D rotations.
 *
 * Quaternions provide a mathematically robust way to represent rotations
 * in 3D space, avoiding issues like gimbal lock that can occur with
 * Euler angles. This implementation provides basic quaternion operations
 * needed for the simulation.
 */
struct Quaternion
{
    float w, x, y, z; /**< Quaternion components: w (real part), x,y,z (imaginary parts) */

    /**
     * @brief Construct a quaternion with specified components.
     *
     * @param w The real component (default: 1.0f for identity rotation)
     * @param x The i component (default: 0.0f)
     * @param y The j component (default: 0.0f)
     * @param z The k component (default: 0.0f)
     */
    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) {}

    /**
     * @brief Create an identity quaternion representing no rotation.
     *
     * @return Quaternion The identity quaternion (1, 0, 0, 0)
     */
    static Quaternion identity()
    {
        return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }
};
