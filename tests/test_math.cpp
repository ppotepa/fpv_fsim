#include <iostream>
#include "src/math/MathUtils.h"

int main()
{
    std::cout << "=== Testing Orbital Mechanics Math Implementation ===" << std::endl;

    // Test basic vector operations
    Math::float3 v1{1.0f, 2.0f, 3.0f};
    Math::float3 v2{4.0f, 5.0f, 6.0f};

    Math::float3 sum = Math::add(v1, v2);
    std::cout << "Vector addition: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;

    float dot = Math::dot(v1, v2);
    std::cout << "Dot product: " << dot << std::endl;

    Math::float3 cross = Math::cross(v1, v2);
    std::cout << "Cross product: (" << cross.x << ", " << cross.y << ", " << cross.z << ")" << std::endl;

    // Test orbital mechanics
    Math::OrbitParams orbit;
    orbit.semiMajorAxis = 5.0f;
    orbit.eccentricity = 0.2f;
    orbit.angularRate = 1.0f;
    orbit.inclination = 0.0f;
    orbit.phaseOffset = 0.0f;

    float time = 0.0f;
    Math::float3 position = Math::calculateOrbitPosition(orbit, time);
    std::cout << "Orbital position at t=0: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    Math::float3 velocity = Math::calculateOrbitVelocity(orbit, time);
    std::cout << "Orbital velocity at t=0: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")" << std::endl;

    // Test cel-shading
    std::vector<float> bands = {0.2f, 0.5f, 0.8f, 1.0f};
    float intensity = 0.6f;
    float quantized = Math::quantizeToBands(intensity, bands, 0.1f);
    std::cout << "Cel-shading quantized intensity: " << quantized << std::endl;

    // Test quaternions
    Math::quat q1{0.0f, 0.0f, 0.0f, 1.0f};
    Math::quat q2{0.0f, 0.5f, 0.0f, 0.866f}; // 60 degree rotation around Y
    Math::quat result = Math::q_mul(q1, q2);
    std::cout << "Quaternion multiplication: (" << result.x << ", " << result.y << ", " << result.z << ", " << result.w << ")" << std::endl;

    std::cout << "=== All tests completed ===" << std::endl;
    return 0;
}
