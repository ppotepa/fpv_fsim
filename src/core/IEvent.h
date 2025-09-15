#ifndef IEVENT_H
#define IEVENT_H

enum class EventType
{
    BatteryLow,
    Collision,
    ConsoleToggle,
    ConsoleVisibilityChanged,
    NoPackagesFound,
    DefaultWorldGenerated,
    // Add more as needed
};

class IEvent
{
public:
    virtual ~IEvent() = default;
    virtual EventType getType() const = 0;
};

#endif
