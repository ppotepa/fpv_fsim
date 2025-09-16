#pragma once
#include "../core/IComponent.h"
#include "../core/Vector3D.h"
#include "../core/Quaternion.h"

/**
 * @file TransformC.h
 * @brief Component for entities that have spatial positioning and orientation.
 *
 * The TransformC component defines the spatial properties of an entity in 3D space,
 * including position, rotation, and scale. This is a fundamental component used
 * by most entities in the simulation for positioning and transformation.
 */

/**
 * @struct TransformC
 * @brief Component that defines the spatial transformation of an entity.
 *
 * This component inherits from IComponent and provides 3D transformation
 * properties including position, rotation (as quaternion), and scale.
 * Transform components are processed by transformation and rendering systems.
 */
struct TransformC : public IComponent
{
    /** @brief Position of the entity in 3D world space */
    Vector3D position;

    /** @brief Rotation of the entity as a quaternion */
    Quaternion rotation;

    /** @brief Scale of the entity in each axis */
    Vector3D scale;

    /**
     * @brief Construct a new TransformC component.
     *
     * @param pos Initial position (default: origin)
     * @param rot Initial rotation (default: identity quaternion)
     * @param scl Initial scale (default: unit scale)
     */
    TransformC(Vector3D pos = Vector3D(), Quaternion rot = Quaternion(), Vector3D scl = Vector3D(1.0f, 1.0f, 1.0f))
        : position(pos), rotation(rot), scale(scl) {}
};

