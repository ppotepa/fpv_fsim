# EventBus.h / EventBus.cpp

## Constructors

- `EventBus()`

  **Summary:** Default constructor for the event bus.

## Public Methods

- `void subscribe(EventType type, std::function<void(const IEvent &)> handler)`

  **Summary:** Subscribes a handler function to a specific event type.

- `void publish(const IEvent &event)`

  **Summary:** Publishes an event to all subscribed handlers of that event type.
