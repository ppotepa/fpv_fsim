#include "../components/EntityBehavior.h"
#include "BehaviorSystem.h"
#include "../factory/BehaviorRegistry.h"
#include <algorithm>
#include <stdexcept>

namespace Systems
{

    BehaviorSystem::BehaviorSystem()
        : behaviorRegistry(Factory::BehaviorRegistry::instance())
    {
    }

    BehaviorSystem::~BehaviorSystem()
    {
        if (isInitialized)
        {
            shutdown();
        }
    }

    void BehaviorSystem::initialize()
    {
        if (isInitialized)
        {
            return;
        }

        entityBehaviors.clear();
        isInitialized = true;
    }

    void BehaviorSystem::shutdown()
    {
        if (!isInitialized)
        {
            return;
        }

        // Cleanup all behaviors
        for (auto &[entityId, behaviors] : entityBehaviors)
        {
            for (auto &behaviorInstance : behaviors)
            {
                if (behaviorInstance->behavior)
                {
                    behaviorInstance->behavior->cleanup();
                }
            }
        }

        entityBehaviors.clear();
        isInitialized = false;
    }

    void BehaviorSystem::update(float deltaTime)
    {
        if (!isInitialized)
        {
            return;
        }

        // Update all behaviors
        for (auto &[entityId, behaviors] : entityBehaviors)
        {
            for (auto &behaviorInstance : behaviors)
            {
                if (behaviorInstance->behavior)
                {
                    try
                    {
                        behaviorInstance->behavior->update(deltaTime);
                    }
                    catch (const std::exception &e)
                    {
                        // Log error but continue updating other behaviors
                        // In a real implementation, this would use the logging system
                        // LogError("Behavior update failed for entity {}: {}", entityId, e.what());
                    }
                }
            }
        }
    }

    bool BehaviorSystem::attachBehavior(Entity &entity, const std::string &behaviorName,
                                        const Assets::BehaviorParams &params)
    {
        if (!isInitialized)
        {
            return false;
        }

        // Create the behavior instance
        auto behavior = behaviorRegistry.createBehavior(behaviorName);
        if (!behavior)
        {
            return false;
        }

        // Initialize the behavior
        try
        {
            behavior->setEntity(entity);
            behavior->setParams(params);
            behavior->initialize(entity, params);
        }
        catch (const std::exception &e)
        {
            // Initialization failed
            return false;
        }

        // Create behavior instance wrapper
        auto instance = std::make_unique<BehaviorInstance>();
        instance->behavior = std::move(behavior);
        instance->behaviorName = behaviorName;
        instance->entityId = entity.getId();

        // Add to entity's behavior list
        entityBehaviors[entity.getId()].push_back(std::move(instance));

        return true;
    }

    void BehaviorSystem::removeBehaviors(unsigned int entityId)
    {
        auto it = entityBehaviors.find(entityId);
        if (it != entityBehaviors.end())
        {
            // Cleanup behaviors before removal
            for (auto &behaviorInstance : it->second)
            {
                if (behaviorInstance->behavior)
                {
                    behaviorInstance->behavior->cleanup();
                }
            }
            entityBehaviors.erase(it);
        }
    }

    void BehaviorSystem::removeBehavior(unsigned int entityId, const std::string &behaviorName)
    {
        auto it = entityBehaviors.find(entityId);
        if (it != entityBehaviors.end())
        {
            auto &behaviors = it->second;

            auto behaviorIt = std::remove_if(behaviors.begin(), behaviors.end(),
                                             [&behaviorName](const std::unique_ptr<BehaviorInstance> &instance)
                                             {
                                                 if (instance->behaviorName == behaviorName)
                                                 {
                                                     if (instance->behavior)
                                                     {
                                                         instance->behavior->cleanup();
                                                     }
                                                     return true;
                                                 }
                                                 return false;
                                             });

            behaviors.erase(behaviorIt, behaviors.end());

            // Remove entity entry if no behaviors remain
            if (behaviors.empty())
            {
                entityBehaviors.erase(it);
            }
        }
    }

    std::vector<Components::EntityBehavior *> BehaviorSystem::getBehaviors(unsigned int entityId) const
    {
        std::vector<Components::EntityBehavior *> result;

        auto it = entityBehaviors.find(entityId);
        if (it != entityBehaviors.end())
        {
            result.reserve(it->second.size());
            for (const auto &instance : it->second)
            {
                if (instance->behavior)
                {
                    result.push_back(instance->behavior.get());
                }
            }
        }

        return result;
    }

    Components::EntityBehavior *BehaviorSystem::getBehavior(unsigned int entityId,
                                                            const std::string &behaviorName) const
    {
        auto instance = findBehaviorInstance(entityId, behaviorName);
        return instance ? instance->behavior.get() : nullptr;
    }

    bool BehaviorSystem::hasBehaviors(unsigned int entityId) const
    {
        auto it = entityBehaviors.find(entityId);
        return it != entityBehaviors.end() && !it->second.empty();
    }

    size_t BehaviorSystem::getBehaviorCount() const
    {
        size_t count = 0;
        for (const auto &[entityId, behaviors] : entityBehaviors)
        {
            count += behaviors.size();
        }
        return count;
    }

    size_t BehaviorSystem::createSceneBehaviors(const Assets::Package &package, const std::string &sceneName,
                                                const std::unordered_map<std::string, Entity *> &entities)
    {
        if (!isInitialized)
        {
            return 0;
        }

        size_t behaviorCount = 0;

        // Find the scene in the package
        const auto *scene = package.findScene(sceneName);
        if (!scene)
        {
            return 0;
        }

        // Process each entity in the scene
        for (const auto &entityDef : scene->entities)
        {
            // Find the corresponding entity object
            auto entityIt = entities.find(entityDef.id);
            if (entityIt == entities.end())
            {
                continue;
            }

            Entity *entity = entityIt->second;
            if (!entity)
            {
                continue;
            }

            // Create behavior for this entity if it has a behavior class
            if (!entityDef.behaviorClass.empty())
            {
                if (attachBehavior(*entity, entityDef.behaviorClass, entityDef.behaviorParams))
                {
                    behaviorCount++;
                }
            }
        }

        return behaviorCount;
    }

    BehaviorSystem::BehaviorInstance *BehaviorSystem::findBehaviorInstance(unsigned int entityId,
                                                                           const std::string &behaviorName) const
    {
        auto it = entityBehaviors.find(entityId);
        if (it != entityBehaviors.end())
        {
            for (const auto &instance : it->second)
            {
                if (instance->behaviorName == behaviorName)
                {
                    return instance.get();
                }
            }
        }
        return nullptr;
    }

} // namespace Systems
