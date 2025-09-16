#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>

namespace Assets {

// Forward declarations
class Asset;
class Scene;
class Entity;

// Asset types enumeration
enum class AssetType {
    Material,
    Mesh,
    Texture,
    Shader,
    Audio,
    Scene
};

// Asset identification
using AssetId = uint64_t;
using SceneId = uint32_t;
using EntityId = uint32_t;

// Package dependency information
struct PackageDependency {
    std::string packageId;
    std::string version;
    bool required = true;
};

// Package metadata
struct PackageMetadata {
    std::string id;
    std::string name;
    std::string version;
    std::string description;
    std::string author;
    std::vector<PackageDependency> dependencies;
};

// Asset definition data structures
struct MaterialAssetData {
    std::string shaderReference;
    std::unordered_map<std::string, std::string> textureReferences;
    std::unordered_map<std::string, std::string> properties;
};

struct MeshAssetData {
    std::string sourcePath;
    bool optimize = true;
    bool generateTangents = false;
    int optimizationLevel = 1;
};

struct TextureAssetData {
    std::string sourcePath;
    bool generateMipmaps = true;
    std::string compressionFormat = "auto";
    int compressionQuality = 85;
};

struct ShaderAssetData {
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string geometryShaderPath; // Optional
    std::vector<std::string> defines;
};

struct AudioAssetData {
    std::string sourcePath;
    bool compressed = true;
    int sampleRate = 44100;
    int bitDepth = 16;
};

// Asset definition
struct AssetDefinition {
    std::string id;
    AssetType type;
    std::variant<MaterialAssetData, MeshAssetData, TextureAssetData, 
                ShaderAssetData, AudioAssetData> data;
    uint64_t sourceHash = 0;
};

// Component definitions
enum class ComponentType {
    Transform,
    Mesh,
    Material,
    Renderable,
    Physics,
    Audio,
    Behavior
};

struct MeshComponent {
    std::string assetRef;
};

struct MaterialComponent {
    std::string assetRef;
};

struct RenderableComponent {
    bool visible = true;
    bool castShadows = true;
    bool receiveShadows = true;
    float lodBias = 1.0f;
};

struct PhysicsComponent {
    float mass = 1.0f;
    float friction = 0.8f;
    float restitution = 0.2f;
    bool isStatic = false;
    struct { float x, y, z; } centerOfMass = {0, 0, 0};
};

struct AudioComponent {
    std::string assetRef;
    bool autoPlay = false;
    bool loop = false;
    float volume = 1.0f;
    float pitch = 1.0f;
};

// Transform data
struct Transform {
    struct { float x, y, z; } position = {0, 0, 0};
    struct { float x, y, z, w; } rotation = {0, 0, 0, 1}; // Quaternion
    struct { float x, y, z; } scale = {1, 1, 1};
};

// Component definition
struct Component {
    ComponentType type;
    std::variant<MeshComponent, MaterialComponent, RenderableComponent,
                PhysicsComponent, AudioComponent> data;
};

// Behavior parameters
class BehaviorParams {
public:
    void setParameter(const std::string& name, const std::string& value) {
        parameters[name] = value;
    }
    
    template<typename T>
    T get(const std::string& name, const T& defaultValue = T{}) const;
    
    float getFloat(const std::string& name, float defaultValue = 0.0f) const;
    int getInt(const std::string& name, int defaultValue = 0) const;
    bool getBool(const std::string& name, bool defaultValue = false) const;
    std::string getString(const std::string& name, const std::string& defaultValue = "") const;
    
    // Vector types
    struct Vector3 { float x, y, z; };
    struct Vector2 { float x, y; };
    struct Color { float r, g, b, a; };
    
    Vector3 getVector3(const std::string& name, const Vector3& defaultValue = {0, 0, 0}) const;
    Vector2 getVector2(const std::string& name, const Vector2& defaultValue = {0, 0}) const;
    Color getColor(const std::string& name, const Color& defaultValue = {1, 1, 1, 1}) const;

private:
    std::unordered_map<std::string, std::string> parameters;
};

// Entity definition
struct EntityDefinition {
    std::string id;
    std::string name;
    Transform transform;
    std::vector<Component> components;
    std::string behaviorClass;
    BehaviorParams behaviorParams;
};

// Scene definition
struct SceneDefinition {
    std::string id;
    std::string name;
    std::vector<EntityDefinition> entities;
};

// Main package structure
struct Package {
    PackageMetadata metadata;
    std::vector<AssetDefinition> assets;
    std::vector<SceneDefinition> scenes;
    std::string sourcePath;
    
    // Utility methods
    const AssetDefinition* findAsset(const std::string& assetId) const {
        for (const auto& asset : assets) {
            if (asset.id == assetId) {
                return &asset;
            }
        }
        return nullptr;
    }
    
    const SceneDefinition* findScene(const std::string& sceneId) const {
        for (const auto& scene : scenes) {
            if (scene.id == sceneId) {
                return &scene;
            }
        }
        return nullptr;
    }
};

// Asset ID generation utilities
class AssetIdGenerator {
public:
    static AssetId generateAssetId(const std::string& packageId, const std::string& assetId);
    static SceneId generateSceneId(const std::string& packageId, const std::string& sceneId);
    static EntityId generateEntityId(const std::string& sceneId, const std::string& entityId);

private:
    static uint64_t fnv1a_hash(const std::string& str);
};

} // namespace Assets
