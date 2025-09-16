#pragma once
#include "../components/EntityBehavior.h"
#include "../math/Vec3.h"

namespace Behaviors {

/**
 * Simple behavior that spins an entity around a specified axis.
 * Used to demonstrate the red cube spinning behavior from the package system.
 */
class CubeSpinBehavior : public Components::EntityBehavior {
public:
    void initialize(Core::Entity& entity, const Assets::BehaviorParams& params) override;
    void update(float deltaTime) override;
    void cleanup() override;

private:
    Math::Vec3 rotationAxis = {0.0f, 1.0f, 0.0f}; // Default: Y-axis
    float rotationSpeed = 90.0f; // degrees per second
    float currentRotation = 0.0f;
    
    bool hasTransform = false;
};

} // namespace Behaviors
