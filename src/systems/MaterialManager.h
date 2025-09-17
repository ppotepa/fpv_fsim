#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "../math/MathUtils.h"
#include "../generators/ProceduralTextureGenerator.h"
#include "../core/AssetIds.h"

// MaterialManager uses string-based IDs internally but should convert to numeric AssetIds for registry
using MaterialId = std::string;

namespace Material
{
    // Core material properties for cel-shading and PBR workflows
    struct MaterialProperties
    {
        // Cel-shading properties
        Math::float3 albedo = {1.0f, 1.0f, 1.0f};
        Math::float3 emission = {0.0f, 0.0f, 0.0f};
        float metallic = 0.0f;
        float roughness = 0.5f;
        float rimPower = 2.0f;
        float rimStrength = 1.0f;
        Math::float3 rimColor = {1.0f, 1.0f, 1.0f};

        // Texture asset IDs
        std::string albedoTexture;
        std::string normalTexture;
        std::string metallicTexture;
        std::string roughnessTexture;
        std::string emissionTexture;

        // Cel-shading specific
        int toonSteps = 4;
        float toonThreshold = 0.5f;
        bool enableRimLighting = true;
        bool enableOutlines = false;
        float outlineWidth = 0.02f;
        Math::float3 outlineColor = {0.0f, 0.0f, 0.0f};

        // Animation properties
        bool isAnimated = false;
        float animationSpeed = 1.0f;
        std::string animationType = "none"; // "scroll", "rotate", "pulse", "wave"
    };

    // Material definition combining properties and metadata
    struct Material
    {
        std::string name;
        std::string type; // "standard", "earth", "atmosphere", "cloud", "contrail"
        MaterialProperties properties;
        bool isDynamic = false; // Whether textures are generated at runtime

        Material() = default;
        Material(const std::string &materialName, const std::string &materialType)
            : name(materialName), type(materialType) {}
    };

    // Material manager for dynamic loading and cel-shading setup
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager() = default;

        // Core material management
        bool LoadMaterial(const std::string &materialId, const Material &material);
        std::optional<Material> GetMaterial(const std::string &materialId) const;
        bool HasMaterial(const std::string &materialId) const;

        // Dynamic material creation
        std::string CreateDynamicMaterial(const std::string &baseType, const MaterialProperties &properties);
        std::string CreateEarthMaterial(float radius, int detailLevel = 1);
        std::string CreateAtmosphereMaterial(int layer = 0, float density = 0.1f);
        std::string CreateCloudMaterial(float coverage = 0.6f, float density = 0.3f);
        std::string CreateContrailMaterial(const Math::float3 &color = {1.0f, 1.0f, 1.0f});

        // Cel-shading configuration
        void SetGlobalCelShadingParams(int toonSteps, float threshold, bool enableRim);
        void EnableOutlinesForMaterial(const std::string &materialId, float width, const Math::float3 &color);
        void SetMaterialAnimation(const std::string &materialId, const std::string &animType, float speed);

        // Texture integration (internal use only)
        void SetTextureGenerator(const ProceduralTexture::ProceduralTextureGenerator *generator);
        MaterialId GenerateAndAssignTexture(const std::string &materialId, const std::string &textureType);

        // Bulk operations
        bool LoadMaterialsFromFile(const std::string &filePath);
        void LoadDefaultMaterials(); // Deprecated - use LoadMaterialsFromFile
        void ClearAllMaterials();
        size_t GetMaterialCount() const;

        // Debugging and validation
        std::vector<std::string> GetAllMaterialIds() const;
        bool ValidateMaterial(const std::string &materialId) const;
        void PrintMaterialInfo(const std::string &materialId) const;

    private:
        std::unordered_map<std::string, Material> materials_;
        const ProceduralTexture::ProceduralTextureGenerator *textureGenerator_;

        // Global cel-shading settings
        int globalToonSteps_ = 4;
        float globalToonThreshold_ = 0.5f;
        bool globalRimLighting_ = true;

        // Helper methods
        std::string GenerateUniqueMaterialId(const std::string &baseType);
        MaterialProperties CreateBaseProperties(const std::string &materialType);
        void ApplyGlobalCelShadingSettings(MaterialProperties &properties);

        // Material type creators
        MaterialProperties CreateEarthProperties(float radius, int detailLevel);
        MaterialProperties CreateAtmosphereProperties(int layer, float density);
        MaterialProperties CreateCloudProperties(float coverage, float density);
        MaterialProperties CreateContrailProperties(const Math::float3 &color);

        // Material loading methods
        bool LoadMaterialsFromJsonPackages();

        // Texture assignment helpers
        void AssignEarthTextures(MaterialProperties &properties, float radius, int detailLevel);
        void AssignAtmosphereTextures(MaterialProperties &properties, int layer);
        void AssignCloudTextures(MaterialProperties &properties, float coverage);
        void AssignContrailTextures(MaterialProperties &properties);
    };
}
