/**
 * @file CloudPrecessionSystem.h
 * @brief Animation system for voxel cloud orbital precession
 *
 * The CloudPrecessionSystem manages the complex orbital motion of
 * voxel cloud formations with precession and lifecycle management.
 * Features include:
 * - Dual orbital system management (primary + precession)
 * - Cloud lifecycle coordination (spawn, active, despawn)
 * - Hierarchical cloud organization
 * - Performance optimization for large cloud systems
 * - Integration with Math utilities for orbital calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/VoxelCloudC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>

/**
 * @brief Animation system for voxel cloud precession
 *
 * Manages complex orbital cloud formations with precession,
 * lifecycle management, and hierarchical organization.
 */
class CloudPrecessionSystem
{
public:
    /**
     * @brief Entity with cloud precession
     */
    struct CloudEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<VoxelCloudC> cloud;    /**< Voxel cloud component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */
        float spawnTime;                       /**< Time when cloud was spawned */

        CloudEntity(uint32_t id, std::shared_ptr<VoxelCloudC> cl, std::shared_ptr<TransformC> trans)
            : entityId(id), cloud(cl), transform(trans), active(true), spawnTime(0.0f) {}
    };

    /**
     * @brief Cloud formation for organized group behavior
     */
    struct CloudFormation
    {
        std::string name;                /**< Formation name */
        std::vector<uint32_t> entityIds; /**< Clouds in this formation */
        Math::float3 centerPoint;        /**< Formation center point */
        float formationRadius;           /**< Formation extent radius */
        float rotationSpeed;             /**< Formation rotation speed */
        float precessionSpeed;           /**< Formation precession speed */
        Math::float3 precessionAxis;     /**< Formation precession axis */
        bool synchronized;               /**< Whether formation is synchronized */

        CloudFormation(const std::string &formationName = "default")
            : name(formationName), centerPoint{0, 0, 0}, formationRadius(10.0f), rotationSpeed(0.1f), precessionSpeed(0.02f), precessionAxis{0, 1, 0}, synchronized(true)
        {
        }
    };

    /**
     * @brief Cloud spawning configuration
     */
    struct SpawnConfig
    {
        float spawnRate;          /**< Clouds per second */
        float spawnRadius;        /**< Spawn radius from center */
        float cloudLifetime;      /**< Individual cloud lifetime */
        uint32_t maxClouds;       /**< Maximum concurrent clouds */
        Math::float3 spawnCenter; /**< Center point for spawning */
        float randomOffset;       /**< Random position offset */

        SpawnConfig()
            : spawnRate(0.1f), spawnRadius(8.0f), cloudLifetime(60.0f), maxClouds(20), spawnCenter{0, 0, 0}, randomOffset(2.0f)
        {
        }
    };

    /**
     * @brief System performance statistics
     */
    struct PerformanceStats
    {
        uint32_t totalClouds;     /**< Total active clouds */
        uint32_t totalVoxels;     /**< Total active voxel elements */
        float updateTime;         /**< Last update time in milliseconds */
        uint32_t cloudsSpawned;   /**< Clouds spawned this frame */
        uint32_t cloudsDespawned; /**< Clouds despawned this frame */

        PerformanceStats() : totalClouds(0), totalVoxels(0), updateTime(0), cloudsSpawned(0), cloudsDespawned(0) {}
    };

private:
    /** @brief All registered cloud entities */
    std::vector<CloudEntity> entities;

    /** @brief Cloud formations for organized behavior */
    std::unordered_map<std::string, CloudFormation> formations;

    /** @brief Spawn configuration */
    SpawnConfig spawnConfig;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Performance statistics */
    PerformanceStats stats;

    /** @brief Spawn timer accumulator */
    float spawnTimer;

    /** @brief Global center point for orbital motion */
    Math::float3 globalCenter;

    /** @brief Random state for procedural generation */
    uint32_t randomState;

    /** @brief Queue of entities to be removed */
    std::queue<uint32_t> removalQueue;

