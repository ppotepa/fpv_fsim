#ifndef IEVENT_H
#define IEVENT_H

/**
 * @brief Enumeration of all possible event types in the simulation.
 *
 * Event types are used to categorize different kinds of events that can occur
 * during simulation execution, enabling systems to subscribe to specific event types.
 */
enum class EventType
{
    BatteryLow,               /**< Low battery warning event */
    Collision,                /**< Collision detection event */
    ConsoleToggle,            /**< Console visibility toggle event */
    ConsoleVisibilityChanged, /**< Console visibility state change event */
    NoPackagesFound,          /**< No asset packages found during bootstrap */
    DefaultWorldGenerated,    /**< Default world generation completed */
    // Add more as needed
};

/**
 * @brief Base interface for all events in the event-driven architecture.
 *
 * Events are used for communication between different systems in the simulation.
 * Each event must provide its type for proper routing and handling.
 */
class IEvent
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived events.
     */
    virtual ~IEvent() = default;

    /**
     * @brief Get the type of this event.
     *
     * @return EventType The specific type of this event instance.
     */
    virtual EventType getType() const = 0;
};

#endif
