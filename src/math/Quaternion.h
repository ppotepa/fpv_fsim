#pragma once
#include "Vector3D.h"
#include <cmath>

/**
 * @struct Quaternion
 * @brief Quaternion class for representing 3D rotations.
 *
 * Quaternions offer a more stable and efficient way to represent rotations
 * compared to Euler angles, avoiding gimbal lock and providing smooth interpolation.
 */
struct Quaternion
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f; // Real part, initialized to identity rotation

    /**
     * @brief Default constructor creates an identity quaternion
     */
    Quaternion() = default;

    /**
     * @brief Constructs a quaternion with specified components
     *
     * @param x The x component (imaginary i)
     * @param y The y component (imaginary j)
     * @param z The z component (imaginary k)
     * @param w The w component (real part)
     */
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    /**
     * @brief Creates a quaternion from Euler angles (in radians)
     *
     * @param pitch Rotation around X axis (in radians)
     * @param yaw Rotation around Y axis (in radians)
     * @param roll Rotation around Z axis (in radians)
     * @return Quaternion representing the rotation
     */
    static Quaternion fromEulerAngles(float pitch, float yaw, float roll)
    {
        // Convert Euler angles to quaternion using the ZYX convention
        float cy = std::cos(yaw * 0.5f);
        float sy = std::sin(yaw * 0.5f);
        float cp = std::cos(pitch * 0.5f);
        float sp = std::sin(pitch * 0.5f);
        float cr = std::cos(roll * 0.5f);
        float sr = std::sin(roll * 0.5f);

        Quaternion q;
        q.w = cy * cp * cr + sy * sp * sr;
        q.x = cy * cp * sr - sy * sp * cr;
        q.y = sy * cp * sr + cy * sp * cr;
        q.z = sy * cp * cr - cy * sp * sr;

        return q;
    }

    /**
     * @brief Normalizes this quaternion to unit length
     *
     * @return Reference to this quaternion after normalization
     */
    Quaternion &normalize()
    {
        float len = std::sqrt(x * x + y * y + z * z + w * w);
        if (len > 0)
        {
            float invLen = 1.0f / len;
            x *= invLen;
            y *= invLen;
            z *= invLen;
            w *= invLen;
        }
        return *this;
    }

    /**
     * @brief Multiply this quaternion by another (compose rotations)
     *
     * @param other Quaternion to multiply with
     * @return Reference to this quaternion after multiplication
     */
    Quaternion &operator*=(const Quaternion &other)
    {
        float newW = w * other.w - x * other.x - y * other.y - z * other.z;
        float newX = w * other.x + x * other.w + y * other.z - z * other.y;
        float newY = w * other.y - x * other.z + y * other.w + z * other.x;
        float newZ = w * other.z + x * other.y - y * other.x + z * other.w;

        w = newW;
        x = newX;
        y = newY;
        z = newZ;

        return *this;
    }
};

/**
 * @brief Multiply two quaternions (compose rotations)
 *
 * @param a First quaternion
 * @param b Second quaternion
 * @return Resulting quaternion (a * b)
 */
inline Quaternion operator*(const Quaternion &a, const Quaternion &b)
{
    return Quaternion(
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
}

