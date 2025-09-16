#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>
#include <vector>

namespace Core {

/**
 * Simple IoC (Inversion of Control) container for dependency injection.
 * Supports singleton and transient lifetimes, and integration with the package system.
 */
class IoContainer {
public:
    enum class Lifetime {
        Singleton,  // One instance for the entire application
        Transient   // New instance each time
    };
    
    /**
     * Factory function type for creating instances
     */
    template<typename T>
    using Factory = std::function<std::unique_ptr<T>()>;
    
    IoContainer();
    ~IoContainer();
    
    /**
     * Register a type with a factory function
     * @param factory Function that creates instances of T
     * @param lifetime Lifetime management for the type
     * @param name Optional name for named registrations
     */
    template<typename TInterface, typename TImplementation>
    void register_(Factory<TInterface> factory, Lifetime lifetime = Lifetime::Singleton, 
                  const std::string& name = "");
    
    /**
     * Register a type with automatic factory creation
     * @param lifetime Lifetime management for the type
     * @param name Optional name for named registrations
     */
    template<typename TInterface, typename TImplementation>
    void register_(Lifetime lifetime = Lifetime::Singleton, const std::string& name = "");
    
    /**
     * Register an existing instance (always singleton)
     * @param instance Existing instance to register
     * @param name Optional name for named registrations
     */
    template<typename TInterface>
    void registerInstance(std::shared_ptr<TInterface> instance, const std::string& name = "");
    
    /**
     * Resolve a dependency by type
     * @param name Optional name for named resolution
     * @return Shared pointer to the resolved instance
     */
    template<typename T>
    std::shared_ptr<T> resolve(const std::string& name = "");
    
    /**
     * Check if a type is registered
     * @param name Optional name for named check
     * @return True if the type is registered
     */
    template<typename T>
    bool isRegistered(const std::string& name = "") const;
    
    /**
     * Unregister a type
     * @param name Optional name for named unregistration
     */
    template<typename T>
    void unregister(const std::string& name = "");
    
    /**
     * Clear all registrations
     */
    void clear();
    
    /**
     * Create a child container for scoped dependencies (e.g., package-specific services)
     * Child containers can resolve from parent but registrations don't affect parent
     */
    std::unique_ptr<IoContainer> createChild();
    
    /**
     * Get all registered type names for debugging
     */
    std::vector<std::string> getRegisteredTypes() const;
    
private:
    struct Registration {
        std::function<std::shared_ptr<void>()> factory;
        Lifetime lifetime;
        std::shared_ptr<void> singletonInstance;
        std::type_index typeIndex;
        std::string typeName;
        
        Registration(std::function<std::shared_ptr<void>()> f, Lifetime lt, 
                    std::type_index ti, const std::string& tn)
            : factory(std::move(f)), lifetime(lt), typeIndex(ti), typeName(tn) {}
    };
    
    std::unordered_map<std::string, Registration> registrations;
    IoContainer* parent = nullptr;
    
    /**
     * Get registration key for type and name
     */
    template<typename T>
    std::string getKey(const std::string& name = "") const;
    
    /**
     * Constructor for child containers
     */
    IoContainer(IoContainer* parentContainer);
    
    /**
     * Find registration, checking parent if not found locally
     */
    Registration* findRegistration(const std::string& key);
};

// Template implementations
template<typename TInterface, typename TImplementation>
void IoContainer::register_(Factory<TInterface> factory, Lifetime lifetime, const std::string& name) {
    std::string key = getKey<TInterface>(name);
    
    // Wrap the typed factory in a void* factory
    auto voidFactory = [factory]() -> std::shared_ptr<void> {
        return std::static_pointer_cast<void>(factory());
    };
    
    registrations.emplace(key, Registration(
        std::move(voidFactory), 
        lifetime, 
        std::type_index(typeid(TInterface)),
        typeid(TInterface).name()
    ));
}

template<typename TInterface, typename TImplementation>
void IoContainer::register_(Lifetime lifetime, const std::string& name) {
    auto factory = []() -> std::unique_ptr<TInterface> {
        return std::make_unique<TImplementation>();
    };
    register_<TInterface, TImplementation>(std::move(factory), lifetime, name);
}

template<typename TInterface>
void IoContainer::registerInstance(std::shared_ptr<TInterface> instance, const std::string& name) {
    std::string key = getKey<TInterface>(name);
    
    auto factory = [instance]() -> std::shared_ptr<void> {
        return std::static_pointer_cast<void>(instance);
    };
    
    Registration reg(std::move(factory), Lifetime::Singleton, 
                    std::type_index(typeid(TInterface)), typeid(TInterface).name());
    reg.singletonInstance = std::static_pointer_cast<void>(instance);
    
    registrations.emplace(key, std::move(reg));
}

template<typename T>
std::shared_ptr<T> IoContainer::resolve(const std::string& name) {
    std::string key = getKey<T>(name);
    
    Registration* reg = findRegistration(key);
    if (!reg) {
        return nullptr;
    }
    
    if (reg->lifetime == Lifetime::Singleton) {
        if (!reg->singletonInstance) {
            reg->singletonInstance = reg->factory();
        }
        return std::static_pointer_cast<T>(reg->singletonInstance);
    } else {
        return std::static_pointer_cast<T>(reg->factory());
    }
}

template<typename T>
bool IoContainer::isRegistered(const std::string& name) const {
    std::string key = getKey<T>(name);
    return registrations.find(key) != registrations.end() ||
           (parent && parent->isRegistered<T>(name));
}

template<typename T>
void IoContainer::unregister(const std::string& name) {
    std::string key = getKey<T>(name);
    registrations.erase(key);
}

template<typename T>
std::string IoContainer::getKey(const std::string& name) const {
    std::string key = typeid(T).name();
    if (!name.empty()) {
        key += ":" + name;
    }
    return key;
}

} // namespace Core
