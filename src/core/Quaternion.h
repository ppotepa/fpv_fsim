#pragma once
#include <cmath> // For std::sin, std::cos

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

    /**
     * @brief Create a quaternion from Euler angles (pitch, yaw, roll).
     *
     * @param pitch The pitch angle in radians (rotation around X-axis)
     * @param yaw The yaw angle in radians (rotation around Y-axis)
     * @param roll The roll angle in radians (rotation around Z-axis)
     * @return Quaternion The quaternion representing the given Euler angles
     */
    static Quaternion fromEulerAngles(float pitch, float yaw, float roll)
    {
        // Calculate half angles
        float halfPitch = pitch * 0.5f;
        float halfYaw = yaw * 0.5f;
        float halfRoll = roll * 0.5f;

        // Pre-calculate sine and cosine values
        float cosHalfPitch = std::cos(halfPitch);
        float sinHalfPitch = std::sin(halfPitch);
        float cosHalfYaw = std::cos(halfYaw);
        float sinHalfYaw = std::sin(halfYaw);
        float cosHalfRoll = std::cos(halfRoll);
        float sinHalfRoll = std::sin(halfRoll);

        // Calculate quaternion components
        float w = cosHalfRoll * cosHalfPitch * cosHalfYaw + sinHalfRoll * sinHalfPitch * sinHalfYaw;
        float x = sinHalfRoll * cosHalfPitch * cosHalfYaw - cosHalfRoll * sinHalfPitch * sinHalfYaw;
        float y = cosHalfRoll * sinHalfPitch * cosHalfYaw + sinHalfRoll * cosHalfPitch * sinHalfYaw;
        float z = cosHalfRoll * cosHalfPitch * sinHalfYaw - sinHalfRoll * sinHalfPitch * cosHalfYaw;

        return Quaternion(w, x, y, z);
    }
};
