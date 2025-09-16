/**
 * @file ImpulseCollisionResolver.cpp
 * @brief Implementation of impulse-based collision resolution.
 */

#include "ImpulseCollisionResolver.h"
#include "../debug.h"

/**
 * @brief Construct a new ImpulseCollisionResolver.
 *
 * Initializes the collision resolver with default friction and restitution values.
 *
 * @param friction Coefficient of friction (0.0 = no friction, 1.0 = high friction)
 * @param restitution Default coefficient of restitution (0.0 = inelastic, 1.0 = elastic)
 */
ImpulseCollisionResolver::ImpulseCollisionResolver(float friction, float restitution)
    : friction_(friction), restitution_(restitution)
{
    DEBUG_LOG("Initializing ImpulseCollisionResolver with friction " + std::to_string(friction) + " and restitution " + std::to_string(restitution));
}

/**
 * @brief Resolve a collision using impulse-based calculations.
 *
 * This is a simplified implementation that applies an impulse to reverse
 * the component of velocity towards the surface. The impulse magnitude
 * is calculated based on the coefficient of restitution.
 *
 * Note: This is currently a stub implementation. A full impulse-based
 * resolver would include friction calculations and proper impulse magnitude
 * determination based on object masses and collision geometry.
 *
 * @param vx [in,out] X component of object velocity (modified by collision response)
 * @param vy [in,out] Y component of object velocity (modified by collision response)
 * @param vz [in,out] Z component of object velocity (modified by collision response)
 * @param normalX X component of the surface normal vector
 * @param normalY Y component of the surface normal vector
 * @param normalZ Z component of the surface normal vector
 * @param restitution Coefficient of restitution for this collision
 */
void ImpulseCollisionResolver::resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution)
{
    DEBUG_LOG("Resolving collision with restitution " + std::to_string(restitution));
    // Calculate the component of velocity towards the surface
    float dot = vx * normalX + vy * normalY + vz * normalZ;

    // Only resolve if object is moving towards the surface
    if (dot < 0)
    {
        // Apply impulse to reverse the normal component of velocity
        // Formula: v' = v - (1+e) * (v·n) * n
        // where e is the coefficient of restitution
        vx -= (1 + restitution) * dot * normalX;
        vy -= (1 + restitution) * dot * normalY;
        vz -= (1 + restitution) * dot * normalZ;
    }
}

