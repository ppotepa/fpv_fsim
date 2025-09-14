#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "IEvent.h"
#include <functional>
#include <unordered_map>
#include <vector>

class EventBus
{
public:
    EventBus();
    void subscribe(EventType type, std::function<void(const IEvent &)> handler);
    void publish(const IEvent &event);

private:
    std::unordered_map<EventType, std::vector<std::function<void(const IEvent &)>>> handlers_;
};

#endif
