#pragma once

#include "../core/System.h"
#include "../components/VoxelCloudComponent.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>
#include <array>

namespace ECS
{

    // ============================================================================
    // Voxel Cloud Data Structures
    // ============================================================================

    struct VoxelData
    {
        float density = 0.0f; // 0.0 = empty, 1.0 = solid
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float3 normal = {0.0f, 1.0f, 0.0f};
        float temperature = 0.0f; // For heat distortion effects
        float humidity = 0.0f;    // For cloud formation
        uint8_t materialId = 0;   // Different cloud types

        bool isEmpty() const { return density <= 0.001f; }
        bool isSolid() const { return density >= 0.999f; }
    };

    struct VoxelChunk
    {
        static constexpr uint32_t CHUNK_SIZE = 16; // 16x16x16 voxels per chunk
        static constexpr uint32_t VOXEL_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

        std::array<VoxelData, VOXEL_COUNT> voxels;
        Math::float3 worldPosition;
        bool needsMeshUpdate = true;
        bool isEmpty = true;

        // Mesh data for rendering
        std::vector<Math::float3> vertices;
        std::vector<Math::float3> normals;
        std::vector<Math::float2> uvs;
        std::vector<Math::float4> colors;
        std::vector<uint32_t> indices;

        // GPU buffer handles
        uint32_t vertexBufferId = 0;
        uint32_t indexBufferId = 0;
        uint32_t instanceBufferId = 0;

        // Optimization data
        uint32_t activeVoxelCount = 0;
        float boundingRadius = 0.0f;
        float lastUpdateTime = 0.0f;

        VoxelData &getVoxel(uint32_t x, uint32_t y, uint32_t z);
        const VoxelData &getVoxel(uint32_t x, uint32_t y, uint32_t z) const;
        void setVoxel(uint32_t x, uint32_t y, uint32_t z, const VoxelData &voxel);

        void clear();
        void updateBounds();
        size_t getVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const;
    };

    struct CloudLayer
    {
        float altitude = 0.0f;
        float thickness = 100.0f;
        float coverage = 0.5f; // 0.0 = no clouds, 1.0 = full coverage
        float density = 0.8f;
        Math::float4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float4 shadowColor = {0.3f, 0.3f, 0.5f, 1.0f};

        // Animation properties
        Math::float2 windSpeed = {2.0f, 0.0f};
        float evolutionSpeed = 0.1f; // How fast clouds change shape
        float turbulence = 0.3f;

        // Noise parameters for generation
        uint32_t seed = 12345;
        float noiseScale = 0.01f;
        uint32_t noiseOctaves = 4;
        float noisePersistence = 0.5f;
        float noiseLacunarity = 2.0f;
    };

    // ============================================================================
    // Voxel Cloud System Configuration
    // ============================================================================

    struct VoxelCloudSystemConfig
    {
        // World parameters
        Math::float3 worldSize = {1000.0f, 200.0f, 1000.0f};
        float voxelSize = 2.0f;    // Size of each voxel in world units
        uint32_t maxChunks = 1000; // Maximum number of active chunks

        // Rendering settings
        uint32_t renderDistance = 500; // Distance in voxels
        uint32_t lodLevels = 4;        // Number of LOD levels
        bool enableVolumetricLighting = true;
        bool enableShadows = true;
        bool enableScattering = true;

        // Performance settings
        uint32_t maxChunkUpdatesPerFrame = 5;
        uint32_t maxMeshGenerationsPerFrame = 2;
        float cullingDistance = 1000.0f;
        bool enableFrustumCulling = true;
        bool enableOcclusionCulling = false;

        // Quality settings
        bool enableSmoothNormals = true;
        bool enableAmbientOcclusion = false;
        float ambientOcclusionRadius = 3.0f;
        uint32_t ambientOcclusionSamples = 16;

        // Animation settings
        bool enableCloudEvolution = true;
        float globalWindSpeed = 1.0f;
        Math::float3 globalWindDirection = {1.0f, 0.0f, 0.0f};
        float turbulenceIntensity = 0.5f;

        // Memory management
        bool useChunkPooling = true;
        uint32_t chunkPoolSize = 200;
        bool enableGarbageCollection = true;
        float garbageCollectionInterval = 5.0f; // seconds
    };

    // ============================================================================
    // Main Voxel Cloud System
    // ============================================================================

    class VoxelCloudSystem : public System
    {
    public:
        explicit VoxelCloudSystem(const VoxelCloudSystemConfig &config = VoxelCloudSystemConfig{});
        ~VoxelCloudSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const VoxelCloudSystemConfig &config);
        const VoxelCloudSystemConfig &getConfig() const;

        // Cloud management
        void createVoxelCloud(EntityId entityId, const VoxelCloudComponent &component);
        void removeVoxelCloud(EntityId entityId);
        void updateVoxelCloudComponent(EntityId entityId, const VoxelCloudComponent &component);

