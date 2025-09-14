#include "EventBus.h"

EventBus::EventBus() {}

void EventBus::subscribe(EventType type, std::function &lt; void(const IEvent &amp;) & gt; handler)
{
    handlers_[type].push_back(handler);
}

void EventBus::publish(const IEvent &amp; event)
{
    auto it = handlers_.find(event.getType());
    if (it != handlers_.end())
    {
        for (auto &amp; handler : it - &gt; second)
        {
            handler(event);
        }
    }
}
