#pragma once

#include "../core/System.h"
#include "../math/MathUtils.h"
#include "../config/SceneConfigParser.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <string>

namespace ECS
{

    // ============================================================================
    // Animation Data Structures
    // ============================================================================

    struct AnimationKeyframe
    {
        float time = 0.0f;
        Math::float3 position = {0.0f, 0.0f, 0.0f};
        Math::float4 rotation = {0.0f, 0.0f, 0.0f, 1.0f}; // Quaternion
        Math::float3 scale = {1.0f, 1.0f, 1.0f};
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        float value = 0.0f; // Generic scalar value

        // Custom properties for specialized animations
        std::map<std::string, float> customFloats;
        std::map<std::string, Math::float3> customVectors;
        std::map<std::string, Math::float4> customColors;
    };

    struct AnimationTrack
    {
        enum class Type
        {
            Transform, // Position, rotation, scale
            Color,     // Color animation
            Value,     // Generic scalar value
            Orbital,   // Orbital motion
            Custom     // Custom animation with callback
        };

        enum class Interpolation
        {
            Linear,
            Cubic,
            Bezier,
            Step,
            Smooth
        };

        Type type = Type::Transform;
        Interpolation interpolation = Interpolation::Linear;
        std::string targetProperty; // Property name to animate
        std::vector<AnimationKeyframe> keyframes;

        // Track-specific parameters
        bool loop = true;
        bool pingPong = false;
        float speed = 1.0f;
        float delay = 0.0f;

        // Orbital motion specific
        Math::OrbitParams orbitParams;

        // Custom animation callback
        std::function<void(EntityId, float, const AnimationKeyframe &)> customCallback;
    };

    struct Animation
    {
        std::string id;
        std::string name;
        float duration = 1.0f;
        bool autoStart = true;
        bool loop = true;
        float playbackSpeed = 1.0f;

        // Animation tracks
        std::vector<AnimationTrack> tracks;

        // Animation state
        enum class State
        {
            Stopped,
            Playing,
            Paused,
            Finished
        };

        State state = State::Stopped;
        float currentTime = 0.0f;
        float normalizedTime = 0.0f; // 0.0 to 1.0
        uint32_t currentLoop = 0;

        // Events
        std::function<void(EntityId)> onStart;
        std::function<void(EntityId)> onComplete;
        std::function<void(EntityId, uint32_t)> onLoop;
        std::function<void(EntityId, float)> onUpdate;
    };

    struct AnimationGroup
    {
        std::string id;
        std::vector<std::string> animationIds;

        enum class PlayMode
        {
            Sequential, // Play animations one after another
            Parallel,   // Play all animations simultaneously
            Random      // Play animations in random order
        };

        PlayMode playMode = PlayMode::Parallel;
        bool loop = false;
        float delay = 0.0f;

        // Group state
        uint32_t currentAnimationIndex = 0;
        bool isPlaying = false;
    };

    // ============================================================================
    // Animation System Configuration
    // ============================================================================

    struct AnimationSystemConfig
    {
        // Performance settings
        uint32_t maxAnimationsPerEntity = 10;
        uint32_t maxActiveAnimations = 1000;
        float updateFrequency = 60.0f; // Updates per second
        bool enableInterpolation = true;

        // Quality settings
        bool enableSmoothing = true;
        float smoothingFactor = 0.1f;
        bool enableBlending = true;
        uint32_t maxBlendedAnimations = 4;

        // Optimization settings
        bool enableCulling = true;
        float cullingDistance = 200.0f;
        bool enableLOD = true;
        float lodNearDistance = 50.0f;
        float lodFarDistance = 150.0f;

        // Memory management
        bool useObjectPooling = true;
        uint32_t initialPoolSize = 500;
        uint32_t poolGrowthSize = 100;

        // Debug settings
        bool logAnimationEvents = false;
        bool validateKeyframes = true;
        bool enablePerformanceMetrics = true;
    };

    // ============================================================================
    // Main Animation System
    // ============================================================================

    class AnimationSystem : public System
    {
    public:
        explicit AnimationSystem(const AnimationSystemConfig &config = AnimationSystemConfig{});
        ~AnimationSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const AnimationSystemConfig &config);
        const AnimationSystemConfig &getConfig() const;

        // Animation management
        void createAnimation(const std::string &animationId, const Animation &animation);
        void removeAnimation(const std::string &animationId);
        bool hasAnimation(const std::string &animationId) const;
        Animation *getAnimation(const std::string &animationId);
        const Animation *getAnimation(const std::string &animationId) const;

