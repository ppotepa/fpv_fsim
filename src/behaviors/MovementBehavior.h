#pragma once
#include "../components/EntityBehavior.h"
#include "../math/Vec3.h"

namespace Behaviors
{

    /**
     * Behavior for moving entities along specified paths or directions.
     * Supports linear movement, circular movement, and waypoint-based paths.
     */
    class MovementBehavior : public Components::EntityBehavior
    {
    public:
        enum class MovementType
        {
            Linear,   // Move in a straight line
            Circular, // Move in a circle
            Waypoints // Move between predefined waypoints
        };

        void initialize(Core::Entity &entity, const Assets::BehaviorParams &params) override;
        void update(float deltaTime) override;
        void cleanup() override;

    private:
        MovementType movementType = MovementType::Linear;
        Math::Vec3 velocity = {0.0f, 0.0f, 0.0f};
        float speed = 1.0f;

        // Linear movement
        Math::Vec3 direction = {1.0f, 0.0f, 0.0f};

        // Circular movement
        Math::Vec3 center = {0.0f, 0.0f, 0.0f};
        float radius = 5.0f;
        float angularSpeed = 45.0f; // degrees per second
        float currentAngle = 0.0f;

        // Waypoint movement
        std::vector<Math::Vec3> waypoints;
        size_t currentWaypoint = 0;
        bool loop = true;

        bool hasTransform = false;
        Math::Vec3 startPosition = {0.0f, 0.0f, 0.0f};

        void updateLinearMovement(float deltaTime);
        void updateCircularMovement(float deltaTime);
        void updateWaypointMovement(float deltaTime);
        MovementType parseMovementType(const std::string &typeStr) const;
    };

} // namespace Behaviors
