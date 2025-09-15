#pragma once

/**
 * Simple 3D vector class for positions, scales, etc.
 */
struct Vector3D
{
    float x, y, z;

    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator*(float scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
};
