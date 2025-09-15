/**
 * @file VoxelCloudC.h
 * @brief Voxel cloud component for orbital cloud systems
 *
 * The VoxelCloudC component manages large-scale orbital cloud formations
 * that consist of multiple voxel elements. Features include:
 * - Orbital precession with slow rotation around multiple axes
 * - Procedural cloud density and lifecycle management
 * - Fade curves for natural appearance and disappearance
 * - Integration with orbital mechanics for realistic motion
 * - Hierarchical cloud structure with multiple detail levels
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Component for large-scale orbital voxel cloud systems
 *
 * Manages collections of voxel elements that move in complex orbital
 * patterns with precession and hierarchical organization. Clouds can
 * have multiple detail levels and smooth lifecycle transitions.
 */
class VoxelCloudC
{
public:
    /**
     * @brief Individual voxel element in the cloud
     */
    struct VoxelElement
    {
        Math::float3 localPosition; /**< Position relative to cloud center */
        Math::float3 velocity;      /**< Current velocity vector */
        float density;              /**< Voxel density/opacity [0,1] */
        float size;                 /**< Voxel size multiplier */
        float age;                  /**< Element age in seconds */
        float maxAge;               /**< Maximum element lifetime */
        bool active;                /**< Whether element is active */

        VoxelElement() : localPosition{0, 0, 0}, velocity{0, 0, 0}, density(1), size(1), age(0), maxAge(10), active(false) {}
    };

    /** @brief Phase offset for density animation uniqueness */
    float densityPhase;

    /**
     * @brief Cloud configuration parameters
     */
    struct CloudParams
    {
        Math::OrbitParams primaryOrbit;    /**< Primary orbital motion */
        Math::OrbitParams precessionOrbit; /**< Precession orbital motion */
        float cloudRadius;                 /**< Maximum cloud extent */
        float elementCount;                /**< Target number of voxel elements */
        float densityVariation;            /**< Random density variation [0,1] */
        float sizeVariation;               /**< Random size variation [0,1] */
        float turbulenceStrength;          /**< Internal turbulence factor */
        float cohesionStrength;            /**< Element attraction to center */
        float fadeInTime;                  /**< Time to fade in from spawn */
        float fadeOutTime;                 /**< Time to fade out before death */

        CloudParams()
            : cloudRadius(2.0f), elementCount(50.0f), densityVariation(0.3f), sizeVariation(0.4f), turbulenceStrength(0.1f), cohesionStrength(0.5f), fadeInTime(2.0f), fadeOutTime(3.0f)
        {
            // Default primary orbit (large, slow)
            primaryOrbit.semiMajorAxis = 8.0f;
            primaryOrbit.eccentricity = 0.1f;
            primaryOrbit.angularRate = 0.1f;
            primaryOrbit.inclination = 0.2f;
            primaryOrbit.phaseOffset = 0.0f;

            // Default precession orbit (slow rotation)
            precessionOrbit.semiMajorAxis = 1.0f;
            precessionOrbit.eccentricity = 0.0f;
            precessionOrbit.angularRate = 0.02f;
            precessionOrbit.inclination = 0.1f;
            precessionOrbit.phaseOffset = 0.0f;
        }
    };

private:
    /** @brief Current cloud configuration */
    CloudParams params;

    /** @brief Cloud center position in world space */
    Math::float3 worldPosition;

    /** @brief Current cloud orientation quaternion */
    Math::quat worldOrientation;

    /** @brief Active voxel elements */
    std::vector<VoxelElement> elements;

    /** @brief Current primary orbital time */
    float primaryTime;

    /** @brief Current precession orbital time */
    float precessionTime;

    /** @brief Random state for procedural generation */
    uint32_t randomState;

    /** @brief Cloud lifecycle state */
    enum LifecycleState
    {
        SPAWNING,  /**< Cloud is fading in */
        ACTIVE,    /**< Cloud is fully active */
        DESPAWNING /**< Cloud is fading out */
    } lifecycleState;

    /** @brief Current lifecycle time */
    float lifecycleTime;

