/**
 * @file ICollisionResolver.h
 * @brief Interface for collision resolution algorithms.
 *
 * This interface defines the contract for collision resolution systems that
 * handle the physics of objects colliding with surfaces. Different implementations
 * can provide various collision response models (impulse-based, penalty-based, etc.).
 */

#ifndef ICOLLISIONRESOLVER_H
#define ICOLLISIONRESOLVER_H

/**
 * @class ICollisionResolver
 * @brief Abstract interface for resolving collisions between objects and surfaces.
 *
 * This interface provides a standardized way to handle collision responses.
 * Implementations calculate how an object's velocity should change when it
 * collides with a surface, taking into account factors like restitution (bounciness).
 */
class ICollisionResolver
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~ICollisionResolver() = default;

    /**
     * @brief Resolve a collision by modifying object velocity.
     *
     * This method calculates the post-collision velocity of an object based on
     * its pre-collision velocity, the surface normal, and the coefficient of restitution.
     *
     * @param vx [in,out] X component of object velocity (modified by collision response)
     * @param vy [in,out] Y component of object velocity (modified by collision response)
     * @param vz [in,out] Z component of object velocity (modified by collision response)
     * @param normalX X component of the surface normal vector
     * @param normalY Y component of the surface normal vector
     * @param normalZ Z component of the surface normal vector
     * @param restitution Coefficient of restitution (0.0 = perfectly inelastic, 1.0 = perfectly elastic)
     */
    virtual void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) = 0;
};

#endif