        // World interaction
        void setVoxel(const Math::float3 &worldPos, const VoxelData &voxel);
        VoxelData getVoxel(const Math::float3 &worldPos) const;
        void clearVoxels(const Math::float3 &center, float radius);
        void addCloudMass(const Math::float3 &center, float radius, float density);

        // Environmental controls
        void setGlobalWind(const Math::float3 &windDirection, float windSpeed);
        void addCloudLayer(const CloudLayer &layer);
        void removeCloudLayer(uint32_t layerIndex);
        void updateCloudLayer(uint32_t layerIndex, const CloudLayer &layer);

        // Lighting and atmosphere
        void setSunDirection(const Math::float3 &direction);
        void setSunColor(const Math::float4 &color);
        void setAmbientColor(const Math::float4 &color);
        void setScatteringCoefficients(float rayleigh, float mie);

        // Performance monitoring
        uint32_t getActiveChunkCount() const;
        uint32_t getTotalVoxelCount() const;
        float getAverageUpdateTime() const;

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
        // ============================================================================
        // Internal Cloud Management
        // ============================================================================

        struct CloudData
        {
            VoxelCloudComponent component;
            std::map<Math::int3, std::unique_ptr<VoxelChunk>, Math::Int3Comparator> chunks;

            // Generation parameters
            Math::float3 center;
            Math::float3 size;
            float totalDensity = 0.0f;

            // Animation state
            float animationTime = 0.0f;
            Math::float3 windOffset = {0.0f, 0.0f, 0.0f};

            // Performance tracking
            uint32_t activeChunkCount = 0;
            float lastFullUpdate = 0.0f;

            CloudData() = default;
            CloudData(const VoxelCloudComponent &comp) : component(comp) {}
        };

        VoxelCloudSystemConfig config_;
        std::map<EntityId, std::unique_ptr<CloudData>> activeClouds_;
        std::vector<CloudLayer> cloudLayers_;

        // Environmental state
        Math::float3 sunDirection_ = {0.707f, 0.707f, 0.0f};
        Math::float4 sunColor_ = {1.0f, 0.9f, 0.7f, 1.0f};
        Math::float4 ambientColor_ = {0.2f, 0.3f, 0.5f, 1.0f};
        float rayleighScattering_ = 0.0025f;
        float mieScattering_ = 0.004f;

        Math::float3 globalWindDirection_ = {1.0f, 0.0f, 0.0f};
        float globalWindSpeed_ = 1.0f;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;
        float lastGarbageCollection_ = 0.0f;

        // Debug visualization
        bool debugVisualization_ = false;

        // Chunk pooling for performance
        std::vector<std::unique_ptr<VoxelChunk>> chunkPool_;
        std::vector<VoxelChunk *> freeChunks_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateCloudGeneration(CloudData &cloud, float deltaTime);
        void updateCloudAnimation(CloudData &cloud, float deltaTime);
        void updateChunkMeshes(CloudData &cloud);
        void updateVisibility(CloudData &cloud);
        void performGarbageCollection();

        // ============================================================================
        // Chunk Management
        // ============================================================================

        Math::int3 worldToChunkCoord(const Math::float3 &worldPos) const;
        Math::float3 chunkToWorldPos(const Math::int3 &chunkCoord) const;
        Math::int3 voxelToLocalCoord(const Math::float3 &worldPos) const;

        VoxelChunk *getOrCreateChunk(CloudData &cloud, const Math::int3 &chunkCoord);
        void removeChunk(CloudData &cloud, const Math::int3 &chunkCoord);
        bool isChunkVisible(const VoxelChunk &chunk) const;
        void cullDistantChunks(CloudData &cloud);

        // ============================================================================
        // Voxel Generation and Manipulation
        // ============================================================================

        void generateCloudVoxels(CloudData &cloud);
        float calculateCloudDensity(const Math::float3 &worldPos, const CloudData &cloud, float time) const;
        Math::float4 calculateCloudColor(const Math::float3 &worldPos, float density, const CloudData &cloud) const;

        void applyCloudLayers(const Math::float3 &worldPos, VoxelData &voxel, float time) const;
        float sampleLayerDensity(const CloudLayer &layer, const Math::float3 &worldPos, float time) const;

        // Noise functions for cloud generation
        float fractalNoise(const Math::float3 &pos, uint32_t seed, uint32_t octaves,
                           float persistence, float lacunarity, float scale) const;
        float billowNoise(const Math::float3 &pos, uint32_t seed, float scale) const;
        float ridgedNoise(const Math::float3 &pos, uint32_t seed, float scale) const;

        // ============================================================================
        // Mesh Generation
        // ============================================================================

        void generateChunkMesh(VoxelChunk &chunk);
        void generateMarchingCubesMesh(VoxelChunk &chunk);
        void generateInstancedMesh(VoxelChunk &chunk);

