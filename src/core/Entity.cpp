#include "Entity.h"

/**
 * @brief Construct an entity with a unique identifier.
 *
 * Initializes the entity with the provided ID and prepares the component storage.
 *
 * @param id The unique identifier for this entity
 */
Entity::Entity(unsigned int id) : id_(id) {}
