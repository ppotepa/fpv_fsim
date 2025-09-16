/**
 * @file CelShadingSystem.h
 * @brief Cel-shading (toon shading) rendering system
 *
 * The CelShadingSystem implements stylized cel-shading with band quantization
 * and rim lighting for the voxel busy indicator scene. Features include:
 * - Multi-band light quantization for cartoon appearance
 * - Rim lighting for object definition
 * - Configurable shading parameters
 * - Integration with Math utilities for calculations
 * - Support for multiple light sources
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Cel-shading rendering system
 *
 * Implements stylized cartoon-like shading with quantized lighting
 * bands and rim lighting effects for enhanced visual definition.
 */
class CelShadingSystem
{
public:
    /**
     * @brief Light source definition
     */
    struct Light
    {
        Math::float3 direction; /**< Light direction (normalized) */
        Math::float3 color;     /**< Light color (RGB) */
        float intensity;        /**< Light intensity */
        bool enabled;           /**< Whether light is active */

        Light() : direction{0, -1, 0}, color{1, 1, 1}, intensity(1.0f), enabled(true) {}
        Light(const Math::float3 &dir, const Math::float3 &col, float intens)
            : direction(Math::norm(dir)), color(col), intensity(intens), enabled(true) {}
    };

    /**
     * @brief Cel-shading parameters
     */
    struct CelShadingParams
    {
        uint32_t bandCount;          /**< Number of lighting bands */
        float bandSmoothness;        /**< Smoothness between bands */
        float rimPower;              /**< Rim lighting power */
        float rimIntensity;          /**< Rim lighting intensity */
        Math::float3 rimColor;       /**< Rim lighting color */
        Math::float3 ambientColor;   /**< Ambient light color */
        float ambientIntensity;      /**< Ambient light intensity */
        bool enableRimLighting;      /**< Whether rim lighting is enabled */
        bool enableBandQuantization; /**< Whether to quantize lighting bands */

        CelShadingParams()
            : bandCount(4), bandSmoothness(0.1f), rimPower(2.0f), rimIntensity(0.5f), rimColor{0.8f, 0.9f, 1.0f}, ambientColor{0.2f, 0.3f, 0.4f}, ambientIntensity(0.3f), enableRimLighting(true), enableBandQuantization(true)
        {
        }
    };

    /**
     * @brief Material properties for cel-shading
     */
    struct CelMaterial
    {
        Math::float3 baseColor;   /**< Base material color */
        Math::float3 shadowColor; /**< Color in shadowed areas */
        float roughness;          /**< Surface roughness [0,1] */
        float metallic;           /**< Metallic factor [0,1] */
        float subsurface;         /**< Subsurface scattering [0,1] */

        CelMaterial()
            : baseColor{0.8f, 0.8f, 0.8f}, shadowColor{0.3f, 0.3f, 0.5f}, roughness(0.5f), metallic(0.0f), subsurface(0.0f)
        {
        }

        CelMaterial(const Math::float3 &base, const Math::float3 &shadow)
            : baseColor(base), shadowColor(shadow), roughness(0.5f), metallic(0.0f), subsurface(0.0f)
        {
        }
    };

    /**
     * @brief Shading calculation result
     */
    struct ShadingResult
    {
        Math::float3 finalColor; /**< Final shaded color */
        float lightIntensity;    /**< Overall light intensity */
        float rimFactor;         /**< Rim lighting factor */
        uint32_t activeBand;     /**< Active lighting band index */

        ShadingResult() : finalColor{0, 0, 0}, lightIntensity(0), rimFactor(0), activeBand(0) {}
    };

private:
    /** @brief Current shading parameters */
    CelShadingParams params;

    /** @brief Active light sources */
    std::vector<Light> lights;

    /** @brief Cached band thresholds for performance */
    std::vector<float> bandThresholds;

public:
    /**
     * @brief Construct a new CelShadingSystem
     *
     * @param shadingParams Initial shading parameters
     */
    CelShadingSystem(const CelShadingParams &shadingParams = CelShadingParams())
        : params(shadingParams)
    {
        updateBandThresholds();
        setupDefaultLighting();
    }

