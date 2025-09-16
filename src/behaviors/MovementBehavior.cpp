#include "MovementBehavior.h"
#include "../components/Transform.h"
#include "../math/Math.h"
#include <sstream>

namespace Behaviors {

void MovementBehavior::initialize(Core::Entity& entity, const Assets::BehaviorParams& params) {
    // Parse movement type
    auto typeStr = getParameter<std::string>("type", "linear");
    movementType = parseMovementType(typeStr);
    
    // Get common parameters
    speed = getParameter<float>("speed", 1.0f);
    
    // Check if entity has Transform component
    hasTransform = entity.hasComponent<Components::Transform>();
    if (hasTransform) {
        auto& transform = entity.getComponent<Components::Transform>();
        startPosition = transform.position;
    }
    
    // Initialize based on movement type
    switch (movementType) {
        case MovementType::Linear:
            direction.x = getParameter<float>("directionX", 1.0f);
            direction.y = getParameter<float>("directionY", 0.0f);
            direction.z = getParameter<float>("directionZ", 0.0f);
            direction = Math::normalize(direction);
            break;
            
        case MovementType::Circular:
            center.x = getParameter<float>("centerX", startPosition.x);
            center.y = getParameter<float>("centerY", startPosition.y);
            center.z = getParameter<float>("centerZ", startPosition.z);
            radius = getParameter<float>("radius", 5.0f);
            angularSpeed = getParameter<float>("angularSpeed", 45.0f);
            currentAngle = 0.0f;
            break;
            
        case MovementType::Waypoints:
            // Parse waypoints from comma-separated values
            auto waypointsStr = getParameter<std::string>("waypoints", "");
            if (!waypointsStr.empty()) {
                std::istringstream iss(waypointsStr);
                std::string token;
                Math::Vec3 waypoint;
                int componentIndex = 0;
                
                while (std::getline(iss, token, ',')) {
                    float value = std::stof(token);
                    switch (componentIndex % 3) {
                        case 0: waypoint.x = value; break;
                        case 1: waypoint.y = value; break;
                        case 2: waypoint.z = value; waypoints.push_back(waypoint); break;
                    }
                    componentIndex++;
                }
            }
            
            loop = getParameter<bool>("loop", true);
            currentWaypoint = 0;
            break;
    }
}

void MovementBehavior::update(float deltaTime) {
    if (!hasTransform) {
        return;
    }
    
    switch (movementType) {
        case MovementType::Linear:
            updateLinearMovement(deltaTime);
            break;
        case MovementType::Circular:
            updateCircularMovement(deltaTime);
            break;
        case MovementType::Waypoints:
            updateWaypointMovement(deltaTime);
            break;
    }
}

void MovementBehavior::cleanup() {
    // No special cleanup needed
}

void MovementBehavior::updateLinearMovement(float deltaTime) {
    auto& transform = getEntity().getComponent<Components::Transform>();
    
    Math::Vec3 movement = direction * speed * deltaTime;
    transform.position = transform.position + movement;
    transform.markDirty();
}

void MovementBehavior::updateCircularMovement(float deltaTime) {
    auto& transform = getEntity().getComponent<Components::Transform>();
    
    currentAngle += angularSpeed * deltaTime;
    if (currentAngle >= 360.0f) {
        currentAngle -= 360.0f;
    }
    
    float radians = Math::degreesToRadians(currentAngle);
    transform.position.x = center.x + radius * std::cos(radians);
    transform.position.z = center.z + radius * std::sin(radians);
    transform.position.y = center.y; // Keep Y constant
    
    transform.markDirty();
}

void MovementBehavior::updateWaypointMovement(float deltaTime) {
    if (waypoints.empty()) {
        return;
    }
    
    auto& transform = getEntity().getComponent<Components::Transform>();
    Math::Vec3 currentPos = transform.position;
    Math::Vec3 targetPos = waypoints[currentWaypoint];
    
    // Calculate direction to target
    Math::Vec3 direction = targetPos - currentPos;
    float distance = Math::length(direction);
    
    // Check if we've reached the waypoint
    if (distance < 0.1f) { // Within 0.1 units
        currentWaypoint++;
        
        if (currentWaypoint >= waypoints.size()) {
            if (loop) {
                currentWaypoint = 0;
            } else {
                // Stop at the last waypoint
                currentWaypoint = waypoints.size() - 1;
                return;
            }
        }
        
        // Recalculate for new target
        targetPos = waypoints[currentWaypoint];
        direction = targetPos - currentPos;
        distance = Math::length(direction);
    }
    
    if (distance > 0.0f) {
        direction = direction / distance; // Normalize
        Math::Vec3 movement = direction * speed * deltaTime;
        
        // Don't overshoot the target
        if (Math::length(movement) > distance) {
            movement = direction * distance;
        }
        
        transform.position = currentPos + movement;
        transform.markDirty();
    }
}

MovementBehavior::MovementType MovementBehavior::parseMovementType(const std::string& typeStr) const {
    if (typeStr == "circular") {
        return MovementType::Circular;
    } else if (typeStr == "waypoints") {
        return MovementType::Waypoints;
    } else {
        return MovementType::Linear; // Default
    }
}

} // namespace Behaviors

// Register the behavior with the system
REGISTER_BEHAVIOR(Behaviors::MovementBehavior, "MovementBehavior")
