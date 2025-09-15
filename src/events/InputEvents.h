#pragma once
#include "../core/IEvent.h"

/**
 * Event triggered when the console toggle key is pressed.
 */
struct ConsoleToggleEvent : public IEvent
{
    ConsoleToggleEvent() = default;
    EventType getType() const override { return EventType::ConsoleToggle; }
};

/**
 * Event triggered when console visibility changes.
 */
struct ConsoleVisibilityChangedEvent : public IEvent
{
    ConsoleVisibilityChangedEvent(bool visible) : isVisible(visible) {}
    EventType getType() const override { return EventType::ConsoleVisibilityChanged; }

    bool isVisible;
};