    /**
     * @brief Calculate cel-shaded lighting for a surface point
     *
     * @param position World position of the surface point
     * @param normal Surface normal (normalized)
     * @param viewDirection Direction to viewer (normalized)
     * @param material Material properties
     * @return Shading calculation result
     */
    ShadingResult calculateShading(const Math::float3 &position,
                                   const Math::float3 &normal,
                                   const Math::float3 &viewDirection,
                                   const CelMaterial &material)
    {
        ShadingResult result;

        // Start with ambient lighting
        Math::float3 color = Math::scale(
            Math::mul(params.ambientColor, material.baseColor),
            params.ambientIntensity);

        float totalLightIntensity = 0.0f;

        // Process each light source
        for (const auto &light : lights)
        {
            if (!light.enabled)
                continue;

            // Calculate lighting contribution
            float dotNL = Math::dot(normal, Math::scale(light.direction, -1.0f));
            float lightContribution = Math::clamp(dotNL, 0.0f, 1.0f);

            // Apply cel-shading quantization
            if (params.enableBandQuantization)
            {
                lightContribution = quantizeToBands(lightContribution);
            }

            // Combine with light color and intensity
            Math::float3 lightColor = Math::scale(
                Math::mul(light.color, material.baseColor),
                lightContribution * light.intensity);

            color = Math::add(color, lightColor);
            totalLightIntensity += lightContribution * light.intensity;
        }

        // Apply rim lighting if enabled
        float rimFactor = 0.0f;
        if (params.enableRimLighting)
        {
            rimFactor = calculateRimLighting(normal, viewDirection);
            Math::float3 rimContribution = Math::scale(params.rimColor, rimFactor * params.rimIntensity);
            color = Math::add(color, rimContribution);
        }

        // Apply shadow color mixing in dark areas
        float shadowFactor = 1.0f - Math::clamp(totalLightIntensity, 0.0f, 1.0f);
        if (shadowFactor > 0.0f)
        {
            Math::float3 shadowContribution = Math::scale(material.shadowColor, shadowFactor);
            color = Math::lerp3(color, shadowContribution, shadowFactor * 0.5f);
        }

        // Store results
        result.finalColor = color;
        result.lightIntensity = totalLightIntensity;
        result.rimFactor = rimFactor;
        result.activeBand = getBandIndex(totalLightIntensity);

        return result;
    }

    /**
     * @brief Set cel-shading parameters
     *
     * @param newParams New shading parameters
     */
    void setParams(const CelShadingParams &newParams)
    {
        params = newParams;
        updateBandThresholds();
    }

    /**
     * @brief Get current cel-shading parameters
     *
     * @return Current parameters
     */
    const CelShadingParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Add a light source
     *
     * @param light Light to add
     */
    void addLight(const Light &light)
    {
        lights.push_back(light);
    }

    /**
     * @brief Remove all lights
     */
    void clearLights()
    {
        lights.clear();
    }

    /**
     * @brief Set directional light (sun/moon)
     *
     * @param direction Light direction
     * @param color Light color
     * @param intensity Light intensity
     */
    void setDirectionalLight(const Math::float3 &direction,
                             const Math::float3 &color = {1, 1, 1},
                             float intensity = 1.0f)
    {
        clearLights();
        addLight(Light(direction, color, intensity));
    }

    /**
     * @brief Setup default three-point lighting
     */
    void setupDefaultLighting()
    {
        clearLights();

        // Key light (main directional light)
        addLight(Light({-0.3f, -0.7f, -0.6f}, {1.0f, 0.95f, 0.8f}, 1.0f));

        // Fill light (softer secondary light)
        addLight(Light({0.5f, -0.2f, 0.8f}, {0.6f, 0.7f, 1.0f}, 0.4f));

        // Rim light (back light for definition)
        addLight(Light({0.2f, 0.8f, -0.5f}, {0.9f, 0.9f, 1.0f}, 0.3f));
    }

    /**
     * @brief Get number of active lights
     *
     * @return Number of enabled lights
     */
    size_t getActiveLightCount() const
    {
        size_t count = 0;
        for (const auto &light : lights)
        {
            if (light.enabled)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Quantize light intensity to discrete bands
     *
     * @param intensity Input light intensity [0,1]
     * @return Quantized intensity
     */
    float quantizeToBands(float intensity)
    {
        if (bandThresholds.empty())
            return intensity;

        // Use Math utility for band quantization
        return Math::quantizeToBands(intensity, bandThresholds, params.bandSmoothness);
    }

    /**
     * @brief Calculate rim lighting factor
     *
     * @param normal Surface normal
     * @param viewDirection View direction
     * @return Rim lighting factor [0,1]
     */
    float calculateRimLighting(const Math::float3 &normal, const Math::float3 &viewDirection)
    {
        return Math::calculateRimLighting(normal, viewDirection, params.rimPower);
    }

    /**
     * @brief Get the active lighting band index
     *
     * @param intensity Light intensity
     * @return Band index
     */
    uint32_t getBandIndex(float intensity)
    {
        for (size_t i = 0; i < bandThresholds.size(); ++i)
        {
            if (intensity <= bandThresholds[i])
            {
                return static_cast<uint32_t>(i);
            }
        }
        return static_cast<uint32_t>(bandThresholds.size() - 1);
    }

    /**
     * @brief Update cached band threshold values
     */
    void updateBandThresholds()
    {
        bandThresholds.clear();
        if (params.bandCount == 0)
            return;

        // Create evenly spaced thresholds
        for (uint32_t i = 1; i <= params.bandCount; ++i)
        {
            float threshold = static_cast<float>(i) / static_cast<float>(params.bandCount);
            bandThresholds.push_back(threshold);
        }
    }
};

