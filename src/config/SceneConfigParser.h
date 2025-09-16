#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <optional>
#include <cstdint>

// Forward declarations for ECS components
namespace ECS
{
    class Entity;
    class World;
}

namespace SceneConfig
{

    // ============================================================================
    // Scene Data Structures
    // ============================================================================

    struct Transform
    {
        struct Position
        {
            float x, y, z;
        };
        struct Rotation
        {
            float x, y, z, w;
        }; // Quaternion
        struct Scale
        {
            float x, y, z;
        };

        Position position = {0.0f, 0.0f, 0.0f};
        Rotation rotation = {0.0f, 0.0f, 0.0f, 1.0f};
        Scale scale = {1.0f, 1.0f, 1.0f};
    };

    struct VoxelPrimitive
    {
        enum class Type
        {
            Cube,
            Sphere,
            Cylinder,
            Plane
        };

        Type type = Type::Cube;
        float size = 1.0f;
        float radius = 0.5f;
        float height = 1.0f;
        uint32_t subdivisions = 1;
        Transform transform;
        std::string materialId;

        // Animation properties
        bool animated = false;
        std::string animationType;
        std::map<std::string, std::string> animationParams;
    };

    struct CompoundMesh
    {
        std::string id;
        std::string name;
        std::vector<VoxelPrimitive> parts;
        Transform baseTransform;
        std::string materialId;

        // Animation properties
        bool animated = false;
        std::string animationType;
        std::map<std::string, std::string> animationParams;
    };

    struct Material
    {
        std::string id;
        std::string name;
        std::string shader = "standard";

        // Basic material properties
        struct Color
        {
            float r, g, b, a;
        };
        Color diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        Color ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        Color specular = {1.0f, 1.0f, 1.0f, 1.0f};
        Color emissive = {0.0f, 0.0f, 0.0f, 1.0f};

        float metallic = 0.0f;
        float roughness = 0.5f;
        float shininess = 32.0f;
        float opacity = 1.0f;

        // Texture references
        std::string diffuseTexture;
        std::string normalTexture;
        std::string specularTexture;
        std::string emissiveTexture;

        // Cel-shading specific
        bool celShading = false;
        uint32_t celLevels = 3;
        float celThreshold = 0.5f;
        Color celOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        float celOutlineWidth = 0.01f;

        // Additional properties
        std::map<std::string, std::string> customProperties;
    };

    struct ProceduralTexture
    {
        std::string id;
        std::string name;
        std::string type; // "noise", "gradient", "pattern", "composite"
        uint32_t width = 256;
        uint32_t height = 256;
        std::string format = "RGBA";

        // Generation parameters
        std::map<std::string, std::string> parameters;
    };

    struct Animation
    {
        std::string id;
        std::string name;
        std::string type; // "orbital", "rotation", "scale", "transform", "compound"
        float duration = 1.0f;
        bool loop = true;
        bool autoStart = true;

        // Target specification
        std::string targetType; // "entity", "component", "material"
        std::string targetId;

        // Animation parameters
        std::map<std::string, std::string> parameters;

        // Keyframes (optional, for complex animations)
        struct Keyframe
        {
            float time;
            std::map<std::string, std::string> values;
        };
        std::vector<Keyframe> keyframes;
    };

    struct Camera
    {
        std::string id = "main_camera";
        Transform transform;

        enum class Type
        {
            Perspective,
            Orthographic
        };
        Type type = Type::Perspective;

        // Perspective parameters
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;

        // Orthographic parameters
        float left = -10.0f, right = 10.0f;
        float bottom = -10.0f, top = 10.0f;

        // Animation
        bool animated = false;
        std::string animationId;
    };

    struct Light
    {
        std::string id;
        std::string name;

        enum class Type
        {
            Directional,
            Point,
            Spot,
            Ambient
        };
        Type type = Type::Directional;

        Transform transform;
        Material::Color color = {1.0f, 1.0f, 1.0f, 1.0f};
        float intensity = 1.0f;

        // Point/Spot light parameters
        float range = 10.0f;
        float constantAttenuation = 1.0f;
        float linearAttenuation = 0.09f;
        float quadraticAttenuation = 0.032f;

        // Spot light parameters
        float innerCone = 30.0f; // degrees
        float outerCone = 45.0f; // degrees

        // Animation
        bool animated = false;
        std::string animationId;
    };

    struct Entity
    {
        std::string id;
        std::string name;
        std::string type; // "mesh", "light", "camera", "compound"
        Transform transform;

