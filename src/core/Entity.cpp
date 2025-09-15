#include "Entity.h"

Entity::Entity(unsigned int id) : id_(id) {}

template <typename T>
void Entity::addComponent(std::unique_ptr<T> component)
{
    components_[std::type_index(typeid(T))] = std::move(component);
}

template <typename T>
T *Entity::getComponent()
{
    auto it = components_.find(std::type_index(typeid(T)));
    if (it != components_.end())
    {
        return static_cast<T *>(it->second.get());
    }
    return nullptr;
}
