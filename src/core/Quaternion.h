#pragma once

/**
 * Simple quaternion class for rotations.
 */
struct Quaternion
{
    float w, x, y, z;

    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) {}

    static Quaternion identity()
    {
        return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }
};