        // Component references
        std::string meshId;
        std::string materialId;
        std::string lightId;
        std::string cameraId;

        // Animation
        bool animated = false;
        std::string animationId;

        // Custom properties for specific entity types
        std::map<std::string, std::string> properties;

        // Child entities (for hierarchical scenes)
        std::vector<std::shared_ptr<Entity>> children;
    };

    struct Scene
    {
        std::string id;
        std::string name;
        std::string type; // "loading_indicator", "menu_background", etc.
        std::string version = "1.0";

        // Scene assets
        std::vector<Material> materials;
        std::vector<ProceduralTexture> textures;
        std::vector<CompoundMesh> meshes;
        std::vector<Animation> animations;

        // Scene graph
        std::vector<Camera> cameras;
        std::vector<Light> lights;
        std::vector<std::shared_ptr<Entity>> rootEntities;

        // Environment settings
        Material::Color backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
        Material::Color ambientLight = {0.2f, 0.2f, 0.2f, 1.0f};
        std::string skybox;

        // Rendering settings
        bool enableShadows = true;
        bool enableBloom = false;
        bool enableSSAO = false;
        float gamma = 2.2f;
        float exposure = 1.0f;

        // Scene metadata
        std::map<std::string, std::string> metadata;
    };

    // ============================================================================
    // Parser Configuration and Validation
    // ============================================================================

    struct ParserConfig
    {
        std::string schemaPath; // Path to scene.xsd for validation
        bool validateSchema = true;
        bool strictParsing = false;     // If true, fail on unknown elements
        bool generateMissingIds = true; // Auto-generate IDs if missing
        bool loadExternalAssets = true; // Load referenced external files

        // Default values for missing required fields
        std::string defaultMaterial = "default_material";
        std::string defaultTexture = "default_texture";
        uint32_t defaultSubdivisions = 1;
    };

    struct ParseResult
    {
        bool success = false;
        std::string errorMessage;
        std::vector<std::string> warnings;
        std::shared_ptr<Scene> scene;

        // Parse statistics
        uint32_t entitiesLoaded = 0;
        uint32_t materialsLoaded = 0;
        uint32_t texturesLoaded = 0;
        uint32_t animationsLoaded = 0;
        float parseTimeMs = 0.0f;
    };

    // ============================================================================
    // Main Scene Configuration Parser
    // ============================================================================

    class SceneConfigParser
    {
    public:
        // Construction and configuration
        explicit SceneConfigParser(const ParserConfig &config = ParserConfig{});
        ~SceneConfigParser() = default;

        // Main parsing methods
        ParseResult parseSceneFile(const std::string &filePath);
        ParseResult parseSceneString(const std::string &xmlContent);
        ParseResult parseSceneData(const void *xmlData, size_t dataSize);

        // Enhanced XML-based scene loading
        ParseResult loadXmlScene(const std::string &sceneId);

        // Validation methods
        bool validateSceneFile(const std::string &filePath, std::vector<std::string> &errors);
        bool validateSceneString(const std::string &xmlContent, std::vector<std::string> &errors);
        bool validateAgainstSchema(const std::string &xmlContent, std::vector<std::string> &errors);

        // Configuration management
        void setConfig(const ParserConfig &config);
        const ParserConfig &getConfig() const;

        // Utility methods for manual scene construction
        static std::shared_ptr<Entity> createEntity(const std::string &id, const std::string &type);
        static Material createMaterial(const std::string &id, const std::string &shader = "standard");
        static ProceduralTexture createTexture(const std::string &id, const std::string &type);
        static Animation createAnimation(const std::string &id, const std::string &type);
        static Camera createCamera(const std::string &id);
        static Light createLight(const std::string &id, Light::Type type);

        // Scene export methods (for debugging/serialization)
        std::string serializeScene(const Scene &scene, bool prettyPrint = true);
        bool exportSceneToFile(const Scene &scene, const std::string &filePath);

        // Asset resolution and validation
        std::vector<std::string> getReferencedAssets(const Scene &scene);
        std::vector<std::string> validateAssetReferences(const Scene &scene);
        bool resolveAssetPaths(Scene &scene, const std::string &baseDirectory);

    private:
        ParserConfig config_;

        // XML parsing implementation
        ParseResult parseXmlDocument(const std::string &xmlContent);

