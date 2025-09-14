#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.h"
#include &lt; memory & gt;
#include &lt; unordered_map & gt;
#include &lt; typeindex & gt;

class Entity
{
public:
    Entity(unsigned int id);
    template &lt;
    typename T &gt;
    void addComponent(std::unique_ptr &lt; T & gt; component);
    template &lt;
    typename T &gt;
    T *getComponent();

private:
    unsigned int id_;
    std::unordered_map &lt;
    std::type_index, std::unique_ptr &lt;
    IComponent &gt;
    &gt;
    components_;
};

#endif