    /** @brief Total cloud lifetime (0 = infinite) */
    float totalLifetime;

public:
    /**
     * @brief Construct a new VoxelCloudC component
     *
     * @param cloudLifetime Total cloud lifetime (0 for infinite)
     * @param seed Random seed for procedural generation
     */
    VoxelCloudC(float cloudLifetime = 0.0f, uint32_t seed = 12345)
        : worldPosition{0, 0, 0}, worldOrientation(Math::quat::identity()), primaryTime(0.0f), precessionTime(0.0f), randomState(seed), lifecycleState(SPAWNING), lifecycleTime(0.0f), totalLifetime(cloudLifetime)
    {
        generateElements();
    }

    /**
     * @brief Set cloud parameters
     *
     * @param newParams New configuration parameters
     */
    void setParams(const CloudParams &newParams)
    {
        params = newParams;
        generateElements(); // Regenerate with new parameters
    }

    /**
     * @brief Get current cloud parameters
     *
     * @return Current configuration parameters
     */
    const CloudParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Update cloud simulation
     *
     * @param deltaTime Time step in seconds
     * @param globalCenter Global center point for orbital motion
     */
    void update(float deltaTime, const Math::float3 &globalCenter)
    {
        // Update orbital times
        primaryTime += deltaTime;
        precessionTime += deltaTime;

        // Update lifecycle
        updateLifecycle(deltaTime);

        // Calculate orbital positions
        updateOrbitalMotion(globalCenter);

        // Update individual elements
        updateElements(deltaTime);
    }

    /**
     * @brief Get current world position of cloud center
     *
     * @return World space position
     */
    Math::float3 getWorldPosition() const
    {
        return worldPosition;
    }

    /**
     * @brief Get current world orientation of cloud
     *
     * @return World space orientation quaternion
     */
    Math::quat getWorldOrientation() const
    {
        return worldOrientation;
    }

    /**
     * @brief Get all active voxel elements
     *
     * @return Vector of active elements
     */
    std::vector<VoxelElement> getActiveElements() const
    {
        std::vector<VoxelElement> active;
        for (const auto &element : elements)
        {
            if (element.active && element.density > 0.01f)
            {
                active.push_back(element);
            }
        }
        return active;
    }

    /**
     * @brief Get element world positions
     *
     * @return Vector of world space positions for all active elements
     */
    std::vector<Math::float3> getElementWorldPositions() const
    {
        std::vector<Math::float3> positions;
        for (const auto &element : elements)
        {
            if (element.active && element.density > 0.01f)
            {
                // Transform local position to world space
                Math::float3 rotatedPos = Math::q_rotate(worldOrientation, element.localPosition);
                Math::float3 worldPos = Math::add(worldPosition, rotatedPos);
                positions.push_back(worldPos);
            }
        }
        return positions;
    }

    /**
     * @brief Check if cloud is in despawning state
     *
     * @return True if cloud is fading out
     */
    bool isDespawning() const
    {
        return lifecycleState == DESPAWNING;
    }

    /**
     * @brief Check if cloud should be destroyed
     *
     * @return True if cloud lifecycle is complete
     */
    bool shouldDestroy() const
    {
        return lifecycleState == DESPAWNING && lifecycleTime >= params.fadeOutTime;
    }

    /**
     * @brief Force cloud to start despawning
     */
    void startDespawning()
    {
        if (lifecycleState != DESPAWNING)
        {
            lifecycleState = DESPAWNING;
            lifecycleTime = 0.0f;
        }
    }

private:
    /**
     * @brief Generate voxel elements based on current parameters
     */
    void generateElements()
    {
        elements.clear();
        elements.reserve(static_cast<size_t>(params.elementCount));

        for (int i = 0; i < static_cast<int>(params.elementCount); ++i)
        {
            VoxelElement element;

            // Generate random position within cloud radius using sphere distribution
            float radius = params.cloudRadius * std::pow(Math::rand01(randomState), 1.0f / 3.0f);
            float theta = 2.0f * Math::Pi * Math::rand01(randomState);
            float phi = std::acos(2.0f * Math::rand01(randomState) - 1.0f);

            element.localPosition.x = radius * std::sin(phi) * std::cos(theta);
            element.localPosition.y = radius * std::sin(phi) * std::sin(theta);
            element.localPosition.z = radius * std::cos(phi);

            // Random velocity for internal motion
            element.velocity.x = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;
            element.velocity.y = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;
            element.velocity.z = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;

            // Random properties
            element.density = 1.0f - params.densityVariation * Math::rand01(randomState);
            element.size = 1.0f - params.sizeVariation * (Math::rand01(randomState) - 0.5f);
            element.age = 0.0f;
            element.maxAge = 20.0f + 40.0f * Math::rand01(randomState); // Variable lifetime
            element.active = true;

            elements.push_back(element);
        }
    }

