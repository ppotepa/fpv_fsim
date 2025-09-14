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
    void addComponent(std::unique_ptr<T> component);
    template <typename T>
    T *getComponent();

private:
    unsigned int id_;
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components_;
};

#endif
