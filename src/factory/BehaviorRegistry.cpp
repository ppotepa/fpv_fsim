#include "../components/EntityBehavior.h"
#include "BehaviorRegistry.h"
#include <stdexcept>

namespace Factory
{

    BehaviorRegistry &BehaviorRegistry::instance()
    {
        static BehaviorRegistry instance;
        return instance;
    }

    BehaviorRegistry::~BehaviorRegistry() = default;

    void BehaviorRegistry::registerBehavior(const std::string &behaviorName, BehaviorFactory factory)
    {
        if (behaviorName.empty())
        {
            throw std::invalid_argument("Behavior name cannot be empty");
        }

        if (!factory)
        {
            throw std::invalid_argument("Behavior factory cannot be null");
        }

        behaviors[behaviorName] = std::move(factory);
    }

    std::unique_ptr<Components::EntityBehavior> BehaviorRegistry::createBehavior(const std::string &behaviorName) const
    {
        auto it = behaviors.find(behaviorName);
        if (it != behaviors.end())
        {
            return it->second();
        }
        return nullptr;
    }

    bool BehaviorRegistry::isBehaviorRegistered(const std::string &behaviorName) const
    {
        return behaviors.find(behaviorName) != behaviors.end();
    }

    std::vector<std::string> BehaviorRegistry::getRegisteredBehaviors() const
    {
        std::vector<std::string> names;
        names.reserve(behaviors.size());

        for (const auto &[name, factory] : behaviors)
        {
            names.push_back(name);
        }

        return names;
    }

    void BehaviorRegistry::unregisterBehavior(const std::string &behaviorName)
    {
        behaviors.erase(behaviorName);
    }

    void BehaviorRegistry::clear()
    {
        behaviors.clear();
    }

} // namespace Factory
