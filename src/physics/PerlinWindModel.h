/**
 * @file PerlinWindModel.h
 * @brief Implementation of a Perlin noise-based wind model.
 *
 * This file implements a wind model using Perlin noise to generate
 * realistic turbulent wind patterns. The model creates spatially
 * coherent wind fields that vary smoothly across 3D space.
 */

#ifndef PERLINWINDMODEL_H
#define PERLINWINDMODEL_H

#include "IWindModel.h"

/**
 * @class PerlinWindModel
 * @brief Wind model using Perlin noise for realistic turbulence.
 *
 * This implementation generates wind velocity fields using Perlin noise,
 * creating natural-looking wind patterns with spatial coherence. The wind
 * varies smoothly in space and can include multiple octaves for complex
 * turbulence patterns.
 */
class PerlinWindModel : public IWindModel
{
public:
    /**
     * @brief Construct a new PerlinWindModel.
     *
     * @param strength Base wind strength multiplier
     * @param frequency Spatial frequency of the wind variations
     * @param amplitude Maximum wind speed variation
     * @param seed Random seed for reproducible wind patterns
     */
    PerlinWindModel(float strength, float frequency, float amplitude, int seed);

    /**
     * @brief Calculate wind velocity at a given position using Perlin noise.
     *
     * Uses Perlin noise functions to generate spatially coherent wind
     * velocity components. The wind field varies smoothly and creates
     * realistic turbulence patterns.
     *
     * @param x X coordinate of the position
     * @param y Y coordinate of the position
     * @param z Z coordinate of the position
     * @param wx [out] X component of wind velocity at the position
     * @param wy [out] Y component of wind velocity at the position
     * @param wz [out] Z component of wind velocity at the position
     */
    void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const override;

private:
    /** @brief Base wind strength multiplier */
    float strength_;

    /** @brief Spatial frequency of wind variations */
    float frequency_;

    /** @brief Maximum wind speed variation */
    float amplitude_;

    /** @brief Random seed for reproducible patterns */
    int seed_;
};

#endif
