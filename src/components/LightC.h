#pragma once
#include "../core/IComponent.h"
#include <string>

/**
 * @file LightC.h
 * @brief Component for entities that emit light.
 *
 * The LightC component defines the lighting properties of an entity,
 * including light type, color, intensity, and range.
 * Entities with this component act as light sources in the scene.
 */

/**
 * @struct LightC
 * @brief Component that defines lighting properties for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for rendering systems to use the entity as a light source.
 * It supports different light types and controls appearance.
 */
struct LightC : public IComponent
{
    /** @brief Type of light (e.g., "point", "spot", "directional") */
    std::string lightType;

    /** @brief RGB color values (red, green, blue) */
    float color[3];

    /** @brief Light intensity factor */
    float intensity;

    /** @brief Maximum range of the light's effect */
    float range;

    /**
     * @brief Construct a new LightC component.
     *
     * @param type Type of light (default: "point")
     * @param r Red component (default: 1.0)
     * @param g Green component (default: 1.0)
     * @param b Blue component (default: 1.0)
     * @param i Intensity factor (default: 1.0)
     * @param rng Range of effect (default: 10.0)
     */
    LightC(std::string type = "point",
           float r = 1.0f,
           float g = 1.0f,
           float b = 1.0f,
           float i = 1.0f,
           float rng = 10.0f)
        : lightType(type), intensity(i), range(rng)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
};
