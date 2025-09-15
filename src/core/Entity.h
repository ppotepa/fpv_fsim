#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.h"
#include <memory>
#include <unordered_map>
#include <typeindex>

class Entity
{
public:
    Entity(unsigned int id);
    template <typename T>
    void addComponent(std::unique_ptr<T> component)
    {
        components_[std::type_index(typeid(T))] = std::move(component);
    }
    template <typename T>
    T *getComponent()
    {
        auto it = components_.find(std::type_index(typeid(T)));
        if (it != components_.end())
        {
            return static_cast<T *>(it->second.get());
        }
        return nullptr;
    }

private:
    unsigned int id_;
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components_;
};

#endif
