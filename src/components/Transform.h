#pragma once

#include <array>

namespace Components {
    struct Vector3 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Quaternion {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 1.0f;
    };

    struct Transform {
        Vector3 position;
        Quaternion rotation;
        Vector3 scale{1.0f, 1.0f, 1.0f};
    };
}
