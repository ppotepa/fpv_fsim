/**
 * @file ContrailC.h
 * @brief Contrail component for particle trail effects behind aircraft
 *
 * The ContrailC component creates and manages particle-based trail effects
 * that follow aircraft in orbital motion. Features include:
 * - Physics-based particle lifecycle with fade curves
 * - Velocity-based particle spawning
 * - Configurable trail length and density
 * - Smooth particle interpolation for visual continuity
 * - Integration with orbital motion systems
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Component for particle-based contrail effects
 *
 * Creates trailing particle effects behind moving aircraft with realistic
 * physics simulation and smooth visual transitions. Particles are spawned
 * based on velocity and fade over time using configurable curves.
 */
class ContrailC
{
public:
    /**
     * @brief Individual particle in the contrail system
     */
    struct Particle
    {
        Math::float3 position; /**< Current particle position */
        Math::float3 velocity; /**< Current particle velocity */
        float age;             /**< Particle age in seconds */
        float maxAge;          /**< Maximum particle lifetime */
        float size;            /**< Current particle size */
        float alpha;           /**< Current particle alpha/opacity */
        bool active;           /**< Whether particle is active */

        Particle() : position{0, 0, 0}, velocity{0, 0, 0}, age(0), maxAge(1), size(1), alpha(1), active(false) {}
    };

    /**
     * @brief Contrail configuration parameters
     */
    struct ContrailParams
    {
        float spawnRate;           /**< Particles per second */
        float particleLifetime;    /**< Max particle age in seconds */
        float initialSize;         /**< Starting particle size */
        float finalSize;           /**< Ending particle size */
        float velocityInheritance; /**< How much parent velocity particles inherit [0,1] */
        float gravityStrength;     /**< Downward gravity acceleration */
        float dragCoefficient;     /**< Air resistance factor */
        Math::float3 windVelocity; /**< Environmental wind vector */

        ContrailParams()
            : spawnRate(20.0f), particleLifetime(3.0f), initialSize(0.1f), finalSize(0.05f), velocityInheritance(0.3f), gravityStrength(0.5f), dragCoefficient(0.8f), windVelocity{0, 0, 0}
        {
        }
    };

private:
    /** @brief Current contrail configuration */
    ContrailParams params;

    /** @brief Active particle pool */
    std::vector<Particle> particles;

    /** @brief Maximum number of particles */
    size_t maxParticles;

    /** @brief Time accumulator for particle spawning */
    float spawnAccumulator;

    /** @brief Random state for particle variation */
    uint32_t randomState;

    /** @brief Whether contrail emission is enabled */
    bool emissionEnabled;

    /** @brief Last position for velocity calculation */
    Math::float3 lastPosition;

    /** @brief Whether last position is valid */
    bool hasLastPosition;

public:
    /**
     * @brief Construct a new ContrailC component
     *
     * @param maxParticleCount Maximum number of particles in the system
     * @param emitParticles Whether to start emitting particles immediately
     */
    ContrailC(size_t maxParticleCount = 100, bool emitParticles = true)
        : maxParticles(maxParticleCount), spawnAccumulator(0.0f), randomState(42), emissionEnabled(emitParticles), lastPosition{0, 0, 0}, hasLastPosition(false)
    {
        particles.reserve(maxParticles);
    }

    /**
     * @brief Set contrail parameters
     *
     * @param newParams New configuration parameters
     */
    void setParams(const ContrailParams &newParams)
    {
        params = newParams;
    }

    /**
     * @brief Get current contrail parameters
     *
     * @return Current configuration parameters
     */
    const ContrailParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Enable or disable particle emission
     *
     * @param enabled Whether to emit new particles
     */
    void setEmissionEnabled(bool enabled)
    {
        emissionEnabled = enabled;
    }

    /**
     * @brief Check if particle emission is enabled
     *
     * @return True if emitting particles
     */
    bool isEmissionEnabled() const
    {
        return emissionEnabled;
    }

    /**
     * @brief Update contrail simulation
     *
     * @param deltaTime Time step in seconds
     * @param currentPosition Current emitter position
     */
    void update(float deltaTime, const Math::float3 &currentPosition)
    {
        // Calculate velocity from position change
        Math::float3 velocity = {0, 0, 0};
        if (hasLastPosition)
        {
            velocity = Math::scale(Math::sub(currentPosition, lastPosition), 1.0f / deltaTime);
        }

        // Update existing particles
        updateParticles(deltaTime);

        // Spawn new particles if emission is enabled
        if (emissionEnabled)
        {
            spawnParticles(deltaTime, currentPosition, velocity);
        }

        // Update last position
        lastPosition = currentPosition;
        hasLastPosition = true;
    }

