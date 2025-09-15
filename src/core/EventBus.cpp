#include "EventBus.h"

/**
 * @brief Construct an empty event bus.
 *
 * Initializes the event bus with no registered handlers.
 */
EventBus::EventBus() {}

/**
 * @brief Subscribe a handler function to a specific event type.
 *
 * Adds the handler to the list of functions that will be called when
 * events of the specified type are published. If this is the first
 * handler for this event type, a new entry is created in the handlers map.
 *
 * @param type The event type to subscribe to
 * @param handler Function to call when events of this type are published
 */
void EventBus::subscribe(EventType type, std::function<void(const IEvent &)> handler)
{
    handlers_[type].push_back(handler);
}

/**
 * @brief Publish an event to all subscribed handlers.
 *
 * Looks up all handlers registered for the event's type and calls each
 * one with a reference to the event. If no handlers are registered for
 * this event type, the function returns without doing anything.
 *
 * @param event The event to publish
 */
void EventBus::publish(const IEvent &event)
{
    auto it = handlers_.find(event.getType());
    if (it != handlers_.end())
    {
        for (auto &handler : it->second)
        {
            handler(event);
        }
    }
}
