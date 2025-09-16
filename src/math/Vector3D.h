#pragma once

/**
 * @struct Vector3D
 * @brief A 3D vector class for representing positions, directions, and velocities.
 */
struct Vector3D
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    /**
     * @brief Default constructor initializes vector to (0,0,0)
     */
    Vector3D() = default;

    /**
     * @brief Constructs a 3D vector with specified coordinates
     *
     * @param x The x coordinate
     * @param y The y coordinate
     * @param z The z coordinate
     */
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * @brief Add another vector to this one
     *
     * @param other Vector to add
     * @return Reference to this vector after addition
     */
    Vector3D &operator+=(const Vector3D &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * @brief Subtract another vector from this one
     *
     * @param other Vector to subtract
     * @return Reference to this vector after subtraction
     */
    Vector3D &operator-=(const Vector3D &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    /**
     * @brief Scale this vector by a scalar value
     *
     * @param scalar Scaling factor
     * @return Reference to this vector after scaling
     */
    Vector3D &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
};

/**
 * @brief Add two vectors
 *
 * @param a First vector
 * @param b Second vector
 * @return Sum of the two vectors
 */
inline Vector3D operator+(const Vector3D &a, const Vector3D &b)
{
    return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
 * @brief Subtract one vector from another
 *
 * @param a Vector to subtract from
 * @param b Vector to subtract
 * @return Difference of the two vectors
 */
inline Vector3D operator-(const Vector3D &a, const Vector3D &b)
{
    return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
 * @brief Scale a vector by a scalar
 *
 * @param v Vector to scale
 * @param scalar Scaling factor
 * @return Scaled vector
 */
inline Vector3D operator*(const Vector3D &v, float scalar)
{
    return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}

/**
 * @brief Scale a vector by a scalar
 *
 * @param scalar Scaling factor
 * @param v Vector to scale
 * @return Scaled vector
 */
inline Vector3D operator*(float scalar, const Vector3D &v)
{
    return v * scalar;
}
