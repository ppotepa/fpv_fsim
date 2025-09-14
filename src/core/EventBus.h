#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "IEvent.h"
#include &lt; functional & gt;
#include &lt; unordered_map & gt;
#include &lt; vector & gt;

class EventBus
{
public:
    EventBus();
    void subscribe(EventType type, std::function &lt; void(const IEvent &amp;) & gt; handler);
    void publish(const IEvent &amp; event);

private:
    std::unordered_map &lt;
    EventType, std::vector &lt;
    std::function &lt;
    void(const IEvent &amp;) & gt;
    &gt;
    &gt;
    handlers_;
};

#endif
