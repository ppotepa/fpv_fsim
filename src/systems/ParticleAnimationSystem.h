/**
 * @file ParticleAnimationSystem.h
 * @brief Animation system for particle effects management
 *
 * The ParticleAnimationSystem manages particle-based effects including
 * contrails, explosions, and other dynamic particle systems. Features include:
 * - Automatic particle lifecycle management
 * - Physics integration for realistic motion
 * - Emitter following for trail effects
 * - Performance optimization through pooling
 * - Integration with Math utilities for physics
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/ContrailC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * @brief Animation system for particle effects
 *
 * Manages the update cycle for all particle-based effects,
 * ensuring smooth physics simulation and lifecycle management.
 */
class ParticleAnimationSystem
{
public:
    /**
     * @brief Entity with particle effects
     */
    struct ParticleEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<ContrailC> contrail;   /**< Contrail component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */
        Math::float3 lastPosition;             /**< Last known position */
        bool hasLastPosition;                  /**< Whether last position is valid */

        ParticleEntity(uint32_t id, std::shared_ptr<ContrailC> cont, std::shared_ptr<TransformC> trans)
            : entityId(id), contrail(cont), transform(trans), active(true), lastPosition{0, 0, 0}, hasLastPosition(false) {}
    };

    /**
     * @brief Particle effect group for synchronized behavior
     */
    struct ParticleGroup
    {
        std::string name;                /**< Group name */
        std::vector<uint32_t> entityIds; /**< Entities in this group */
        Math::float3 windVelocity;       /**< Shared wind velocity */
        float gravityStrength;           /**< Shared gravity strength */
        float timeScale;                 /**< Time scaling factor */
        bool sharedPhysics;              /**< Whether to use shared physics params */

        ParticleGroup(const std::string &groupName = "default")
            : name(groupName), windVelocity{0, 0, 0}, gravityStrength(9.81f), timeScale(1.0f), sharedPhysics(false)
        {
        }
    };

    /**
     * @brief Performance statistics
     */
    struct PerformanceStats
    {
        uint32_t totalParticles;   /**< Total active particles */
        uint32_t totalEmitters;    /**< Total active emitters */
        float updateTime;          /**< Last update time in milliseconds */
        uint32_t particlesSpawned; /**< Particles spawned this frame */
        uint32_t particlesDied;    /**< Particles died this frame */

        PerformanceStats() : totalParticles(0), totalEmitters(0), updateTime(0), particlesSpawned(0), particlesDied(0) {}
    };

private:
    /** @brief All registered particle entities */
    std::vector<ParticleEntity> entities;

    /** @brief Particle groups for synchronized behavior */
    std::unordered_map<std::string, ParticleGroup> groups;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Performance statistics */
    PerformanceStats stats;

    /** @brief Global physics parameters */
    Math::float3 globalWindVelocity;
    float globalGravityStrength;

