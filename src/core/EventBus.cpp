#include "EventBus.h"

EventBus::EventBus() {}

void EventBus::subscribe(EventType type, std::function<void(const IEvent &)> handler)
{
    handlers_[type].push_back(handler);
}

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
