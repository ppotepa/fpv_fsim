#pragma once
#include "../core/IComponent.h"
#include <string>

/**
 * @file PhysicsC.h
 * @brief Component for entities with physical properties.
 *
 * The PhysicsC component defines the physical properties of an entity,
 * including mass, friction, restitution, and collider information.
 * Entities with this component interact with the physics simulation.
 */

/**
 * @struct PhysicsC
 * @brief Component that defines physical properties for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for physics systems to simulate the entity in the physical world.
 * It includes properties for mass, friction, collision, and gravity effects.
 */
struct PhysicsC : public IComponent
{
    /** @brief The mass of the entity in kg */
    float mass;

    /** @brief Friction coefficient (0.0 = no friction, 1.0 = high friction) */
    float friction;

    /** @brief Restitution (bounciness) coefficient (0.0 = no bounce, 1.0 = perfect bounce) */
    float restitution;

    /** @brief Type of collider (e.g., "box", "sphere", "capsule", etc.) */
    std::string colliderType;

    /** @brief Size of the collider in each dimension (x, y, z) */
    float colliderSize[3];

    /** @brief Whether the entity is kinematic (moved by script, not by physics) */
    bool isKinematic;

    /** @brief Whether the entity is affected by gravity */
    bool useGravity;

    /**
     * @brief Construct a new PhysicsC component.
     *
     * @param m Mass of the entity (default: 1.0)
     * @param f Friction coefficient (default: 0.5)
     * @param r Restitution coefficient (default: 0.3)
     * @param cType Type of collider (default: "sphere")
     * @param k Whether the entity is kinematic (default: false)
     * @param g Whether the entity is affected by gravity (default: true)
     */
    PhysicsC(float m = 1.0f,
             float f = 0.5f,
             float r = 0.3f,
             std::string cType = "sphere",
             bool k = false,
             bool g = true)
        : mass(m), friction(f), restitution(r), colliderType(cType),
          isKinematic(k), useGravity(g)
    {
        colliderSize[0] = colliderSize[1] = colliderSize[2] = 1.0f;
    }
};

