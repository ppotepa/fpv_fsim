#pragma once

/**
 * @brief Simple 3D vector class for representing positions, scales, and other 3D quantities.
 *
 * This class provides basic 3D vector operations needed for the simulation,
 * including component-wise arithmetic operations. It's used throughout the
 * ECS for positioning entities, scaling, and other spatial calculations.
 */
struct Vector3D
{
    float x, y, z; /**< The x, y, and z components of the vector */

    /**
     * @brief Construct a 3D vector with specified components.
     *
     * @param x The x component (default: 0.0f)
     * @param y The y component (default: 0.0f)
     * @param z The z component (default: 0.0f)
     */
    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    /**
     * @brief Add two vectors component-wise.
     *
     * @param other The vector to add to this one
     * @return Vector3D The result of the addition
     */
    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Subtract two vectors component-wise.
     *
     * @param other The vector to subtract from this one
     * @return Vector3D The result of the subtraction
     */
    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Multiply this vector by a scalar value.
     *
     * @param scalar The scalar value to multiply by
     * @return Vector3D The scaled vector
     */
    Vector3D operator*(float scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
};
