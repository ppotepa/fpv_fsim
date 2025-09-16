#pragma once
#include "../core/Entity.h"
#include "../assets/Package.h"
#include <string>
#include <memory>

namespace Systems {
    class BehaviorSystem; // Forward declaration
}

namespace Components {

/**
 * Base class for entity behaviors.
 * Provides common functionality for entity behavior implementations.
 */
class EntityBehavior {
public:
    virtual ~EntityBehavior() = default;

    /**
     * Initialize the behavior
     * @param entity The entity this behavior is attached to
     * @param params Parameters for the behavior
     */
    virtual void initialize(Entity& entity, const Assets::BehaviorParams& params) = 0;

    /**
     * Update the behavior
     * @param deltaTime Time since last update
     */
    virtual void update(float deltaTime) = 0;

    /**
     * Cleanup when the behavior is removed
     */
    virtual void cleanup() {}

    /**
     * Get a parameter value with type conversion
     * @param name Parameter name
     * @param defaultValue Default value if parameter is not found
     * @return Parameter value or default
     */
    template <typename T>
    T getParameter(const std::string &name, const T &defaultValue = T{}) const
    {
        return params.get<T>(name, defaultValue);
    }

    void setEntity(Entity &e) { entity = &e; }
    void setParams(const Assets::BehaviorParams &p) { params = p; }

protected:
    Entity *entity = nullptr;
    Assets::BehaviorParams params;

private:
    friend class Systems::BehaviorSystem;
};

} // namespace Components