        // Entity animation control
        void playAnimation(EntityId entityId, const std::string &animationId);
        void stopAnimation(EntityId entityId, const std::string &animationId);
        void pauseAnimation(EntityId entityId, const std::string &animationId);
        void resumeAnimation(EntityId entityId, const std::string &animationId);
        void stopAllAnimations(EntityId entityId);

        // Animation playback control
        void setAnimationTime(EntityId entityId, const std::string &animationId, float time);
        void setAnimationSpeed(EntityId entityId, const std::string &animationId, float speed);
        float getAnimationTime(EntityId entityId, const std::string &animationId) const;
        bool isAnimationPlaying(EntityId entityId, const std::string &animationId) const;

        // Animation groups
        void createAnimationGroup(const std::string &groupId, const AnimationGroup &group);
        void playAnimationGroup(EntityId entityId, const std::string &groupId);
        void stopAnimationGroup(EntityId entityId, const std::string &groupId);

        // Animation blending
        void blendAnimations(EntityId entityId, const std::vector<std::string> &animationIds,
                             const std::vector<float> &weights);
        void crossfadeAnimation(EntityId entityId, const std::string &fromAnimation,
                                const std::string &toAnimation, float duration);

        // Dynamic animation creation
        Animation createTransformAnimation(const std::string &id, const Math::float3 &startPos,
                                           const Math::float3 &endPos, float duration);
        Animation createRotationAnimation(const std::string &id, const Math::float4 &startRot,
                                          const Math::float4 &endRot, float duration);
        Animation createScaleAnimation(const std::string &id, const Math::float3 &startScale,
                                       const Math::float3 &endScale, float duration);
        Animation createOrbitalAnimation(const std::string &id, const Math::OrbitParams &params, float duration);
        Animation createColorAnimation(const std::string &id, const Math::float4 &startColor,
                                       const Math::float4 &endColor, float duration);

        // Scene integration
        void loadAnimationsFromScene(const SceneConfig::Scene &scene);
        void applyAnimationToEntity(EntityId entityId, const SceneConfig::Animation &sceneAnimation);

        // Performance monitoring
        uint32_t getActiveAnimationCount() const;
        uint32_t getTotalAnimationCount() const;
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
        // Internal Animation Management
        // ============================================================================

        struct EntityAnimationState
        {
            std::map<std::string, Animation> activeAnimations;
            std::map<std::string, AnimationGroup> activeGroups;
            std::vector<std::string> blendedAnimations;
            std::vector<float> blendWeights;

            // Transform accumulation for blending
            Math::float3 accumulatedPosition = {0.0f, 0.0f, 0.0f};
            Math::float4 accumulatedRotation = {0.0f, 0.0f, 0.0f, 1.0f};
            Math::float3 accumulatedScale = {1.0f, 1.0f, 1.0f};
            Math::float4 accumulatedColor = {1.0f, 1.0f, 1.0f, 1.0f};

            // Performance tracking
            float lastUpdateTime = 0.0f;
            uint32_t animationCount = 0;
        };

        AnimationSystemConfig config_;
        std::map<std::string, Animation> animationTemplates_;
        std::map<std::string, AnimationGroup> groupTemplates_;
        std::map<EntityId, EntityAnimationState> entityAnimations_;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Object pooling
        std::vector<Animation> animationPool_;
        std::vector<size_t> freeAnimationIndices_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateEntityAnimations(EntityId entityId, EntityAnimationState &state, float deltaTime);
        void updateAnimation(EntityId entityId, Animation &animation, float deltaTime);
        void updateAnimationGroup(EntityId entityId, AnimationGroup &group, float deltaTime);
        void applyAnimationBlending(EntityId entityId, EntityAnimationState &state);

        // ============================================================================
        // Animation Track Processing
        // ============================================================================

        void processTransformTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processColorTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processValueTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processOrbitalTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processCustomTrack(EntityId entityId, const AnimationTrack &track, float time);

        // ============================================================================
        // Keyframe Interpolation
        // ============================================================================

        AnimationKeyframe interpolateKeyframes(const AnimationKeyframe &a, const AnimationKeyframe &b,
                                               float t, AnimationTrack::Interpolation interpolation) const;

        // Interpolation methods
        float interpolateLinear(float a, float b, float t) const;
        float interpolateCubic(float a, float b, float ta, float tb, float t) const;
        float interpolateBezier(float a, float b, float control1, float control2, float t) const;
        float interpolateStep(float a, float b, float t) const;
        float interpolateSmooth(float a, float b, float t) const;

