#include "CubeSpinBehavior.h"
#include "../components/Transform.h"
#include "../math/Math.h"

namespace Behaviors {

void CubeSpinBehavior::initialize(Core::Entity& entity, const Assets::BehaviorParams& params) {
    // Get rotation axis from parameters (default: Y-axis)
    auto axisX = getParameter<float>("axisX", 0.0f);
    auto axisY = getParameter<float>("axisY", 1.0f);
    auto axisZ = getParameter<float>("axisZ", 0.0f);
    rotationAxis = Math::Vec3(axisX, axisY, axisZ);
    
    // Get rotation speed from parameters (default: 90 degrees per second)
    rotationSpeed = getParameter<float>("speed", 90.0f);
    
    // Check if entity has a Transform component
    hasTransform = entity.hasComponent<Components::Transform>();
    
    if (!hasTransform) {
        // Log warning: entity needs Transform component for CubeSpinBehavior
    }
    
    currentRotation = 0.0f;
}

void CubeSpinBehavior::update(float deltaTime) {
    if (!hasTransform) {
        return;
    }
    
    auto& transform = getEntity().getComponent<Components::Transform>();
    
    // Update rotation
    currentRotation += rotationSpeed * deltaTime;
    
    // Keep rotation in [0, 360) range
    if (currentRotation >= 360.0f) {
        currentRotation -= 360.0f;
    }
    
    // Apply rotation around the specified axis
    float radians = Math::degreesToRadians(currentRotation);
    
    // Create rotation quaternion around the specified axis
    Math::Quaternion rotation = Math::Quaternion::fromAxisAngle(rotationAxis, radians);
    
    // Apply rotation to transform
    transform.rotation = rotation;
    transform.markDirty();
}

void CubeSpinBehavior::cleanup() {
    // No special cleanup needed
}

} // namespace Behaviors

// Register the behavior with the system
REGISTER_BEHAVIOR(Behaviors::CubeSpinBehavior, "CubeSpinBehavior")
