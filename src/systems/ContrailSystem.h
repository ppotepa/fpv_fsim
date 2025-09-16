#pragma once

#include "../core/System.h"
#include "../components/ContrailComponent.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>

namespace ECS
{

    // ============================================================================
    // Particle Trail Data Structures
    // ============================================================================

    struct TrailParticle
    {
        Math::float3 position;
        Math::float3 velocity;
        float life = 1.0f; // 0.0 = dead, 1.0 = just spawned
        float size = 1.0f;
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        float age = 0.0f; // Time since spawn

        // Trail-specific properties
        float trailWeight = 1.0f; // Influence on trail curve
        Math::float3 normal;      // For ribbon trails
        float distance = 0.0f;    // Distance along trail
    };

    struct TrailSegment
    {
        Math::float3 startPos;
        Math::float3 endPos;
        Math::float3 startNormal;
        Math::float3 endNormal;
        float startWidth;
        float endWidth;
        Math::float4 startColor;
        Math::float4 endColor;
        float startLife;
        float endLife;
        float length;
    };

    struct TrailMesh
    {
        std::vector<Math::float3> vertices;
        std::vector<Math::float3> normals;
        std::vector<Math::float2> uvs;
        std::vector<Math::float4> colors;
        std::vector<uint32_t> indices;

        bool needsUpdate = true;
        uint32_t vertexBufferId = 0;
        uint32_t indexBufferId = 0;

        void clear();
        void reserve(size_t vertexCount, size_t indexCount);
    };

    // ============================================================================
    // Contrail System Configuration
    // ============================================================================

    struct ContrailSystemConfig
    {
        // Performance settings
        uint32_t maxParticlesPerTrail = 100;
        uint32_t maxActiveTrails = 50;
        float updateFrequency = 60.0f; // Updates per second
        float cullDistance = 1000.0f;  // Distance beyond which trails are culled

        // Quality settings
        uint32_t segmentSubdivisions = 2; // Smoothing subdivisions
        bool enableCollision = false;
        bool enableWindEffect = false;
        bool enableTurbulence = false;

        // Rendering settings
        bool enableAlphaBlending = true;
        bool enableDepthWrite = false;
        bool enableSoftParticles = true;
        float fadeNearDistance = 1.0f;
        float fadeFarDistance = 100.0f;

        // Memory management
        bool useObjectPooling = true;
        uint32_t initialPoolSize = 1000;
        uint32_t poolGrowthSize = 500;
    };

    // ============================================================================
    // Main Contrail System
    // ============================================================================

    class ContrailSystem : public System
    {
    public:
        explicit ContrailSystem(const ContrailSystemConfig &config = ContrailSystemConfig{});
        ~ContrailSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const ContrailSystemConfig &config);
        const ContrailSystemConfig &getConfig() const;

        // Trail management
        void createTrail(EntityId entityId, const ContrailComponent &component);
        void removeTrail(EntityId entityId);
        void updateTrailComponent(EntityId entityId, const ContrailComponent &component);

        // Environmental effects
        void setWindVector(const Math::float3 &wind);
        void setGravity(const Math::float3 &gravity);
        void setTurbulenceIntensity(float intensity);

        // Performance monitoring
        uint32_t getActiveTrailCount() const;
        uint32_t getTotalParticleCount() const;
        float getAverageUpdateTime() const;

        // Debugging and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        // ============================================================================
        // Internal Trail Management
        // ============================================================================

        struct TrailData
        {
            ContrailComponent component;
            std::vector<TrailParticle> particles;
            TrailMesh mesh;

            // State tracking
            Math::float3 lastPosition;
            float timeSinceLastEmit = 0.0f;
            float totalLifeTime = 0.0f;
            bool isActive = true;

            // Performance data
            float lastUpdateTime = 0.0f;
            uint32_t particleCount = 0;

            TrailData() = default;
            TrailData(const ContrailComponent &comp) : component(comp) {}
        };

        ContrailSystemConfig config_;
        std::map<EntityId, std::unique_ptr<TrailData>> activeTrails_;

        // Environmental forces
        Math::float3 windVector_ = {0.0f, 0.0f, 0.0f};
        Math::float3 gravity_ = {0.0f, -9.81f, 0.0f};
        float turbulenceIntensity_ = 0.0f;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Object pooling for performance
        std::vector<TrailParticle> particlePool_;
        std::vector<size_t> freeParticleIndices_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateTrailEmission(EntityId entityId, TrailData &trail, float deltaTime);
        void updateTrailParticles(TrailData &trail, float deltaTime);
        void updateTrailMesh(TrailData &trail);
        void cullDistantTrails();

