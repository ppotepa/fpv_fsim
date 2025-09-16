#pragma once
#include "../core/IEvent.h"

/**
 * @file InputEvents.h
 * @brief Event definitions for user input and console interactions.
 *
 * This file defines events related to user input handling, including
 * console toggling and visibility changes. These events are used
 * by input systems and UI management systems.
 */

/**
 * @struct ConsoleToggleEvent
 * @brief Event triggered when the console toggle key is pressed.
 *
 * This event is fired when the user presses the key combination
 * that toggles the developer console visibility. It contains no
 * additional data beyond the event type.
 */
struct ConsoleToggleEvent : public IEvent
{
    /** @brief Default constructor for ConsoleToggleEvent */
    ConsoleToggleEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::ConsoleToggle
     */
    EventType getType() const override { return EventType::ConsoleToggle; }
};

/**
 * @struct ConsoleVisibilityChangedEvent
 * @brief Event triggered when console visibility changes.
 *
 * This event is fired whenever the console visibility state changes,
 * either due to user input or programmatic control. It includes
 * the new visibility state.
 */
struct ConsoleVisibilityChangedEvent : public IEvent
{
    /**
     * @brief Construct a new ConsoleVisibilityChangedEvent.
     * @param visible The new visibility state of the console
     */
    ConsoleVisibilityChangedEvent(bool visible) : isVisible(visible) {}

    /**
     * @brief Get the event type identifier.
     * @return EventType::ConsoleVisibilityChanged
     */
    EventType getType() const override { return EventType::ConsoleVisibilityChanged; }

    /** @brief The current visibility state of the console */
    bool isVisible;
};

/**
 * @struct DebugModeToggled
 * @brief Event triggered when debug mode is toggled on or off.
 *
 * This event is fired when the user presses F9 to toggle debug mode.
 * It includes the new debug mode state (active/inactive).
 */
struct DebugModeToggled : public IEvent
{
    /**
     * @brief Construct a new DebugModeToggled event.
     * @param active The new debug mode state
     */
    DebugModeToggled(bool active) : isActive(active) {}

    /**
     * @brief Get the event type identifier.
     * @return EventType::DebugModeToggled
     */
    EventType getType() const override { return EventType::DebugModeToggled; }

    /** @brief The current debug mode state */
    bool isActive;
};