        // Marching cubes implementation
        void marchCube(const VoxelChunk &chunk, uint32_t x, uint32_t y, uint32_t z,
                       std::vector<Math::float3> &vertices, std::vector<uint32_t> &indices);
        Math::float3 interpolateVertex(const Math::float3 &p1, const Math::float3 &p2,
                                       float density1, float density2, float isoLevel = 0.5f);

        // Mesh optimization
        void smoothMeshNormals(VoxelChunk &chunk);
        void calculateAmbientOcclusion(VoxelChunk &chunk);
        void optimizeMesh(VoxelChunk &chunk);

        // ============================================================================
        // Rendering Support
        // ============================================================================

        void renderCloud(const CloudData &cloud);
        void renderChunk(const VoxelChunk &chunk, const CloudData &cloud);
        void setupCloudMaterial(const VoxelCloudComponent &component);
        void setupVolumetricLighting();
        void setupAtmosphericScattering();

        // Volumetric rendering
        void renderVolumetricClouds(const CloudData &cloud);
        void renderCloudShadows(const CloudData &cloud);
        void applyAtmosphericPerspective(const VoxelChunk &chunk);

        // ============================================================================
        // Utility Methods
        // ============================================================================

        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float3 getCameraPosition() const;
        float calculateLODLevel(const Math::float3 &position) const;
        bool isInFrustum(const VoxelChunk &chunk) const;

        // Lighting calculations
        float calculateShadowFactor(const Math::float3 &worldPos, const CloudData &cloud) const;
        Math::float4 calculateVolumetricLighting(const Math::float3 &worldPos, const Math::float3 &viewDir) const;
        float calculateScattering(float cosTheta, float g) const; // Henyey-Greenstein phase function

        // Object pooling
        VoxelChunk *acquireChunk();
        void releaseChunk(VoxelChunk *chunk);
        void expandChunkPool();

        // Performance optimization
        bool shouldUpdateChunk(const VoxelChunk &chunk, float deltaTime) const;
        void updatePerformanceCounters(float deltaTime);

        // ============================================================================
        // Physics and Simulation
        // ============================================================================

        void simulateCloudPhysics(CloudData &cloud, float deltaTime);
        void applyWindForces(VoxelChunk &chunk, const Math::float3 &wind, float deltaTime);
        void simulateEvaporation(VoxelChunk &chunk, float deltaTime);
        void simulateCondensation(VoxelChunk &chunk, float deltaTime);

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderCloudDebugInfo(const CloudData &cloud, EntityId entityId);
        void renderChunkBounds(const VoxelChunk &chunk);
        void logCloudStatistics() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline VoxelData &VoxelChunk::getVoxel(uint32_t x, uint32_t y, uint32_t z)
    {
        return voxels[getVoxelIndex(x, y, z)];
    }

    inline const VoxelData &VoxelChunk::getVoxel(uint32_t x, uint32_t y, uint32_t z) const
    {
        return voxels[getVoxelIndex(x, y, z)];
    }

    inline void VoxelChunk::setVoxel(uint32_t x, uint32_t y, uint32_t z, const VoxelData &voxel)
    {
        voxels[getVoxelIndex(x, y, z)] = voxel;
        needsMeshUpdate = true;
    }

    inline size_t VoxelChunk::getVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const
    {
        return x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
    }

    inline uint32_t VoxelCloudSystem::getActiveChunkCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, cloud] : activeClouds_)
        {
            total += cloud->activeChunkCount;
        }
        return total;
    }

    inline uint32_t VoxelCloudSystem::getTotalVoxelCount() const
    {
        return getActiveChunkCount() * VoxelChunk::VOXEL_COUNT;
    }

    inline float VoxelCloudSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool VoxelCloudSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void VoxelCloudSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const VoxelCloudSystemConfig &VoxelCloudSystem::getConfig() const
    {
        return config_;
    }

    inline Math::int3 VoxelCloudSystem::worldToChunkCoord(const Math::float3 &worldPos) const
    {
        float chunkWorldSize = VoxelChunk::CHUNK_SIZE * config_.voxelSize;
        return {
            static_cast<int32_t>(std::floor(worldPos.x / chunkWorldSize)),
            static_cast<int32_t>(std::floor(worldPos.y / chunkWorldSize)),
            static_cast<int32_t>(std::floor(worldPos.z / chunkWorldSize))};
    }

    inline Math::float3 VoxelCloudSystem::chunkToWorldPos(const Math::int3 &chunkCoord) const
    {
        float chunkWorldSize = VoxelChunk::CHUNK_SIZE * config_.voxelSize;
        return {
            chunkCoord.x * chunkWorldSize,
            chunkCoord.y * chunkWorldSize,
            chunkCoord.z * chunkWorldSize};
    }

} // namespace ECS
