#pragma once
#include "../core/IComponent.h"
#include "../math/MathUtils.h"

/**
 * @file OrbitalC.h
 * @brief Component for entities that follow orbital motion around a center point
 *
 * The OrbitalC component defines orbital motion parameters including center point,
 * orbital radius, angular speed, orbital axis, and phase offset. Entities with this
 * component will be updated by the OrbitalSystem to follow elliptical orbital paths
 * with proper velocity-based orientation and banking for aircraft.
 */

/**
 * @struct OrbitalC
 * @brief Component that defines orbital motion properties for an entity
 *
 * This component inherits from IComponent and provides all necessary parameters
 * for realistic orbital motion including elliptical orbits, inclination, and
 * coordinated banking for aircraft entities.
 */
struct OrbitalC : public IComponent
{
    /** @brief Center point of orbital motion in world space */
    Math::float3 center;

    /** @brief Orbital parameters for elliptical motion */
    Math::OrbitParams orbitParams;

    /** @brief Current time accumulator for orbit calculation */
    float currentTime;

    /** @brief Whether to apply banking for aircraft-like entities */
    bool enableBanking;

    /** @brief Maximum banking angle in radians (for aircraft) */
    float maxBankAngle;

    /** @brief Speed jitter percentage for natural variation */
    float speedJitter;

    /** @brief Random seed for deterministic jitter */
    uint32_t randomSeed;

    /** @brief Current banking angle (internal state) */
    float currentBankAngle;

    /** @brief Current banking rate (internal state) */
    float currentBankRate;

    /**
     * @brief Construct a new OrbitalC component
     *
     * @param centerPoint Center of orbital motion (default: origin)
     * @param radius Orbital radius (default: 1.0)
     * @param speed Angular speed in rad/s (default: 1.0)
     * @param axis Orbital axis (default: Y-axis)
     * @param phase Initial phase offset (default: 0.0)
     * @param banking Enable banking for aircraft (default: false)
     */
    OrbitalC(const Math::float3 &centerPoint = {0, 0, 0},
             float radius = 1.0f,
             float speed = 1.0f,
             const Math::float3 &axis = {0, 1, 0},
             float phase = 0.0f,
             bool banking = false)
        : center(centerPoint), currentTime(0.0f), enableBanking(banking), maxBankAngle(15.0f * Math::DegToRad), speedJitter(0.0f), randomSeed(12345), currentBankAngle(0.0f), currentBankRate(0.0f)
    {
        // Initialize orbital parameters
        orbitParams.semiMajorAxis = radius;
        orbitParams.eccentricity = 0.0f; // circular by default
        orbitParams.angularRate = speed;
        orbitParams.phaseOffset = phase;

        // Calculate inclination from axis (assume axis is rotation axis)
        Math::float3 worldY = {0, 1, 0};
        Math::float3 normalizedAxis = Math::norm(axis);
        orbitParams.inclination = std::acos(Math::clamp(Math::dot(normalizedAxis, worldY), -1.0f, 1.0f));
    }

    /**
     * @brief Get current orbital position
     *
     * @return Current 3D position on orbit relative to center
     */
    Math::float3 getCurrentPosition() const
    {
        // Apply speed jitter if enabled
        float jitteredTime = currentTime;
        if (speedJitter > 0.0f)
        {
            uint32_t state = randomSeed;
            float jitter = 1.0f + speedJitter * (2.0f * Math::rand01(state) - 1.0f);
            jitteredTime *= jitter;
        }

        Math::float3 localPos = Math::calculateOrbitPosition(orbitParams, jitteredTime);
        return Math::add(center, localPos);
    }

    /**
     * @brief Get current orbital velocity
     *
     * @return Current 3D velocity vector
     */
    Math::float3 getCurrentVelocity() const
    {
        return Math::calculateOrbitVelocity(orbitParams, currentTime);
    }

    /**
     * @brief Get current orientation quaternion (for aircraft with banking)
     *
     * @return Orientation quaternion with velocity alignment and banking
     */
    Math::quat getCurrentOrientation() const
    {
        Math::float3 velocity = getCurrentVelocity();
        Math::float3 position = getCurrentPosition();

        if (Math::len(velocity) < 1e-4f)
        {
            return Math::quat::identity();
        }

        // Forward direction aligned with velocity
        Math::float3 forward = Math::norm(velocity);

        if (enableBanking)
        {
            // Calculate banking angle for coordinated turn
            float bankAngle = Math::calculateBankingAngle(velocity, Math::sub(position, center), maxBankAngle);

            // Apply banking to up vector
            Math::float3 worldUp = {0, 1, 0};
            Math::float3 right = Math::norm(Math::cross(worldUp, forward));
            Math::float3 up = Math::cross(forward, right);

            // Roll around forward axis for banking
            Math::quat bankRotation = Math::q_from_axis_angle(forward, bankAngle);
            Math::float3 bankedUp = Math::q_rotate(bankRotation, up);

            return Math::q_look_rotation(forward, bankedUp);
        }
        else
        {
            // Simple velocity alignment without banking
            Math::float3 worldUp = {0, 1, 0};
            return Math::q_look_rotation(forward, worldUp);
        }
    }

    /**
     * @brief Set elliptical orbit parameters
     *
     * @param semiMajor Semi-major axis length
     * @param eccentricity Orbital eccentricity [0,1)
     */
    void setEllipticalOrbit(float semiMajor, float eccentricity)
    {
        orbitParams.semiMajorAxis = semiMajor;
        orbitParams.eccentricity = Math::clamp(eccentricity, 0.0f, 0.99f);
    }

    /**
     * @brief Set orbital inclination angle
     *
     * @param inclinationDegrees Inclination angle in degrees
     */
    void setInclination(float inclinationDegrees)
    {
        orbitParams.inclination = inclinationDegrees * Math::DegToRad;
    }

    /**
     * @brief Enable speed jitter for natural orbital variation
     *
     * @param jitterPercent Jitter percentage (e.g., 0.05 for ±5%)
     * @param seed Random seed for deterministic jitter
     */
    void setSpeedJitter(float jitterPercent, uint32_t seed)
    {
        speedJitter = jitterPercent;
        randomSeed = seed;
    }

    /**
     * @brief Update orbital motion by time step
     *
     * @param deltaTime Time step in seconds
     */
    void update(float deltaTime)
    {
        currentTime += deltaTime;
    }

    /**
     * @brief Reset orbital time to specific value
     *
     * @param time New time value
     */
    void setTime(float time)
    {
        currentTime = time;
    }
};
