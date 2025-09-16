#pragma once
#include "../components/EntityBehavior.h"
#include "../factory/BehaviorRegistry.h"
#include "../assets/Package.h"
#include "../core/Entity.h"
#include <vector>
#include <memory>
#include <unordered_map>

namespace Systems {

/**
 * System responsible for managing and updating all entity behaviors.
 * Integrates with the package system to create behaviors from XML definitions.
 */
class BehaviorSystem {
public:
    BehaviorSystem();
    ~BehaviorSystem();
    
    /**
     * Initialize the behavior system
     */
    void initialize();
    
    /**
     * Shutdown the behavior system and cleanup all behaviors
     */
    void shutdown();
    
    /**
     * Update all active behaviors
     * @param deltaTime Time elapsed since last frame in seconds
     */
    void update(float deltaTime);
    
    /**
     * Create and attach a behavior to an entity from package definition
     * @param entity The entity to attach the behavior to
     * @param behaviorName Name of the behavior class
     * @param params Parameters from the package XML
     * @return True if behavior was successfully created and attached
     */
    bool attachBehavior(Core::Entity& entity, const std::string& behaviorName, 
                       const Assets::BehaviorParams& params);
    
    /**
     * Remove all behaviors from an entity
     * @param entityId ID of the entity to remove behaviors from
     */
    void removeBehaviors(Core::EntityId entityId);
    
    /**
     * Remove a specific behavior from an entity
     * @param entityId ID of the entity
     * @param behaviorName Name of the behavior to remove
     */
    void removeBehavior(Core::EntityId entityId, const std::string& behaviorName);
    
    /**
     * Get all behaviors attached to an entity
     * @param entityId ID of the entity
     * @return Vector of behavior pointers (empty if entity has no behaviors)
     */
    std::vector<Components::EntityBehavior*> getBehaviors(Core::EntityId entityId) const;
    
    /**
     * Get a specific behavior from an entity
     * @param entityId ID of the entity
     * @param behaviorName Name of the behavior
     * @return Pointer to the behavior, or nullptr if not found
     */
    Components::EntityBehavior* getBehavior(Core::EntityId entityId, const std::string& behaviorName) const;
    
    /**
     * Check if an entity has any behaviors
     * @param entityId ID of the entity
     * @return True if the entity has at least one behavior
     */
    bool hasBehaviors(Core::EntityId entityId) const;
    
    /**
     * Get the total number of active behaviors in the system
     */
    size_t getBehaviorCount() const;
    
    /**
     * Create behaviors for all entities defined in a package scene
     * @param package The package containing the scene definition
     * @param sceneName Name of the scene to process
     * @param entities Map of entity names to entity objects
     * @return Number of behaviors successfully created
     */
    size_t createSceneBehaviors(const Assets::Package& package, const std::string& sceneName,
                               const std::unordered_map<std::string, Core::Entity*>& entities);
    
private:
    struct BehaviorInstance {
        std::unique_ptr<Components::EntityBehavior> behavior;
        std::string behaviorName;
        Core::EntityId entityId;
    };
    
    // Map from entity ID to list of behaviors
    std::unordered_map<Core::EntityId, std::vector<std::unique_ptr<BehaviorInstance>>> entityBehaviors;
    
    // Registry for creating behaviors
    Factory::BehaviorRegistry& behaviorRegistry;
    
    bool isInitialized = false;
    
    /**
     * Helper method to find a behavior instance
     */
    BehaviorInstance* findBehaviorInstance(Core::EntityId entityId, const std::string& behaviorName) const;
};

} // namespace Systems