        // ============================================================================
        // Particle Management
        // ============================================================================

        void emitParticle(TrailData &trail, const Math::float3 &position, const Math::float3 &velocity);
        void updateParticlePhysics(TrailParticle &particle, float deltaTime);
        void applyEnvironmentalForces(TrailParticle &particle, float deltaTime);
        void killExpiredParticles(TrailData &trail);

        // ============================================================================
        // Mesh Generation
        // ============================================================================

        void generateTrailMesh(TrailData &trail);
        void generateRibbonMesh(TrailData &trail);
        void generateTubeMesh(TrailData &trail);
        void smoothTrailCurve(std::vector<TrailParticle> &particles);
        void calculateTrailNormals(std::vector<TrailParticle> &particles);

        std::vector<TrailSegment> generateTrailSegments(const std::vector<TrailParticle> &particles);
        void addQuadToMesh(TrailMesh &mesh, const TrailSegment &segment, float uvStart, float uvEnd);
        void addTriangleToMesh(TrailMesh &mesh, const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                               const Math::float3 &n0, const Math::float3 &n1, const Math::float3 &n2,
                               const Math::float2 &uv0, const Math::float2 &uv1, const Math::float2 &uv2,
                               const Math::float4 &c0, const Math::float4 &c1, const Math::float4 &c2);

        // ============================================================================
        // Rendering Support
        // ============================================================================

        void renderTrail(const TrailData &trail);
        void setupTrailMaterial(const ContrailComponent &component);
        void bindTrailTextures(const ContrailComponent &component);
        void updateTrailUniforms(const ContrailComponent &component);

        // ============================================================================
        // Utility Methods
        // ============================================================================

        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float3 getEntityVelocity(EntityId entityId) const;
        float calculateEmissionRate(const ContrailComponent &component) const;
        Math::float4 calculateParticleColor(const ContrailComponent &component, float life) const;
        float calculateParticleSize(const ContrailComponent &component, float life) const;

        // Interpolation and smoothing
        Math::float3 catmullRomSpline(const Math::float3 &p0, const Math::float3 &p1,
                                      const Math::float3 &p2, const Math::float3 &p3, float t);
        Math::float3 calculateTangent(const std::vector<TrailParticle> &particles, size_t index);
        Math::float3 calculateBinormal(const Math::float3 &tangent, const Math::float3 &normal);

        // Object pooling
        TrailParticle *acquireParticle();
        void releaseParticle(TrailParticle *particle);
        void expandParticlePool();

        // Performance optimization
        bool shouldUpdateTrail(const TrailData &trail, float deltaTime) const;
        float calculateLODFactor(EntityId entityId) const;
        void optimizeTrailMesh(TrailMesh &mesh);

        // ============================================================================
        // Physics and Forces
        // ============================================================================

        Math::float3 calculateAerodynamicForce(const TrailParticle &particle, const Math::float3 &velocity) const;
        Math::float3 calculateTurbulence(const Math::float3 &position, float time) const;
        Math::float3 calculateWindForce(const TrailParticle &particle) const;
        void handleCollisions(TrailParticle &particle) const;

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderTrailDebugInfo(const TrailData &trail, EntityId entityId);
        void updatePerformanceCounters(float deltaTime);
        void logTrailStatistics() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline void TrailMesh::clear()
    {
        vertices.clear();
        normals.clear();
        uvs.clear();
        colors.clear();
        indices.clear();
        needsUpdate = true;
    }

    inline void TrailMesh::reserve(size_t vertexCount, size_t indexCount)
    {
        vertices.reserve(vertexCount);
        normals.reserve(vertexCount);
        uvs.reserve(vertexCount);
        colors.reserve(vertexCount);
        indices.reserve(indexCount);
    }

    inline uint32_t ContrailSystem::getActiveTrailCount() const
    {
        return static_cast<uint32_t>(activeTrails_.size());
    }

    inline uint32_t ContrailSystem::getTotalParticleCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, trail] : activeTrails_)
        {
            total += trail->particleCount;
        }
        return total;
    }

    inline float ContrailSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool ContrailSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void ContrailSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const ContrailSystemConfig &ContrailSystem::getConfig() const
    {
        return config_;
    }

} // namespace ECS

