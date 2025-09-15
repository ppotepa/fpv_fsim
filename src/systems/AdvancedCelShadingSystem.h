#pragma once

#include "../core/System.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

namespace ECS
{

    // Forward declarations
    class Entity;
    class MaterialComponent;
    class MeshComponent;
    class LightComponent;

    // ============================================================================
    // Advanced Cel-Shading Data Structures
    // ============================================================================

    struct AdvancedCelShadingMaterial
    {
        // Base material properties
        Math::float4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float4 shadowColor = {0.3f, 0.3f, 0.5f, 1.0f};
        Math::float4 highlightColor = {1.2f, 1.2f, 1.4f, 1.0f};

        // Cel-shading specific parameters
        uint32_t shadingLevels = 3;   // Number of discrete shading levels
        float shadowThreshold = 0.5f; // Light threshold for shadow transition
        float shadowSoftness = 0.1f;  // Softness of shadow transitions

        // Outline properties
        bool enableOutline = true;
        Math::float4 outlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        float outlineWidth = 0.01f; // Outline width in screen space
        float outlineDepthSensitivity = 1.0f;
        float outlineNormalSensitivity = 1.0f;

        // Rim lighting
        bool enableRimLighting = true;
        Math::float4 rimColor = {1.0f, 1.0f, 1.0f, 1.0f};
        float rimPower = 2.0f;
        float rimIntensity = 1.0f;

        // Specular highlights
        bool enableSpecular = true;
        Math::float4 specularColor = {1.0f, 1.0f, 1.0f, 1.0f};
        float specularPower = 32.0f;
        float specularIntensity = 0.5f;
        uint32_t specularLevels = 2; // Discrete specular levels

        // Texture properties
        std::string diffuseTexture;
        std::string shadowRampTexture;   // 1D texture for shadow ramp
        std::string specularRampTexture; // 1D texture for specular ramp
        std::string outlineTexture;      // Texture for outline variation

        // Animation properties
        bool animateColors = false;
        float colorAnimationSpeed = 1.0f;
        float colorAnimationAmplitude = 0.1f;

        // Advanced properties
        bool useVertexColors = false;
        bool useEnvironmentMapping = false;
        float environmentIntensity = 0.3f;
        bool useFresnel = true;
        float fresnelPower = 3.0f;
    };

    struct CelShadingLight
    {
        EntityId lightEntityId;
        Math::float3 direction;
        Math::float4 color;
        float intensity;

        // Cel-shading specific light properties
        float shadowBias = 0.001f;
        bool castCelShadows = true;
        uint32_t shadowSteps = 3; // Number of shadow cascade levels
        float shadowSoftness = 0.2f;

        // Light animation
        bool animateIntensity = false;
        float intensityAnimationSpeed = 1.0f;
        float intensityAnimationRange = 0.2f;
    };

    // ============================================================================
    // Advanced Cel-Shading System Configuration
    // ============================================================================

    struct AdvancedCelShadingSystemConfig
    {
        // Rendering quality
        bool enableMultiPass = true;     // Use multiple passes for better quality
        bool enableSSAO = false;         // Screen-space ambient occlusion
        bool enableShadowMapping = true; // Real-time shadows
        uint32_t shadowMapSize = 1024;   // Shadow map resolution

        // Performance settings
        uint32_t maxLights = 8;         // Maximum number of lights
        bool enableLightCulling = true; // Cull lights outside view
        float cullingDistance = 100.0f; // Light culling distance
        bool enableLOD = true;          // Level of detail for distant objects

        // Outline settings
        bool enableScreenSpaceOutlines = true;
        uint32_t outlineTextureSize = 512; // Outline detection texture size
        float outlineDepthThreshold = 0.1f;
        float outlineNormalThreshold = 0.4f;

        // Post-processing
        bool enableColorGrading = false;
        bool enableVignette = false;
        float vignetteIntensity = 0.3f;
        bool enableFilmGrain = false;
        float filmGrainIntensity = 0.1f;

        // Debug settings
        bool showWireframe = false;
        bool showNormals = false;
        bool showLightInfluence = false;
        bool showShadowCascades = false;
    };

    // ============================================================================
    // Advanced Cel-Shading System (extends the basic one)
    // ============================================================================

    class AdvancedCelShadingSystem : public System
    {
    public:
        explicit AdvancedCelShadingSystem(const AdvancedCelShadingSystemConfig &config = AdvancedCelShadingSystemConfig{});
        ~AdvancedCelShadingSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const AdvancedCelShadingSystemConfig &config);
        const AdvancedCelShadingSystemConfig &getConfig() const;

