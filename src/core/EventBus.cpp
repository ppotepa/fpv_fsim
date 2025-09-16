#include "EventBus.h"
#include "debug.h"
#define DEBUG

#ifdef DEBUG
#pragma message("DEBUG is defined")
#else
#pragma message("DEBUG is not defined")
#endif

/**
 * @brief Construct an empty event bus.
 *
 * Initializes the event bus with no registered handlers.
 */
EventBus::EventBus()
{
    DEBUG_LOG("Creating EventBus");
}

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
    DEBUG_LOG("Subscribing handler for event type " + std::to_string(static_cast<int>(type)));
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
    DEBUG_LOG("Publishing event of type " + std::to_string(static_cast<int>(event.getType())));
    auto it = handlers_.find(event.getType());
    if (it != handlers_.end())
    {
        DEBUG_LOG("Found " + std::to_string(it->second.size()) + " handlers for event type " + std::to_string(static_cast<int>(event.getType())));
        for (auto &handler : it->second)
        {
            handler(event);
        }
    }
    else
    {
        DEBUG_LOG("No handlers found for event type " + std::to_string(static_cast<int>(event.getType())));
    }
}