public:
    /**
     * @brief Construct a new CloudPrecessionSystem
     *
     * @param center Global center point for cloud motion
     */
    CloudPrecessionSystem(const Math::float3 &center = {0, 0, 0})
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), spawnTimer(0.0f), globalCenter(center), randomState(12345)
    {
        // Create default formation
        formations["default"] = CloudFormation("default");
    }

    /**
     * @brief Update all cloud animations
     *
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime)
    {
        if (!systemActive)
            return;

        // Reset frame statistics
        stats.cloudsSpawned = 0;
        stats.cloudsDespawned = 0;
        stats.totalClouds = 0;
        stats.totalVoxels = 0;

        float startTime = globalTime; // For performance measurement

        float scaledDeltaTime = deltaTime * globalTimeScale;
        globalTime += scaledDeltaTime;
        spawnTimer += scaledDeltaTime;

        // Update all cloud entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.cloud || !entity.transform)
                continue;

            updateCloudEntity(entity, scaledDeltaTime);
            stats.totalClouds++;
        }

        // Update formations
        updateFormations(scaledDeltaTime);

        // Handle spawning
        updateSpawning();

        // Handle removal of despawned clouds
        updateRemoval();

        // Calculate performance metrics
        stats.updateTime = (globalTime - startTime) * 1000.0f; // Convert to milliseconds
    }

    /**
     * @brief Register an entity for cloud animation
     *
     * @param entityId Entity identifier
     * @param cloud Voxel cloud component
     * @param transform Transform component
     * @param formationName Formation to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<VoxelCloudC> cloud,
                        std::shared_ptr<TransformC> transform,
                        const std::string &formationName = "default")
    {
        entities.emplace_back(entityId, cloud, transform);
        entities.back().spawnTime = globalTime;

        // Add to formation
        auto &formation = getOrCreateFormation(formationName);
        formation.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from cloud animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const CloudEntity &e)
                           { return e.entityId == entityId; }),
            entities.end());

        // Remove from all formations
        for (auto &[formationName, formation] : formations)
        {
            formation.entityIds.erase(
                std::remove(formation.entityIds.begin(), formation.entityIds.end(), entityId),
                formation.entityIds.end());
        }
    }

    /**
     * @brief Create or get a cloud formation
     *
     * @param formationName Name of the formation
     * @return Reference to the formation
     */
    CloudFormation &getOrCreateFormation(const std::string &formationName)
    {
        if (formations.find(formationName) == formations.end())
        {
            formations[formationName] = CloudFormation(formationName);
        }
        return formations[formationName];
    }

    /**
     * @brief Set formation parameters
     *
     * @param formationName Formation name
     * @param centerPoint Formation center
     * @param radius Formation radius
     * @param rotationSpeed Formation rotation speed
     * @param precessionSpeed Formation precession speed
     */
    void setFormationParams(const std::string &formationName,
                            const Math::float3 &centerPoint = {0, 0, 0},
                            float radius = 10.0f,
                            float rotationSpeed = 0.1f,
                            float precessionSpeed = 0.02f)
    {
        auto &formation = getOrCreateFormation(formationName);
        formation.centerPoint = centerPoint;
        formation.formationRadius = radius;
        formation.rotationSpeed = rotationSpeed;
        formation.precessionSpeed = precessionSpeed;
    }

    /**
     * @brief Set spawn configuration
     *
     * @param config New spawn configuration
     */
    void setSpawnConfig(const SpawnConfig &config)
    {
        spawnConfig = config;
    }

    /**
     * @brief Get current spawn configuration
     *
     * @return Current spawn config
     */
    const SpawnConfig &getSpawnConfig() const
    {
        return spawnConfig;
    }

    /**
     * @brief Set global center point
     *
     * @param center New global center
     */
    void setGlobalCenter(const Math::float3 &center)
    {
        globalCenter = center;
    }

    /**
     * @brief Get global center point
     *
     * @return Current global center
     */
    const Math::float3 &getGlobalCenter() const
    {
        return globalCenter;
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
     * @brief Pause/resume cloud animations
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
     * @brief Update a single cloud entity
     *
     * @param entity Entity to update
     * @param deltaTime Time delta for this update
     */
    void updateCloudEntity(CloudEntity &entity, float deltaTime)
    {
        // Update cloud component with global center
        entity.cloud->update(deltaTime, globalCenter);

        // Get current world position and orientation from cloud
        Math::float3 position = entity.cloud->getWorldPosition();
        Math::quat orientation = entity.cloud->getWorldOrientation();

        // Update transform component
        entity.transform->setPosition(position);
        entity.transform->setRotation(orientation);

        // Count voxel elements for statistics
        auto elements = entity.cloud->getActiveElements();
        stats.totalVoxels += elements.size();

        // Check if cloud should be despawned
        if (entity.cloud->shouldDestroy())
        {
            removalQueue.push(entity.entityId);
            stats.cloudsDespawned++;
        }
    }

    /**
     * @brief Update all formations
     *
     * @param deltaTime Time delta for this update
     */
    void updateFormations(float deltaTime)
    {
        for (auto &[formationName, formation] : formations)
        {
            updateFormation(formation, deltaTime);
        }
    }

    /**
     * @brief Update a specific cloud formation
     *
     * @param formation Formation to update
     * @param deltaTime Time delta for this update
     */
    void updateFormation(CloudFormation &formation, float deltaTime)
    {
        if (!formation.synchronized || formation.entityIds.empty())
            return;

        // Calculate formation-level transformations
        float rotationAngle = globalTime * formation.rotationSpeed;
        float precessionAngle = globalTime * formation.precessionSpeed;

        // Apply formation-level effects to member clouds
        for (uint32_t entityId : formation.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.cloud)
                {
                    applyFormationEffects(entity, formation, rotationAngle, precessionAngle);
                }
            }
        }
    }

    /**
     * @brief Apply formation-level effects to a cloud entity
     *
     * @param entity Cloud entity to affect
     * @param formation Formation parameters
     * @param rotationAngle Current formation rotation
     * @param precessionAngle Current formation precession
     */
    void applyFormationEffects(CloudEntity &entity,
                               const CloudFormation &formation,
                               float rotationAngle,
                               float precessionAngle)
    {
        // Apply formation-level orbital modifications
        auto params = entity.cloud->getParams();

        // Modify primary orbit based on formation
        params.primaryOrbit.phaseOffset += rotationAngle * 0.1f;

        // Modify precession based on formation precession
        params.precessionOrbit.phaseOffset += precessionAngle;

        entity.cloud->setParams(params);
    }

    /**
     * @brief Update cloud spawning
     */
    void updateSpawning()
    {
        if (spawnConfig.spawnRate <= 0.0f)
            return;
        if (getActiveEntityCount() >= spawnConfig.maxClouds)
            return;

        float spawnInterval = 1.0f / spawnConfig.spawnRate;
        while (spawnTimer >= spawnInterval)
        {
            spawnNewCloud();
            spawnTimer -= spawnInterval;
            stats.cloudsSpawned++;
        }
    }

    /**
     * @brief Spawn a new cloud entity
     */
    void spawnNewCloud()
    {
        // Generate random spawn position
        float angle = 2.0f * Math::Pi * Math::rand01(randomState);
        float radius = spawnConfig.spawnRadius * Math::rand01(randomState);

        Math::float3 spawnPos = {
            spawnConfig.spawnCenter.x + radius * std::cos(angle),
            spawnConfig.spawnCenter.y + (Math::rand01(randomState) - 0.5f) * spawnConfig.randomOffset,
            spawnConfig.spawnCenter.z + radius * std::sin(angle)};

        // Create new cloud component with random parameters
        auto cloud = std::make_shared<VoxelCloudC>(spawnConfig.cloudLifetime, randomState);
        auto transform = std::make_shared<TransformC>();

        // Set initial transform
        transform->setPosition(spawnPos);

        // Generate unique entity ID
        uint32_t newEntityId = static_cast<uint32_t>(entities.size()) + 1000;

        // Register the new entity
        registerEntity(newEntityId, cloud, transform, "default");
    }

    /**
     * @brief Update removal of despawned clouds
     */
    void updateRemoval()
    {
        while (!removalQueue.empty())
        {
            uint32_t entityId = removalQueue.front();
            removalQueue.pop();
            unregisterEntity(entityId);
        }
    }
};

