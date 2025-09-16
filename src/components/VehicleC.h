#pragma once
#include "../core/IComponent.h"
#include <string>

/**
 * @file VehicleC.h
 * @brief Component for entities that behave as vehicles.
 *
 * The VehicleC component defines the vehicular properties of an entity,
 * including vehicle type, speed, acceleration, and handling characteristics.
 * Entities with this component can be controlled as vehicles in the simulation.
 */

/**
 * @struct VehicleC
 * @brief Component that defines vehicle behavior for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for vehicle systems to control the entity as a specific
 * type of vehicle (drone, car, aircraft, etc.).
 */
struct VehicleC : public IComponent
{
    /** @brief Type of vehicle (e.g., "drone", "car", "aircraft", etc.) */
    std::string vehicleType;

    /** @brief Maximum speed of the vehicle in units per second */
    float maxSpeed;

    /** @brief Acceleration of the vehicle in units per second squared */
    float acceleration;

    /** @brief Maneuverability factor affecting turning and handling */
    float maneuverability;

    /** @brief Type of controller used for the vehicle */
    std::string controllerType;

    /**
     * @brief Construct a new VehicleC component.
     *
     * @param type Type of vehicle (default: "drone")
     * @param speed Maximum speed (default: 100.0)
     * @param accel Acceleration (default: 10.0)
     * @param maneuver Maneuverability factor (default: 5.0)
     * @param controller Type of controller (default: "manual")
     */
    VehicleC(std::string type = "drone",
             float speed = 100.0f,
             float accel = 10.0f,
             float maneuver = 5.0f,
             std::string controller = "manual")
        : vehicleType(type), maxSpeed(speed), acceleration(accel),
          maneuverability(maneuver), controllerType(controller) {}
};
