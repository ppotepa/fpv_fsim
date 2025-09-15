#pragma once
#include "../core/IEvent.h"

/**
 * Event triggered when no asset packages are found during bootstrap.
 */
struct NoPackagesFoundEvent : public IEvent
{
    NoPackagesFoundEvent() = default;
    EventType getType() const override { return EventType::NoPackagesFound; }
};

/**
 * Event triggered when the default world has been generated.
 */
struct DefaultWorldGeneratedEvent : public IEvent
{
    DefaultWorldGeneratedEvent() = default;
    EventType getType() const override { return EventType::DefaultWorldGenerated; }
};