        // Vector interpolation
        Math::float3 interpolateVector3(const Math::float3 &a, const Math::float3 &b, float t,
                                        AnimationTrack::Interpolation interpolation) const;
        Math::float4 interpolateQuaternion(const Math::float4 &a, const Math::float4 &b, float t) const;
        Math::float4 interpolateColor(const Math::float4 &a, const Math::float4 &b, float t) const;

        // ============================================================================
        // Animation Evaluation
        // ============================================================================

        std::pair<const AnimationKeyframe *, const AnimationKeyframe *>
        findKeyframeInterval(const AnimationTrack &track, float time) const;
        float calculateInterpolationFactor(const AnimationKeyframe &a, const AnimationKeyframe &b, float time) const;
        AnimationKeyframe evaluateTrackAtTime(const AnimationTrack &track, float time) const;

        // ============================================================================
        // Entity Transform Application
        // ============================================================================

        void applyTransformToEntity(EntityId entityId, const Math::float3 &position,
                                    const Math::float4 &rotation, const Math::float3 &scale);
        void applyColorToEntity(EntityId entityId, const Math::float4 &color);
        void applyValueToEntity(EntityId entityId, const std::string &property, float value);

        // Transform component integration
        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float4 getEntityRotation(EntityId entityId) const;
        Math::float3 getEntityScale(EntityId entityId) const;
        void setEntityTransform(EntityId entityId, const Math::float3 &position,
                                const Math::float4 &rotation, const Math::float3 &scale);

        // ============================================================================
        // Animation Validation and Optimization
        // ============================================================================

        bool validateAnimation(const Animation &animation) const;
        bool validateAnimationTrack(const AnimationTrack &track) const;
        void optimizeAnimation(Animation &animation);
        void sortKeyframes(AnimationTrack &track);
        void removeRedundantKeyframes(AnimationTrack &track);

        // ============================================================================
        // Performance Optimization
        // ============================================================================

        bool shouldUpdateAnimation(EntityId entityId, const Animation &animation) const;
        float calculateLODFactor(EntityId entityId) const;
        void cullDistantAnimations();
        void updatePerformanceCounters(float deltaTime);

        // Object pooling
        Animation *acquireAnimation();
        void releaseAnimation(Animation *animation);
        void expandAnimationPool();

        // ============================================================================
        // Event Handling
        // ============================================================================

        void triggerAnimationEvent(EntityId entityId, const Animation &animation, const std::string &eventType);
        void onAnimationStart(EntityId entityId, const Animation &animation);
        void onAnimationComplete(EntityId entityId, const Animation &animation);
        void onAnimationLoop(EntityId entityId, const Animation &animation, uint32_t loopCount);
        void onAnimationUpdate(EntityId entityId, const Animation &animation, float time);

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderAnimationDebugInfo(EntityId entityId, const EntityAnimationState &state);
        void logAnimationStatistics() const;
        void validateAnimationState() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline uint32_t AnimationSystem::getActiveAnimationCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, state] : entityAnimations_)
        {
            total += state.animationCount;
        }
        return total;
    }

    inline uint32_t AnimationSystem::getTotalAnimationCount() const
    {
        return static_cast<uint32_t>(animationTemplates_.size());
    }

    inline float AnimationSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool AnimationSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void AnimationSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const AnimationSystemConfig &AnimationSystem::getConfig() const
    {
        return config_;
    }

    inline bool AnimationSystem::hasAnimation(const std::string &animationId) const
    {
        return animationTemplates_.find(animationId) != animationTemplates_.end();
    }

    inline Animation *AnimationSystem::getAnimation(const std::string &animationId)
    {
        auto it = animationTemplates_.find(animationId);
        return (it != animationTemplates_.end()) ? &it->second : nullptr;
    }

    inline const Animation *AnimationSystem::getAnimation(const std::string &animationId) const
    {
        auto it = animationTemplates_.find(animationId);
        return (it != animationTemplates_.end()) ? &it->second : nullptr;
    }

    inline float AnimationSystem::interpolateLinear(float a, float b, float t) const
    {
        return a + t * (b - a);
    }

    inline float AnimationSystem::interpolateStep(float a, float b, float t) const
    {
        return (t < 1.0f) ? a : b;
    }

    inline float AnimationSystem::interpolateSmooth(float a, float b, float t) const
    {
        // Smoothstep interpolation
        t = t * t * (3.0f - 2.0f * t);
        return interpolateLinear(a, b, t);
    }

} // namespace ECS

