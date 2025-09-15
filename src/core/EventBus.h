#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "IEvent.h"
#include <functional>
#include <unordered_map>
#include <vector>

/**
 * @brief Central event management system for inter-system communication.
 *
 * The EventBus implements a publish-subscribe pattern where systems can
 * subscribe to specific event types and receive notifications when those
 * events are published. This enables decoupled communication between
 * different parts of the simulation.
 */
class EventBus
{
public:
    /**
     * @brief Construct an empty event bus.
     */
    EventBus();

    /**
     * @brief Subscribe a handler function to a specific event type.
     *
     * Multiple handlers can subscribe to the same event type. When an
     * event of that type is published, all subscribed handlers will be called.
     *
     * @param type The event type to subscribe to
     * @param handler Function to call when events of this type are published
     */
    void subscribe(EventType type, std::function<void(const IEvent &)> handler);

    /**
     * @brief Publish an event to all subscribed handlers.
     *
     * All handlers subscribed to the event's type will be called with
     * a reference to the event object.
     *
     * @param event The event to publish
     */
    void publish(const IEvent &event);

private:
    /** Map of event types to lists of handler functions */
    std::unordered_map<EventType, std::vector<std::function<void(const IEvent &)>>> handlers_;
};

#endif