    /**
     * @brief Get all active particles
     *
     * @return Vector of active particles
     */
    std::vector<Particle> getActiveParticles() const
    {
        std::vector<Particle> active;
        for (const auto &particle : particles)
        {
            if (particle.active)
            {
                active.push_back(particle);
            }
        }
        return active;
    }

    /**
     * @brief Get number of active particles
     *
     * @return Count of active particles
     */
    size_t getActiveParticleCount() const
    {
        size_t count = 0;
        for (const auto &particle : particles)
        {
            if (particle.active)
                count++;
        }
        return count;
    }

    /**
     * @brief Clear all particles
     */
    void clearParticles()
    {
        for (auto &particle : particles)
        {
            particle.active = false;
        }
    }

private:
    /**
     * @brief Update all active particles
     *
     * @param deltaTime Time step in seconds
     */
    void updateParticles(float deltaTime)
    {
        for (auto &particle : particles)
        {
            if (!particle.active)
                continue;

            // Age the particle
            particle.age += deltaTime;

            // Check if particle should die
            if (particle.age >= particle.maxAge)
            {
                particle.active = false;
                continue;
            }

            // Calculate age ratio for fade curves
            float ageRatio = particle.age / particle.maxAge;

            // Apply physics forces
            Math::float3 forces = {0, 0, 0};

            // Gravity
            forces = Math::add(forces, {0, -params.gravityStrength, 0});

            // Drag (air resistance)
            Math::float3 dragForce = Math::scale(particle.velocity, -params.dragCoefficient);
            forces = Math::add(forces, dragForce);

            // Wind
            Math::float3 windForce = Math::scale(
                Math::sub(params.windVelocity, particle.velocity),
                params.dragCoefficient * 0.5f);
            forces = Math::add(forces, windForce);

            // Update velocity and position
            particle.velocity = Math::add(particle.velocity, Math::scale(forces, deltaTime));
            particle.position = Math::add(particle.position, Math::scale(particle.velocity, deltaTime));

            // Update visual properties using fade curves
            particle.size = Math::lerp(params.initialSize, params.finalSize, ageRatio);
            particle.alpha = Math::fadeOut(ageRatio); // Smooth fade out over lifetime
        }
    }

    /**
     * @brief Spawn new particles based on emission rate
     *
     * @param deltaTime Time step in seconds
     * @param position Current emitter position
     * @param velocity Current emitter velocity
     */
    void spawnParticles(float deltaTime, const Math::float3 &position, const Math::float3 &velocity)
    {
        spawnAccumulator += deltaTime;

        float spawnInterval = 1.0f / params.spawnRate;
        while (spawnAccumulator >= spawnInterval)
        {
            spawnParticle(position, velocity);
            spawnAccumulator -= spawnInterval;
        }
    }

    /**
     * @brief Spawn a single particle
     *
     * @param position Spawn position
     * @param velocity Emitter velocity
     */
    void spawnParticle(const Math::float3 &position, const Math::float3 &velocity)
    {
        // Find inactive particle slot
        Particle *particle = nullptr;
        for (auto &p : particles)
        {
            if (!p.active)
            {
                particle = &p;
                break;
            }
        }

        // If no slot available and under max count, add new particle
        if (!particle && particles.size() < maxParticles)
        {
            particles.emplace_back();
            particle = &particles.back();
        }

        // If still no slot, skip spawning
        if (!particle)
            return;

        // Initialize particle
        particle->active = true;
        particle->age = 0.0f;
        particle->maxAge = params.particleLifetime * (0.8f + 0.4f * Math::rand01(randomState));

        // Position with small random offset
        Math::float3 offset = {
            (Math::rand01(randomState) - 0.5f) * 0.02f,
            (Math::rand01(randomState) - 0.5f) * 0.02f,
            (Math::rand01(randomState) - 0.5f) * 0.02f};
        particle->position = Math::add(position, offset);

        // Velocity inheritance with random variation
        Math::float3 inheritedVel = Math::scale(velocity, params.velocityInheritance);
        Math::float3 randomVel = {
            (Math::rand01(randomState) - 0.5f) * 0.1f,
            (Math::rand01(randomState) - 0.5f) * 0.1f,
            (Math::rand01(randomState) - 0.5f) * 0.1f};
        particle->velocity = Math::add(inheritedVel, randomVel);

        // Visual properties
        particle->size = params.initialSize;
        particle->alpha = 1.0f;
    }
};
