#ifndef PHYSICS_CONFIG_H
#define PHYSICS_CONFIG_H

#include <string>

namespace Physics
{
    /**
     * @brief Physics engine configuration structure
     */
    struct PhysicsConfig
    {
        float fixedTimestep = 0.01f;      /**< Physics timestep in seconds */
        float gravity = 9.81f;            /**< Gravity constant in m/s² */
        bool enableCollisions = true;     /**< Whether collision detection is enabled */
        int iterationsPerStep = 1;        /**< Physics iterations per time step */
        int maxSubsteps = 10;             /**< Maximum physics substeps per frame */
        float seaLevelDensity = 1.225f;   /**< Air density at sea level in kg/m³ */
        float scaleHeight = 8000.0f;      /**< Atmospheric scale height in meters */
        float baseWindSpeed = 0.0f;       /**< Base wind speed in m/s */
        float turbulenceScale = 100.0f;   /**< Turbulence scale factor */
        float turbulenceIntensity = 0.1f; /**< Turbulence intensity (0-1) */
        int randomSeed = 12345;           /**< Random seed for procedural generators */
        float restitution = 0.5f;         /**< Collision elasticity (0-1) */
        float friction = 0.3f;            /**< Surface friction coefficient */

        PhysicsConfig() = default;
    };
}

#endif // PHYSICS_CONFIG_H
