#pragma once
#include "../core/Entity.h"
#include "../assets/Package.h"
#include <string>
#include <memory>
#include <unordered_map>

namespace Components {

/**
 * Abstract base class for all entity behaviors.
 * Behaviors implement custom logic that can be attached to entities
 * through the package system's codeBehind mechanism.
 */
class EntityBehavior {
public:
    virtual ~EntityBehavior() = default;
    
    /**
     * Initialize the behavior with the entity and parameters from XML
     * @param entity The entity this behavior is attached to
     * @param params Parameters from the package XML definition
     */
    virtual void initialize(Core::Entity& entity, const Assets::BehaviorParams& params) = 0;
    
    /**
     * Called once per frame to update the behavior
     * @param deltaTime Time elapsed since last frame in seconds
     */
    virtual void update(float deltaTime) = 0;
    
    /**
     * Called when the behavior is being destroyed
     * Use this for cleanup operations
     */
    virtual void cleanup() {}
    
    /**
     * Get the entity this behavior is attached to
     */
    Core::Entity& getEntity() { return *entity; }
    const Core::Entity& getEntity() const { return *entity; }
    
    /**
     * Get the behavior parameters
     */
    const Assets::BehaviorParams& getParams() const { return params; }
    
protected:
    /**
     * Helper method to get a parameter value with type checking
     * @param name Parameter name
     * @param defaultValue Default value if parameter is not found
     * @return Parameter value or default
     */
    template<typename T>
    T getParameter(const std::string& name, const T& defaultValue = T{}) const {
        return params.getParameter<T>(name, defaultValue);
    }
    
private:
    friend class BehaviorSystem;
    Core::Entity* entity = nullptr;
    Assets::BehaviorParams params;
    
    void setEntity(Core::Entity& e) { entity = &e; }
    void setParams(const Assets::BehaviorParams& p) { params = p; }
};

/**
 * Macro to register a behavior class with the behavior system
 * Usage: REGISTER_BEHAVIOR(MyBehavior, "MyBehavior")
 */
#define REGISTER_BEHAVIOR(BehaviorClass, BehaviorName) \
    namespace { \
        static bool registered_##BehaviorClass = []() { \
            Factory::BehaviorRegistry::instance().registerBehavior( \
                BehaviorName, \
                []() -> std::unique_ptr<EntityBehavior> { \
                    return std::make_unique<BehaviorClass>(); \
                } \
            ); \
            return true; \
        }(); \
    }

} // namespace Components
