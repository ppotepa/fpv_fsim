#include <iostream>
#include "src/math/MathUtils.h"

int main()
{
    DEBUG_LOG("=== Testing Orbital Mechanics Math Implementation ===");

    // Test basic vector operations
    Math::float3 v1{1.0f, 2.0f, 3.0f};
    Math::float3 v2{4.0f, 5.0f, 6.0f};

    Math::float3 sum = Math::add(v1, v2);
    DEBUG_LOG("Vector addition: (" << sum.x << ", " << sum.y << ", " << sum.z << ")");

    float dot = Math::dot(v1, v2);
    DEBUG_LOG("Dot product: " << dot);

    Math::float3 cross = Math::cross(v1, v2);
    DEBUG_LOG("Cross product: (" << cross.x << ", " << cross.y << ", " << cross.z << ")");

    // Test orbital mechanics
    Math::OrbitParams orbit;
    orbit.semiMajorAxis = 5.0f;
    orbit.eccentricity = 0.2f;
    orbit.angularRate = 1.0f;
    orbit.inclination = 0.0f;
    orbit.phaseOffset = 0.0f;

    float time = 0.0f;
    Math::float3 position = Math::calculateOrbitPosition(orbit, time);
    DEBUG_LOG("Orbital position at t=0: (" << position.x << ", " << position.y << ", " << position.z << ")");

    Math::float3 velocity = Math::calculateOrbitVelocity(orbit, time);
    DEBUG_LOG("Orbital velocity at t=0: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")");

    // Test cel-shading
    std::vector<float> bands = {0.2f, 0.5f, 0.8f, 1.0f};
    float intensity = 0.6f;
    float quantized = Math::quantizeToBands(intensity, bands, 0.1f);
    DEBUG_LOG("Cel-shading quantized intensity: " << quantized);

    // Test quaternions
    Math::quat q1{0.0f, 0.0f, 0.0f, 1.0f};
    Math::quat q2{0.0f, 0.5f, 0.0f, 0.866f}; // 60 degree rotation around Y
    Math::quat result = Math::q_mul(q1, q2);
    DEBUG_LOG("Quaternion multiplication: (" << result.x << ", " << result.y << ", " << result.z << ", " << result.w << ")");

    DEBUG_LOG("=== All tests completed ===");
    return 0;
}