public:
    /**
     * @brief Construct a new ParticleAnimationSystem
     */
    ParticleAnimationSystem()
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), globalWindVelocity{0, 0, 0}, globalGravityStrength(9.81f)
    {
        // Create default group
        groups["default"] = ParticleGroup("default");
    }

    /**
     * @brief Update all particle animations
     *
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime)
    {
        if (!systemActive)
            return;

        // Reset frame statistics
        stats.particlesSpawned = 0;
        stats.particlesDied = 0;
        stats.totalParticles = 0;
        stats.totalEmitters = 0;

        float startTime = globalTime; // For performance measurement

        float scaledDeltaTime = deltaTime * globalTimeScale;
        globalTime += scaledDeltaTime;

        // Update all particle entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.contrail || !entity.transform)
                continue;

            updateParticleEntity(entity, scaledDeltaTime);
            stats.totalEmitters++;
        }

        // Update group-specific effects
        updateGroups(scaledDeltaTime);

        // Calculate performance metrics
        stats.updateTime = (globalTime - startTime) * 1000.0f; // Convert to milliseconds
    }

    /**
     * @brief Register an entity for particle animation
     *
     * @param entityId Entity identifier
     * @param contrail Contrail component
     * @param transform Transform component
     * @param groupName Group to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<ContrailC> contrail,
                        std::shared_ptr<TransformC> transform,
                        const std::string &groupName = "default")
    {
        entities.emplace_back(entityId, contrail, transform);

        // Add to group
        auto &group = getOrCreateGroup(groupName);
        group.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from particle animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const ParticleEntity &e)
                           { return e.entityId == entityId; }),
            entities.end());

        // Remove from all groups
        for (auto &[groupName, group] : groups)
        {
            group.entityIds.erase(
                std::remove(group.entityIds.begin(), group.entityIds.end(), entityId),
                group.entityIds.end());
        }
    }

    /**
     * @brief Create or get a particle group
     *
     * @param groupName Name of the group
     * @return Reference to the group
     */
    ParticleGroup &getOrCreateGroup(const std::string &groupName)
    {
        if (groups.find(groupName) == groups.end())
        {
            groups[groupName] = ParticleGroup(groupName);
        }
        return groups[groupName];
    }

    /**
     * @brief Set group physics parameters
     *
     * @param groupName Group name
     * @param windVelocity Wind velocity vector
     * @param gravityStrength Gravity strength
     * @param timeScale Time scaling factor
     * @param sharedPhysics Whether to use shared physics
     */
    void setGroupPhysics(const std::string &groupName,
                         const Math::float3 &windVelocity = {0, 0, 0},
                         float gravityStrength = 9.81f,
                         float timeScale = 1.0f,
                         bool sharedPhysics = true)
    {
        auto &group = getOrCreateGroup(groupName);
        group.windVelocity = windVelocity;
        group.gravityStrength = gravityStrength;
        group.timeScale = timeScale;
        group.sharedPhysics = sharedPhysics;
    }

    /**
     * @brief Set global physics parameters
     *
     * @param windVelocity Global wind velocity
     * @param gravityStrength Global gravity strength
     */
    void setGlobalPhysics(const Math::float3 &windVelocity, float gravityStrength)
    {
        globalWindVelocity = windVelocity;
        globalGravityStrength = gravityStrength;
    }

    /**
     * @brief Set global time scale
     *
     * @param scale Time scaling factor (1.0 = normal speed)
     */
    void setGlobalTimeScale(float scale)
    {
        globalTimeScale = scale;
    }

    /**
     * @brief Get global time scale
     *
     * @return Current time scale
     */
    float getGlobalTimeScale() const
    {
        return globalTimeScale;
    }

    /**
     * @brief Pause/resume particle animations
     *
     * @param active Whether system should be active
     */
    void setActive(bool active)
    {
        systemActive = active;
    }

    /**
     * @brief Check if system is active
     *
     * @return True if system is running
     */
    bool isActive() const
    {
        return systemActive;
    }

    /**
     * @brief Get performance statistics
     *
     * @return Current performance stats
     */
    const PerformanceStats &getPerformanceStats() const
    {
        return stats;
    }

    /**
     * @brief Clear all particles in a group
     *
     * @param groupName Group to clear (empty = all groups)
     */
    void clearParticles(const std::string &groupName = "")
    {
        if (groupName.empty())
        {
            // Clear all particles
            for (auto &entity : entities)
            {
                if (entity.contrail)
                {
                    entity.contrail->clearParticles();
                }
            }
        }
        else
        {
            // Clear particles in specific group
            auto groupIt = groups.find(groupName);
            if (groupIt != groups.end())
            {
                for (uint32_t entityId : groupIt->second.entityIds)
                {
                    for (auto &entity : entities)
                    {
                        if (entity.entityId == entityId && entity.contrail)
                        {
                            entity.contrail->clearParticles();
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Get number of registered entities
     *
     * @return Entity count
     */
    size_t getEntityCount() const
    {
        return entities.size();
    }

    /**
     * @brief Get number of active entities
     *
     * @return Active entity count
     */
    size_t getActiveEntityCount() const
    {
        size_t count = 0;
        for (const auto &entity : entities)
        {
            if (entity.active)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Update a single particle entity
     *
     * @param entity Entity to update
     * @param deltaTime Time delta for this update
     */
    void updateParticleEntity(ParticleEntity &entity, float deltaTime)
    {
        // Get current position from transform
        Math::float3 currentPosition = entity.transform->getPosition();

        // Find the group this entity belongs to
        ParticleGroup *entityGroup = nullptr;
        for (auto &[groupName, group] : groups)
        {
            auto it = std::find(group.entityIds.begin(), group.entityIds.end(), entity.entityId);
            if (it != group.entityIds.end())
            {
                entityGroup = &group;
                break;
            }
        }

        // Apply group-specific physics if enabled
        if (entityGroup && entityGroup->sharedPhysics)
        {
            applyGroupPhysics(entity, *entityGroup);
            deltaTime *= entityGroup->timeScale;
        }
        else
        {
            applyGlobalPhysics(entity);
        }

        // Update contrail with current position
        entity.contrail->update(deltaTime, currentPosition);

        // Count particles for statistics
        stats.totalParticles += entity.contrail->getActiveParticleCount();

        // Update last position
        entity.lastPosition = currentPosition;
        entity.hasLastPosition = true;
    }

    /**
     * @brief Apply group-specific physics parameters
     *
     * @param entity Entity to update
     * @param group Group physics parameters
     */
    void applyGroupPhysics(ParticleEntity &entity, const ParticleGroup &group)
    {
        auto params = entity.contrail->getParams();
        params.windVelocity = group.windVelocity;
        params.gravityStrength = group.gravityStrength;
        entity.contrail->setParams(params);
    }

    /**
     * @brief Apply global physics parameters
     *
     * @param entity Entity to update
     */
    void applyGlobalPhysics(ParticleEntity &entity)
    {
        auto params = entity.contrail->getParams();
        params.windVelocity = globalWindVelocity;
        params.gravityStrength = globalGravityStrength;
        entity.contrail->setParams(params);
    }

    /**
     * @brief Update group-specific effects
     *
     * @param deltaTime Time delta for this update
     */
    void updateGroups(float deltaTime)
    {
        for (auto &[groupName, group] : groups)
        {
            updateGroup(group, deltaTime);
        }
    }

    /**
     * @brief Update a specific particle group
     *
     * @param group Group to update
     * @param deltaTime Time delta for this update
     */
    void updateGroup(ParticleGroup &group, float deltaTime)
    {
        // Group-specific animations could be added here
        // For example: synchronized emission patterns, group-wide effects, etc.

        // Currently, individual entity updates handle most functionality
        // This method is reserved for future group-level effects
    }
};
