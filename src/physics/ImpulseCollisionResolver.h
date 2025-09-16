/**
 * @file ImpulseCollisionResolver.h
 * @brief Implementation of impulse-based collision resolution.
 *
 * This file implements an impulse-based collision response system that
 * calculates collision impulses and applies them to resolve object collisions
 * with surfaces, taking into account friction and restitution.
 */

#ifndef IMPULSECOLLISIONRESOLVER_H
#define IMPULSECOLLISIONRESOLVER_H

#include "ICollisionResolver.h"

/**
 * @class ImpulseCollisionResolver
 * @brief Collision resolver using impulse-based response calculations.
 *
 * This implementation uses classical mechanics to calculate collision impulses
 * based on conservation of momentum and energy. It handles both normal and
 * tangential components of collisions, applying friction and restitution effects.
 */
class ImpulseCollisionResolver : public ICollisionResolver
{
public:
    /**
     * @brief Construct a new ImpulseCollisionResolver.
     *
     * @param friction Coefficient of friction (0.0 = no friction, 1.0 = high friction)
     * @param restitution Default coefficient of restitution if not specified in resolveCollision
     */
    ImpulseCollisionResolver(float friction, float restitution);

    /**
     * @brief Resolve a collision using impulse-based calculations.
     *
     * Calculates the collision impulse based on the relative velocity,
     * surface normal, and material properties. Applies both normal and
     * tangential impulse components.
     *
     * @param vx [in,out] X component of object velocity (modified by collision response)
     * @param vy [in,out] Y component of object velocity (modified by collision response)
     * @param vz [in,out] Z component of object velocity (modified by collision response)
     * @param normalX X component of the surface normal vector
     * @param normalY Y component of the surface normal vector
     * @param normalZ Z component of the surface normal vector
     * @param restitution Coefficient of restitution for this collision
     */
    void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) override;

private:
    /** @brief Default coefficient of friction for surfaces */
    float friction_;

    /** @brief Default coefficient of restitution for collisions */
    float restitution_;
};

#endif

