#pragma once

#include "../components/EntityBehavior.h"
#include "../core/Vector3D.h"

namespace Behaviors
{
    /**
     * @brief Behavior that continuously rotates an entity around a specified axis
     * 
     * This behavior is used in the red cube scene to make the cube spin,
     * demonstrating the XML-driven scene authoring with C++ code-behind behaviors.
     */
    class SpinBehavior : public Components::EntityBehavior
    {
    public:
        SpinBehavior();
        virtual ~SpinBehavior() = default;

        // EntityBehavior interface
        void initialize(Entity& entity, const Assets::BehaviorParams& params) override;
        void update(float deltaTime) override;
        void cleanup() override;

    private:
        float rotationSpeed_;    // Degrees per second
        Vector3D rotationAxis_;  // Normalized rotation axis
        float currentRotation_;  // Current rotation in degrees
        Entity* entity_;         // Reference to the entity we're attached to
    };
}