        // Element parsing methods
        std::shared_ptr<Scene> parseSceneElement(const void *sceneNode);
        Material parseMaterialElement(const void *materialNode);
        ProceduralTexture parseTextureElement(const void *textureNode);
        CompoundMesh parseMeshElement(const void *meshNode);
        Animation parseAnimationElement(const void *animationNode);
        Camera parseCameraElement(const void *cameraNode);
        Light parseLightElement(const void *lightNode);
        std::shared_ptr<Entity> parseEntityElement(const void *entityNode);
        VoxelPrimitive parsePrimitiveElement(const void *primitiveNode);
        Transform parseTransformElement(const void *transformNode);

        // Attribute parsing helpers
        std::string parseStringAttribute(const void *node, const std::string &name, const std::string &defaultValue = "");
        float parseFloatAttribute(const void *node, const std::string &name, float defaultValue = 0.0f);
        uint32_t parseUintAttribute(const void *node, const std::string &name, uint32_t defaultValue = 0);
        bool parseBoolAttribute(const void *node, const std::string &name, bool defaultValue = false);
        Material::Color parseColorAttribute(const void *node, const std::string &name, const Material::Color &defaultValue = {1, 1, 1, 1});

        // Complex attribute parsing
        std::map<std::string, std::string> parseParameters(const void *parametersNode);
        std::vector<Animation::Keyframe> parseKeyframes(const void *keyframesNode);

        // Validation helpers
        bool validateSceneStructure(const Scene &scene, std::vector<std::string> &errors);
        bool validateEntityReferences(const Scene &scene, std::vector<std::string> &errors);
        bool validateAnimationTargets(const Scene &scene, std::vector<std::string> &errors);
        bool validateMaterialReferences(const Scene &scene, std::vector<std::string> &errors);

        // ID generation and management
        std::string generateEntityId(const std::string &type, uint32_t index);
        std::string generateMaterialId(uint32_t index);
        std::string generateTextureId(uint32_t index);
        std::string generateAnimationId(uint32_t index);
        bool isValidId(const std::string &id);

        // Error handling and logging
        void addError(const std::string &message);
        void addWarning(const std::string &message);
        void logParseStep(const std::string &step);

        // Current parse state
        ParseResult currentResult_;
        std::map<std::string, std::shared_ptr<Entity>> entityLookup_;
        std::map<std::string, Material> materialLookup_;
        std::map<std::string, ProceduralTexture> textureLookup_;
        std::map<std::string, Animation> animationLookup_;

        // Simplified parsing helpers
        std::string extractAttributeSimple(const std::string &xmlContent,
                                           const std::string &elementName,
                                           const std::string &attributeName,
                                           const std::string &defaultValue);

        // XML validation helpers
        bool validateXmlStructure(const std::string &xmlContent);
        bool isWellFormedXml(const std::string &xmlContent);

        // Parse counters for ID generation
        uint32_t entityCounter_ = 0;
        uint32_t materialCounter_ = 0;
        uint32_t textureCounter_ = 0;
        uint32_t animationCounter_ = 0;
    };

    // ============================================================================
    // Utility Functions
    // ============================================================================

    namespace Utils
    {
        // String conversion utilities
        VoxelPrimitive::Type stringToVoxelType(const std::string &str);
        std::string voxelTypeToString(VoxelPrimitive::Type type);

        Light::Type stringToLightType(const std::string &str);
        std::string lightTypeToString(Light::Type type);

        Camera::Type stringToCameraType(const std::string &str);
        std::string cameraTypeToString(Camera::Type type);

        // Transform utilities
        Transform combineTransforms(const Transform &parent, const Transform &child);
        Transform interpolateTransforms(const Transform &a, const Transform &b, float t);

        // Color utilities
        Material::Color parseColorString(const std::string &colorStr);
        std::string colorToString(const Material::Color &color);
        Material::Color interpolateColors(const Material::Color &a, const Material::Color &b, float t);

        // Validation utilities
        bool isValidFloat(const std::string &str);
        bool isValidColor(const std::string &str);
        bool isValidId(const std::string &id);
        bool isValidPath(const std::string &path);

        // Math utilities
        float degreesToRadians(float degrees);
        float radiansToDegrees(float radians);
        void normalizeQuaternion(Transform::Rotation &quat);

        // File utilities
        std::string getFileExtension(const std::string &path);
        std::string getBasePath(const std::string &path);
        std::string resolvePath(const std::string &basePath, const std::string &relativePath);
        bool fileExists(const std::string &path);
    }

} // namespace SceneConfig