        // Material management
        void createCelMaterial(const std::string &materialId, const AdvancedCelShadingMaterial &material);
        void updateCelMaterial(const std::string &materialId, const AdvancedCelShadingMaterial &material);
        void removeCelMaterial(const std::string &materialId);
        bool hasCelMaterial(const std::string &materialId) const;
        const AdvancedCelShadingMaterial *getCelMaterial(const std::string &materialId) const;

        // Light management
        void registerLight(EntityId lightEntityId);
        void unregisterLight(EntityId lightEntityId);
        void updateLightProperties(EntityId lightEntityId);

        // Rendering controls
        void setGlobalToonLevel(uint32_t levels);
        void setGlobalOutlineWidth(float width);
        void setGlobalRimLightIntensity(float intensity);

        // Shadow controls
        void setShadowDistance(float distance);
        void setShadowCascades(uint32_t cascades);
        void setShadowSoftness(float softness);

        // Environment settings
        void setAmbientColor(const Math::float4 &color);
        void setFogColor(const Math::float4 &color);
        void setFogDensity(float density);

        // Performance monitoring
        uint32_t getActiveMaterialCount() const;
        uint32_t getActiveLightCount() const;
        float getAverageRenderTime() const;

        // Debug and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        AdvancedCelShadingSystemConfig config_;
        std::map<std::string, AdvancedCelShadingMaterial> celMaterials_;
        std::map<EntityId, CelShadingLight> celLights_;

        // Global settings
        uint32_t globalToonLevels_ = 3;
        float globalOutlineWidth_ = 0.01f;
        float globalRimLightIntensity_ = 1.0f;

        // Environment
        Math::float4 ambientColor_ = {0.2f, 0.2f, 0.3f, 1.0f};
        Math::float4 fogColor_ = {0.7f, 0.8f, 0.9f, 1.0f};
        float fogDensity_ = 0.01f;

        // Shadow settings
        float shadowDistance_ = 100.0f;
        uint32_t shadowCascades_ = 3;
        float shadowSoftness_ = 0.3f;

        // Performance tracking
        mutable float averageRenderTime_ = 0.0f;
        mutable uint32_t renderSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Core rendering methods
        void renderWithAdvancedCelShading();
        void setupAdvancedCelShadingUniforms(const AdvancedCelShadingMaterial &material);
        void renderScreenSpaceOutlines();
        void applyPostProcessingEffects();

        // Utility methods
        Math::float3 calculateAdvancedCelShading(const Math::float3 &normal, const Math::float3 &lightDir,
                                                 const AdvancedCelShadingMaterial &material) const;
        float quantizeLighting(float lightValue, uint32_t levels) const;
        Math::float3 quantizeColor(const Math::float3 &color, uint32_t levels) const;

        void updatePerformanceCounters(float deltaTime);
    };

    // ============================================================================
    // Inline Implementation
    // ============================================================================

    inline uint32_t AdvancedCelShadingSystem::getActiveMaterialCount() const
    {
        return static_cast<uint32_t>(celMaterials_.size());
    }

    inline uint32_t AdvancedCelShadingSystem::getActiveLightCount() const
    {
        return static_cast<uint32_t>(celLights_.size());
    }

    inline float AdvancedCelShadingSystem::getAverageRenderTime() const
    {
        return averageRenderTime_;
    }

    inline bool AdvancedCelShadingSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void AdvancedCelShadingSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const AdvancedCelShadingSystemConfig &AdvancedCelShadingSystem::getConfig() const
    {
        return config_;
    }

    inline bool AdvancedCelShadingSystem::hasCelMaterial(const std::string &materialId) const
    {
        return celMaterials_.find(materialId) != celMaterials_.end();
    }

    inline const AdvancedCelShadingMaterial *AdvancedCelShadingSystem::getCelMaterial(const std::string &materialId) const
    {
        auto it = celMaterials_.find(materialId);
        return (it != celMaterials_.end()) ? &it->second : nullptr;
    }

    inline float AdvancedCelShadingSystem::quantizeLighting(float lightValue, uint32_t levels) const
    {
        if (levels <= 1)
            return lightValue;

        float step = 1.0f / (levels - 1);
        return std::floor(lightValue / step) * step;
    }

    inline Math::float3 AdvancedCelShadingSystem::quantizeColor(const Math::float3 &color, uint32_t levels) const
    {
        return {
            quantizeLighting(color.x, levels),
            quantizeLighting(color.y, levels),
            quantizeLighting(color.z, levels)};
    }

} // namespace ECS