    /**
     * @brief Update cloud lifecycle state
     *
     * @param deltaTime Time step in seconds
     */
    void updateLifecycle(float deltaTime)
    {
        lifecycleTime += deltaTime;

        switch (lifecycleState)
        {
        case SPAWNING:
            if (lifecycleTime >= params.fadeInTime)
            {
                lifecycleState = ACTIVE;
                lifecycleTime = 0.0f;
            }
            break;

        case ACTIVE:
            if (totalLifetime > 0.0f && lifecycleTime >= totalLifetime)
            {
                lifecycleState = DESPAWNING;
                lifecycleTime = 0.0f;
            }
            break;

        case DESPAWNING:
            // Handled in shouldDestroy()
            break;
        }
    }

    /**
     * @brief Update orbital motion calculation
     *
     * @param globalCenter Global center for orbital motion
     */
    void updateOrbitalMotion(const Math::float3 &globalCenter)
    {
        // Calculate primary orbital position
        Math::float3 primaryPos = Math::calculateOrbitPosition(params.primaryOrbit, primaryTime);

        // Calculate precession rotation
        Math::float3 precessionAxis = {0, 1, 0}; // Default vertical axis
        float precessionAngle = precessionTime * params.precessionOrbit.angularRate;
        Math::quat precessionQuat = Math::q_from_axis_angle(precessionAxis, precessionAngle);

        // Apply inclination to precession
        Math::float3 inclinationAxis = {1, 0, 0};
        Math::quat inclinationQuat = Math::q_from_axis_angle(inclinationAxis, params.precessionOrbit.inclination);

        // Combine rotations
        worldOrientation = Math::q_mul(inclinationQuat, precessionQuat);

        // Calculate final world position
        worldPosition = Math::add(globalCenter, primaryPos);
    }

    /**
     * @brief Update individual voxel elements
     *
     * @param deltaTime Time step in seconds
     */
    void updateElements(float deltaTime)
    {
        float globalAlpha = 1.0f;

        // Calculate global alpha based on lifecycle
        switch (lifecycleState)
        {
        case SPAWNING:
            globalAlpha = Math::fadeIn(lifecycleTime / params.fadeInTime);
            break;
        case ACTIVE:
            globalAlpha = 1.0f;
            break;
        case DESPAWNING:
            globalAlpha = Math::fadeOut(lifecycleTime / params.fadeOutTime);
            break;
        }

        for (auto &element : elements)
        {
            if (!element.active)
                continue;

            // Age the element
            element.age += deltaTime;

            // Apply cohesion force (attraction to center)
            Math::float3 toCenter = Math::scale(element.localPosition, -1.0f);
            float distance = Math::len(toCenter);
            if (distance > 0.01f)
            {
                Math::float3 cohesionForce = Math::scale(
                    Math::norm(toCenter),
                    params.cohesionStrength / (1.0f + distance));
                element.velocity = Math::add(element.velocity, Math::scale(cohesionForce, deltaTime));
            }

            // Apply velocity damping
            element.velocity = Math::scale(element.velocity, std::pow(0.9f, deltaTime));

            // Update position
            element.localPosition = Math::add(element.localPosition, Math::scale(element.velocity, deltaTime));

            // Keep elements within cloud radius
            float distanceFromCenter = Math::len(element.localPosition);
            if (distanceFromCenter > params.cloudRadius)
            {
                element.localPosition = Math::scale(
                    Math::norm(element.localPosition),
                    params.cloudRadius);
            }

            // Update density based on age and global lifecycle
            float ageFactor = 1.0f;
            if (element.age > element.maxAge * 0.8f)
            {
                ageFactor = Math::fadeOut((element.age - element.maxAge * 0.8f) / (element.maxAge * 0.2f));
            }

            element.density = (1.0f - params.densityVariation * Math::rand01(randomState)) * globalAlpha * ageFactor;

            // Deactivate old elements
            if (element.age > element.maxAge || element.density < 0.01f)
            {
                element.active = false;
            }
        }
    }
};
