#pragma once
#include "../core/IEvent.h"

/**
 * @file WorldGenEvents.h
 * @brief Event definitions for world generation and asset loading processes.
 *
 * This file defines events related to world generation, asset package loading,
 * and bootstrap processes. These events are used by world generation systems
 * and asset management systems to communicate state changes.
 */

/**
 * @struct NoPackagesFoundEvent
 * @brief Event triggered when no asset packages are found during bootstrap.
 *
 * This event is fired when the asset loading system cannot find any
 * valid asset packages during the initial bootstrap process. This
 * typically indicates a missing or corrupted asset directory.
 */
struct NoPackagesFoundEvent : public IEvent
{
    /** @brief Default constructor for NoPackagesFoundEvent */
    NoPackagesFoundEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::NoPackagesFound
     */
    EventType getType() const override { return EventType::NoPackagesFound; }
};

/**
 * @struct DefaultWorldGeneratedEvent
 * @brief Event triggered when the default world has been generated.
 *
 * This event is fired after the default world scene has been successfully
 * generated and loaded. It signals that the basic world setup is complete
 * and the simulation can begin.
 */
struct DefaultWorldGeneratedEvent : public IEvent
{
    /** @brief Default constructor for DefaultWorldGeneratedEvent */
    DefaultWorldGeneratedEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::DefaultWorldGenerated
     */
    EventType getType() const override { return EventType::DefaultWorldGenerated; }
};

