#ifndef ICOMPONENT_H
#define ICOMPONENT_H

/**
 * @brief Base interface for all components in the Entity Component System (ECS).
 *
 * Components are data structures that can be attached to entities to give them
 * specific properties or behaviors. This interface provides the basic contract
 * that all components must follow, primarily for proper memory management.
 */
class IComponent
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived components.
     *
     * This allows components to be properly deleted through base class pointers,
     * enabling polymorphic component management in the ECS.
     */
    virtual ~IComponent() = default;
};

#endif

