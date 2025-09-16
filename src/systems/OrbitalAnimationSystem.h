/**
 * @file OrbitalAnimationSystem.h
 * @brief Animation system for orbital motion management
 *
 * The OrbitalAnimationSystem manages orbital motion for entities with
 * OrbitalC components. Features include:
 * - Automatic time advancement and position updates
 * - Synchronization between multiple orbital entities
 * - Speed scaling and time manipulation
 * - Integration with transform components
 * - Support for coordinated group animations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/OrbitalC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * @brief Animation system for orbital motion
 *
 * Manages the update cycle for all entities with orbital motion,
 * ensuring synchronized and smooth orbital animations.
 */
class OrbitalAnimationSystem
{
public:
    /**
     * @brief Entity reference for orbital updates
     */
    struct OrbitalEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<OrbitalC> orbital;     /**< Orbital component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */

        OrbitalEntity(uint32_t id, std::shared_ptr<OrbitalC> orb, std::shared_ptr<TransformC> trans)
            : entityId(id), orbital(orb), transform(trans), active(true) {}
    };

    /**
     * @brief Animation group for synchronized orbital motion
     */
    struct OrbitalGroup
    {
        std::string name;                /**< Group name */
        std::vector<uint32_t> entityIds; /**< Entities in this group */
        float timeScale;                 /**< Time scaling factor */
        float phaseOffset;               /**< Group phase offset */
        Math::float3 centerPoint;        /**< Group center point */
        bool synchronized;               /**< Whether group is synchronized */

        OrbitalGroup(const std::string &groupName = "default")
            : name(groupName), timeScale(1.0f), phaseOffset(0.0f), centerPoint{0, 0, 0}, synchronized(true)
        {
        }
    };

private:
    /** @brief All registered orbital entities */
    std::vector<OrbitalEntity> entities;

    /** @brief Orbital groups for synchronized animation */
    std::unordered_map<std::string, OrbitalGroup> groups;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Frame delta time for smooth updates */
    float deltaTime;

public:
    /**
     * @brief Construct a new OrbitalAnimationSystem
     */
    OrbitalAnimationSystem()
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), deltaTime(0.0f)
    {
        // Create default group
        groups["default"] = OrbitalGroup("default");
    }

    /**
     * @brief Update all orbital animations
     *
     * @param frameTime Time elapsed since last frame
     */
    void update(float frameTime)
    {
        if (!systemActive)
            return;

        deltaTime = frameTime * globalTimeScale;
        globalTime += deltaTime;

        // Update all orbital entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.orbital || !entity.transform)
                continue;

            updateEntity(entity);
        }

        // Update group-specific animations
        updateGroups();
    }

    /**
     * @brief Register an entity for orbital animation
     *
     * @param entityId Entity identifier
     * @param orbital Orbital component
     * @param transform Transform component
     * @param groupName Group to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<OrbitalC> orbital,
                        std::shared_ptr<TransformC> transform,
                        const std::string &groupName = "default")
    {
        entities.emplace_back(entityId, orbital, transform);

        // Add to group
        auto &group = getOrCreateGroup(groupName);
        group.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from orbital animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const OrbitalEntity &e)
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
     * @brief Create or get an orbital group
     *
     * @param groupName Name of the group
     * @return Reference to the group
     */
    OrbitalGroup &getOrCreateGroup(const std::string &groupName)
    {
        if (groups.find(groupName) == groups.end())
        {
            groups[groupName] = OrbitalGroup(groupName);
        }
        return groups[groupName];
    }

    /**
     * @brief Set group parameters
     *
     * @param groupName Group name
     * @param timeScale Time scaling factor
     * @param centerPoint Center point for group
     * @param synchronized Whether group should be synchronized
     */
    void setGroupParams(const std::string &groupName,
                        float timeScale = 1.0f,
                        const Math::float3 &centerPoint = {0, 0, 0},
                        bool synchronized = true)
    {
        auto &group = getOrCreateGroup(groupName);
        group.timeScale = timeScale;
        group.centerPoint = centerPoint;
        group.synchronized = synchronized;
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
     * @brief Pause/resume orbital animations
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
     * @brief Reset global time
     *
     * @param time New time value
     */
    void setGlobalTime(float time)
    {
        globalTime = time;

        // Update all orbital components
        for (auto &entity : entities)
        {
            if (entity.orbital)
            {
                entity.orbital->setTime(time);
            }
        }
    }

    /**
     * @brief Get current global time
     *
     * @return Current global time
     */
    float getGlobalTime() const
    {
        return globalTime;
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
     * @brief Update a single orbital entity
     *
     * @param entity Entity to update
     */
    void updateEntity(OrbitalEntity &entity)
    {
        // Find the group this entity belongs to
        OrbitalGroup *entityGroup = nullptr;
        for (auto &[groupName, group] : groups)
        {
            auto it = std::find(group.entityIds.begin(), group.entityIds.end(), entity.entityId);
            if (it != group.entityIds.end())
            {
                entityGroup = &group;
                break;
            }
        }

        // Calculate time delta for this entity
        float entityDelta = deltaTime;
        if (entityGroup)
        {
            entityDelta *= entityGroup->timeScale;
        }

        // Update orbital component
        entity.orbital->update(entityDelta);

        // Get current orbital position and orientation
        Math::float3 position = entity.orbital->getCurrentPosition();
        Math::quat orientation = entity.orbital->getCurrentOrientation();

        // Apply group center offset if applicable
        if (entityGroup)
        {
            position = Math::add(position, entityGroup->centerPoint);
        }

        // Update transform component
        entity.transform->setPosition(position);
        entity.transform->setRotation(orientation);
    }

    /**
     * @brief Update group-specific animations
     */
    void updateGroups()
    {
        for (auto &[groupName, group] : groups)
        {
            if (!group.synchronized)
                continue;

            // For synchronized groups, ensure all entities have the same phase
            if (group.entityIds.size() > 1)
            {
                updateSynchronizedGroup(group);
            }
        }
    }

    /**
     * @brief Update a synchronized orbital group
     *
     * @param group Group to synchronize
     */
    void updateSynchronizedGroup(OrbitalGroup &group)
    {
        if (group.entityIds.empty())
            return;

        // Find the first active entity as reference
        OrbitalEntity *referenceEntity = nullptr;
        for (uint32_t entityId : group.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.orbital)
                {
                    referenceEntity = &entity;
                    break;
                }
            }
            if (referenceEntity)
                break;
        }

        if (!referenceEntity)
            return;

        // Get reference time from the reference entity
        float referenceTime = globalTime + group.phaseOffset;

        // Apply to all entities in the group
        for (uint32_t entityId : group.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.orbital)
                {
                    // Maintain individual phase offsets while synchronizing base time
                    float individualPhase = entity.orbital->orbitParams.phaseOffset;
                    entity.orbital->setTime(referenceTime + individualPhase);
                }
            }
        }
    }
};

