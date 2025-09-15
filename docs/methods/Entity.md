# Entity.h / Entity.cpp

## Constructors

- `Entity(unsigned int id)`

  **Summary:** Constructor that initializes the entity with a unique ID.

## Template Methods

- `template <typename T> void addComponent(std::unique_ptr<T> component)`

  **Summary:** Adds a component of type T to the entity, storing it in the components map.

- `template <typename T> T *getComponent()`

  **Summary:** Retrieves a component of type T from the entity, returns nullptr if not found.
