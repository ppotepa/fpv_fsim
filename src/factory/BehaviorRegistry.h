#pragma once
#include "../components/EntityBehavior.h"
#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

namespace Factory
{

    /**
     * Registry for behavior classes that can be instantiated from package XML.
     * Uses factory pattern to create behavior instances by name.
     */
    class BehaviorRegistry
    {
    public:
        using BehaviorFactory = std::function<std::unique_ptr<Components::EntityBehavior>()>;

        /**
         * Get the singleton instance of the behavior registry
         */
        static BehaviorRegistry &instance();

        /**
         * Destructor
         */
        ~BehaviorRegistry();

        /**
         * Register a behavior factory function
         * @param behaviorName Name used in package XML codeBehind attribute
         * @param factory Function that creates instances of the behavior
         */
        void registerBehavior(const std::string &behaviorName, BehaviorFactory factory);

        /**
         * Create a behavior instance by name
         * @param behaviorName Name of the behavior to create
         * @return Unique pointer to the behavior, or nullptr if not found
         */
        std::unique_ptr<Components::EntityBehavior> createBehavior(const std::string &behaviorName) const;

        /**
         * Check if a behavior is registered
         * @param behaviorName Name of the behavior to check
         * @return True if the behavior is registered
         */
        bool isBehaviorRegistered(const std::string &behaviorName) const;

        /**
         * Get all registered behavior names
         * @return Vector of all registered behavior names
         */
        std::vector<std::string> getRegisteredBehaviors() const;

        /**
         * Unregister a behavior (useful for testing or dynamic loading)
         * @param behaviorName Name of the behavior to unregister
         */
        void unregisterBehavior(const std::string &behaviorName);

        /**
         * Clear all registered behaviors
         */
        void clear();

    private:
        BehaviorRegistry() = default;
        BehaviorRegistry(const BehaviorRegistry &) = delete;
        BehaviorRegistry &operator=(const BehaviorRegistry &) = delete;

        std::unordered_map<std::string, BehaviorFactory> behaviors;
    };

} // namespace Factory
