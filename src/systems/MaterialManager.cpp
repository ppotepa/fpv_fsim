#include "MaterialManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "../debug.h"
#include "../assets/PackageManager.h"
#include "../platform/NlohmannJsonParser.h"

namespace Material
{
    MaterialManager::MaterialManager()
        : textureGenerator_(nullptr)
    {
        DEBUG_LOG("MaterialManager initialized");
    }

    bool MaterialManager::LoadMaterial(const std::string &materialId, const Material &material)
    {
        if (materialId.empty())
        {
            std::cerr << "Error: Cannot load material with empty ID" << std::endl;
            return false;
        }

        if (HasMaterial(materialId))
        {
            DEBUG_LOG("Warning: Overwriting existing material: " << materialId);
        }

        materials_[materialId] = material;

        // Apply global cel-shading settings if not specifically set
        if (materials_[materialId].properties.toonSteps == 4)
        {
            ApplyGlobalCelShadingSettings(materials_[materialId].properties);
        }

        DEBUG_LOG("Loaded material: " << materialId << " (type: " << material.type << ")");
        return true;
    }

    std::optional<Material> MaterialManager::GetMaterial(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            return it->second;
        }
        return std::nullopt;
    }

    bool MaterialManager::HasMaterial(const std::string &materialId) const
    {
        return materials_.find(materialId) != materials_.end();
    }

    std::string MaterialManager::CreateDynamicMaterial(const std::string &baseType, const MaterialProperties &properties)
    {
        std::string materialId = GenerateUniqueMaterialId(baseType);

        Material material(materialId, baseType);
        material.properties = properties;
        material.isDynamic = true;

        ApplyGlobalCelShadingSettings(material.properties);

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateEarthMaterial(float radius, int detailLevel)
    {
        std::string materialId = GenerateUniqueMaterialId("earth");

        Material material(materialId, "earth");
        material.properties = CreateEarthProperties(radius, detailLevel);
        material.isDynamic = true;

        // Generate and assign textures if texture generator is available
        if (textureGenerator_)
        {
            AssignEarthTextures(material.properties, radius, detailLevel);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateAtmosphereMaterial(int layer, float density)
    {
        std::string materialId = GenerateUniqueMaterialId("atmosphere");

        Material material(materialId, "atmosphere");
        material.properties = CreateAtmosphereProperties(layer, density);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignAtmosphereTextures(material.properties, layer);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateCloudMaterial(float coverage, float density)
    {
        std::string materialId = GenerateUniqueMaterialId("cloud");

        Material material(materialId, "cloud");
        material.properties = CreateCloudProperties(coverage, density);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignCloudTextures(material.properties, coverage);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateContrailMaterial(const Math::float3 &color)
    {
        std::string materialId = GenerateUniqueMaterialId("contrail");

        Material material(materialId, "contrail");
        material.properties = CreateContrailProperties(color);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignContrailTextures(material.properties);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    void MaterialManager::SetGlobalCelShadingParams(int toonSteps, float threshold, bool enableRim)
    {
        globalToonSteps_ = std::max(1, std::min(toonSteps, 16));
        globalToonThreshold_ = std::max(0.0f, std::min(threshold, 1.0f));
        globalRimLighting_ = enableRim;

        DEBUG_LOG("Updated global cel-shading: " << globalToonSteps_ << " steps, "
                                                 << globalToonThreshold_ << " threshold, rim: " << (globalRimLighting_ ? "enabled" : "disabled"));
    }

    void MaterialManager::EnableOutlinesForMaterial(const std::string &materialId, float width, const Math::float3 &color)
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            it->second.properties.enableOutlines = true;
            it->second.properties.outlineWidth = std::max(0.001f, std::min(width, 0.1f));
            it->second.properties.outlineColor = color;
            DEBUG_LOG("Enabled outlines for material: " << materialId);
        }
        else
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
        }
    }

    void MaterialManager::SetMaterialAnimation(const std::string &materialId, const std::string &animType, float speed)
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            it->second.properties.isAnimated = true;
            it->second.properties.animationType = animType;
            it->second.properties.animationSpeed = std::max(0.1f, std::min(speed, 10.0f));
            DEBUG_LOG("Set animation for material: " << materialId << " (" << animType << ", speed: " << speed << ")");
        }
        else
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
        }
    }

    void MaterialManager::SetTextureGenerator(const ProceduralTexture::ProceduralTextureGenerator *generator)
    {
        textureGenerator_ = generator;
        DEBUG_LOG("Texture generator assigned to MaterialManager");
    }

    MaterialId MaterialManager::GenerateAndAssignTexture(const std::string &materialId, const std::string &textureType)
    {
        if (!textureGenerator_)
        {
            std::cerr << "Error: No texture generator available" << std::endl;
            return "";
        }

        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
            return "";
        }

        // Create texture parameters based on material type and texture type
        ProceduralTexture::TextureParams params;
        params.width = 512;
        params.height = 512;
        params.name = materialId + "_" + textureType;

        if (it->second.type == "earth")
        {
            if (textureType == "albedo")
            {
                params.type = ProceduralTexture::TextureParams::Type::Noise;
                params.noise.type = ProceduralTexture::NoiseParams::Type::Perlin;
                params.noise.frequency = 0.01f;
                params.noise.octaves = 4;
            }
            else if (textureType == "normal")
            {
                params.type = ProceduralTexture::TextureParams::Type::Noise;
                params.noise.type = ProceduralTexture::NoiseParams::Type::Simplex;
                params.noise.frequency = 0.005f;
                params.noise.octaves = 3;
            }
        }
        else if (it->second.type == "atmosphere")
        {
            params.type = ProceduralTexture::TextureParams::Type::Gradient;
            params.gradient.type = ProceduralTexture::GradientParams::Type::Linear;
        }
        else if (it->second.type == "cloud")
        {
            params.type = ProceduralTexture::TextureParams::Type::Noise;
            params.noise.type = ProceduralTexture::NoiseParams::Type::Perlin;
            params.noise.frequency = 0.02f;
            params.noise.octaves = 4;
        }

        // Generate the texture (for now just return the name as AssetId)
        // In a real implementation, this would generate the texture and register it in an asset system
        MaterialId textureId = params.name + "_generated";

        if (!textureId.empty())
        {
            // Assign to material
            if (textureType == "albedo")
            {
                it->second.properties.albedoTexture = textureId;
            }
            else if (textureType == "normal")
            {
                it->second.properties.normalTexture = textureId;
            }
            else if (textureType == "emission")
            {
                it->second.properties.emissionTexture = textureId;
            }

            DEBUG_LOG("Generated and assigned " << textureType << " texture to material: " << materialId);
        }

        return textureId;
    }

    void MaterialManager::LoadDefaultMaterials()
    {
        DEBUG_LOG("Loading default materials...");

        // Load materials from the JSON packages
        if (LoadMaterialsFromJsonPackages())
        {
            DEBUG_LOG("Default materials loaded successfully");
            return;
        }

        // Fallback to hardcoded materials if file loading fails
        std::cerr << "Failed to load materials from JSON packages, using hardcoded defaults" << std::endl;

        // Default Earth material (blue)
        Material earthMaterial("EarthSurfaceMaterial", "earth");
        earthMaterial.properties.albedo = {0.2f, 0.4f, 0.9f}; // Blue earth
        earthMaterial.properties.roughness = 0.8f;
        earthMaterial.properties.metallic = 0.0f;
        earthMaterial.properties.toonSteps = 6;
        earthMaterial.properties.enableRimLighting = true;
        earthMaterial.properties.rimColor = {0.8f, 0.9f, 1.0f};
        LoadMaterial("EarthSurfaceMaterial", earthMaterial);

        // Default atmosphere material
        Material atmosphereMaterial("AtmosphereMaterial", "atmosphere");
        atmosphereMaterial.properties.albedo = {0.5f, 0.7f, 1.0f};
        atmosphereMaterial.properties.roughness = 0.0f;
        atmosphereMaterial.properties.metallic = 0.0f;
        atmosphereMaterial.properties.toonSteps = 3;
        atmosphereMaterial.properties.enableRimLighting = true;
        atmosphereMaterial.properties.rimStrength = 2.0f;
        LoadMaterial("AtmosphereMaterial", atmosphereMaterial);

        // Default cloud material
        Material cloudMaterial("CloudMaterial", "cloud");
        cloudMaterial.properties.albedo = {1.0f, 1.0f, 1.0f};
        cloudMaterial.properties.roughness = 0.1f;
        cloudMaterial.properties.toonSteps = 4;
        cloudMaterial.properties.isAnimated = true;
        cloudMaterial.properties.animationType = "scroll";
        cloudMaterial.properties.animationSpeed = 0.5f;
        LoadMaterial("CloudMaterial", cloudMaterial);

        // Default contrail material
        Material contrailMaterial("ContrailMaterial", "contrail");
        contrailMaterial.properties.albedo = {1.0f, 1.0f, 1.0f};
        contrailMaterial.properties.emission = {0.1f, 0.1f, 0.1f};
        contrailMaterial.properties.roughness = 0.0f;
        contrailMaterial.properties.toonSteps = 2;
        contrailMaterial.properties.isAnimated = true;
        contrailMaterial.properties.animationType = "wave";
        LoadMaterial("ContrailMaterial", contrailMaterial);

        DEBUG_LOG("Hardcoded default materials loaded");
    }

    bool MaterialManager::LoadMaterialsFromJsonPackages()
    {
        DEBUG_LOG("Loading materials from JSON packages...");
        
        // Direct JSON loading approach to properly parse color objects
        std::string packagePath = "assets/packages/core/package.json";
        
        try {
            // Use NlohmannJsonParser to load the JSON file
            NlohmannJsonParser jsonParser;
            if (!jsonParser.loadFile(packagePath))
            {
                DEBUG_LOG("Failed to load package file: " + packagePath);
                return false;
            }
            
            const auto& rootJson = jsonParser.getRootJson();
            
            if (!rootJson.contains("assets") || !rootJson["assets"].contains("materials"))
            {
                DEBUG_LOG("No materials section found in package");
                return false;
            }
            
            const auto& materials = rootJson["assets"]["materials"];
            if (!materials.is_array())
            {
                DEBUG_LOG("Materials section is not an array");
                return false;
            }
            
            size_t materialsLoaded = 0;
            
            // Process each material in the JSON
            for (const auto& materialJson : materials)
            {
                if (!materialJson.contains("id"))
                {
                    DEBUG_LOG("Material missing ID, skipping");
                    continue;
                }
                
                std::string materialId = materialJson["id"].get<std::string>();
                
                // Create Material
                Material material(materialId, "json_material");
                
                // Set default properties
                material.properties.albedo = {0.8f, 0.8f, 0.8f}; // Default gray
                material.properties.roughness = 0.5f;
                material.properties.metallic = 0.0f;
                material.properties.toonSteps = 4;
                
                // Parse diffuseColor if present
                if (materialJson.contains("diffuseColor") && materialJson["diffuseColor"].is_object())
                {
                    const auto& color = materialJson["diffuseColor"];
                    if (color.contains("r") && color.contains("g") && color.contains("b"))
                    {
                        material.properties.albedo.x = color["r"].get<float>();
                        material.properties.albedo.y = color["g"].get<float>();
                        material.properties.albedo.z = color["b"].get<float>();
                    }
                }
                
                // Parse other material properties
                if (materialJson.contains("shininess"))
                {
                    float shininess = materialJson["shininess"].get<float>();
                    // Convert shininess to roughness (inverse relationship)
                    material.properties.roughness = 1.0f - std::min(1.0f, shininess / 128.0f);
                }
                
                material.isDynamic = false;
                ApplyGlobalCelShadingSettings(material.properties);
                
                if (LoadMaterial(materialId, material))
                {
                    materialsLoaded++;
                    DEBUG_LOG("Loaded material: " + materialId + 
                             " (albedo: " + std::to_string(material.properties.albedo.x) + ", " +
                             std::to_string(material.properties.albedo.y) + ", " +
                             std::to_string(material.properties.albedo.z) + ")");
                }
                else
                {
                    DEBUG_LOG("Failed to load material: " + materialId);
                }
            }
            
            if (materialsLoaded > 0)
            {
                DEBUG_LOG("Successfully loaded " + std::to_string(materialsLoaded) + " materials from JSON packages");
                return true;
            }
            
            DEBUG_LOG("No materials processed from JSON packages");
            return false;
            
        } catch (const std::exception& e) {
            DEBUG_LOG("Exception while loading materials from JSON: " + std::string(e.what()));
            return false;
        }
    }

    void MaterialManager::ClearAllMaterials()
    {
        size_t count = materials_.size();
        materials_.clear();
        DEBUG_LOG("Cleared " << count << " materials");
    }

    size_t MaterialManager::GetMaterialCount() const
    {
        return materials_.size();
    }

    std::vector<std::string> MaterialManager::GetAllMaterialIds() const
    {
        std::vector<std::string> ids;
        ids.reserve(materials_.size());

        for (const auto &pair : materials_)
        {
            ids.push_back(pair.first);
        }

        std::sort(ids.begin(), ids.end());
        return ids;
    }

    bool MaterialManager::ValidateMaterial(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            return false;
        }

        const auto &props = it->second.properties;

        // Validate color values are in valid range
        auto validateColor = [](const Math::float3 &color)
        {
            return color.x >= 0.0f && color.x <= 1.0f &&
                   color.y >= 0.0f && color.y <= 1.0f &&
                   color.z >= 0.0f && color.z <= 1.0f;
        };

        if (!validateColor(props.albedo) || !validateColor(props.emission) || !validateColor(props.rimColor))
        {
            return false;
        }

        // Validate numeric ranges
        if (props.metallic < 0.0f || props.metallic > 1.0f ||
            props.roughness < 0.0f || props.roughness > 1.0f ||
            props.rimPower < 0.1f || props.rimPower > 10.0f ||
            props.toonSteps < 1 || props.toonSteps > 16)
        {
            return false;
        }

        return true;
    }

    void MaterialManager::PrintMaterialInfo(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            DEBUG_LOG("Material not found: " << materialId);
            return;
        }

        const auto &material = it->second;
        const auto &props = material.properties;

        DEBUG_LOG("\\n=== Material Info: " << materialId << " ===");
        DEBUG_LOG("Type: " << material.type);
        DEBUG_LOG("Dynamic: " << (material.isDynamic ? "Yes" : "No"));
        DEBUG_LOG("Albedo: (" << props.albedo.x << ", " << props.albedo.y << ", " << props.albedo.z << ")");
        DEBUG_LOG("Metallic: " << props.metallic << ", Roughness: " << props.roughness);
        DEBUG_LOG("Toon Steps: " << props.toonSteps << ", Threshold: " << props.toonThreshold);
        DEBUG_LOG("Rim Lighting: " << (props.enableRimLighting ? "Enabled" : "Disabled"));
        DEBUG_LOG("Outlines: " << (props.enableOutlines ? "Enabled" : "Disabled"));
        DEBUG_LOG("Animation: " << (props.isAnimated ? props.animationType + " (speed: " + std::to_string(props.animationSpeed) + ")" : "None"));
        DEBUG_LOG("=========================");
    }

    // Private helper methods

    std::string MaterialManager::GenerateUniqueMaterialId(const std::string &baseType)
    {
        static int counter = 1000;
        std::string materialId;

        do
        {
            std::stringstream ss;
            ss << baseType << "_material_" << std::setfill('0') << std::setw(4) << counter++;
            materialId = ss.str();
        } while (HasMaterial(materialId));

        return materialId;
    }

    MaterialProperties MaterialManager::CreateBaseProperties(const std::string &materialType)
    {
        MaterialProperties props;

        // Try to use the properties from loaded materials if available
        std::string materialId;
        if (materialType == "earth")
        {
            materialId = "EarthSurfaceMaterial";
        }
        else if (materialType == "atmosphere")
        {
            materialId = "AtmosphereMaterial";
        }
        else if (materialType == "cloud")
        {
            materialId = "CloudMaterial";
        }
        else if (materialType == "contrail")
        {
            materialId = "ContrailMaterial";
        }

        // If the material exists, copy its properties
        if (!materialId.empty() && HasMaterial(materialId))
        {
            auto material = GetMaterial(materialId);
            if (material)
            {
                return material->properties;
            }
        }

        // Fallback to default properties if the material isn't loaded
        if (materialType == "earth")
        {
            props.albedo = {0.2f, 0.4f, 0.9f}; // Blue earth (updated from green)
            props.roughness = 0.8f;
            props.metallic = 0.0f;
            props.toonSteps = 6;
        }
        else if (materialType == "atmosphere")
        {
            props.albedo = {0.5f, 0.7f, 1.0f};
            props.roughness = 0.0f;
            props.metallic = 0.0f;
            props.toonSteps = 3;
        }
        else if (materialType == "cloud")
        {
            props.albedo = {1.0f, 1.0f, 1.0f};
            props.roughness = 0.1f;
            props.metallic = 0.0f;
            props.toonSteps = 4;
        }
        else if (materialType == "contrail")
        {
            props.albedo = {1.0f, 1.0f, 1.0f};
            props.emission = {0.1f, 0.1f, 0.1f};
            props.roughness = 0.0f;
            props.metallic = 0.0f;
            props.toonSteps = 2;
        }

        return props;
    }

    void MaterialManager::ApplyGlobalCelShadingSettings(MaterialProperties &properties)
    {
        if (properties.toonSteps == 4)
        { // Only apply if using default
            properties.toonSteps = globalToonSteps_;
        }
        if (properties.toonThreshold == 0.5f)
        { // Only apply if using default
            properties.toonThreshold = globalToonThreshold_;
        }
        if (properties.enableRimLighting)
        { // Only apply if rim lighting is enabled
            properties.enableRimLighting = globalRimLighting_;
        }
    }

    MaterialProperties MaterialManager::CreateEarthProperties(float radius, int detailLevel)
    {
        MaterialProperties props = CreateBaseProperties("earth");

        // Adjust properties based on radius (for LOD)
        if (radius > 5000000.0f)
        { // Large scale (space view)
            props.toonSteps = 8;
            props.roughness = 0.6f;
        }
        else if (radius > 1000000.0f)
        { // Medium scale
            props.toonSteps = 6;
            props.roughness = 0.7f;
        }
        else
        { // Close scale
            props.toonSteps = 4;
            props.roughness = 0.9f;
        }

        // Detail level affects rim lighting
        props.rimStrength = 1.0f + (detailLevel * 0.2f);
        props.enableRimLighting = true;
        props.rimColor = {0.8f, 0.9f, 1.0f};

        return props;
    }

    MaterialProperties MaterialManager::CreateAtmosphereProperties(int layer, float density)
    {
        MaterialProperties props = CreateBaseProperties("atmosphere");

        // Layer affects color and properties
        float layerFactor = static_cast<float>(layer) / 3.0f;
        props.albedo.x = 0.4f + layerFactor * 0.2f;
        props.albedo.y = 0.6f + layerFactor * 0.2f;
        props.albedo.z = 0.9f + layerFactor * 0.1f;

        // Density affects rim lighting
        props.rimStrength = density * 3.0f;
        props.rimPower = 1.5f + density;
        props.enableRimLighting = true;

        props.toonSteps = 2 + layer;
        props.toonThreshold = 0.3f + density * 0.4f;

        return props;
    }

    MaterialProperties MaterialManager::CreateCloudProperties(float coverage, float density)
    {
        MaterialProperties props = CreateBaseProperties("cloud");

        // Coverage affects albedo
        props.albedo = {0.9f + coverage * 0.1f, 0.9f + coverage * 0.1f, 0.9f + coverage * 0.1f};

        // Density affects roughness and animation
        props.roughness = 0.05f + density * 0.15f;
        props.isAnimated = true;
        props.animationType = "scroll";
        props.animationSpeed = 0.3f + density * 0.4f;

        props.enableRimLighting = true;
        props.rimColor = {0.9f, 0.95f, 1.0f};
        props.rimStrength = 1.2f;

        return props;
    }

    MaterialProperties MaterialManager::CreateContrailProperties(const Math::float3 &color)
    {
        MaterialProperties props = CreateBaseProperties("contrail");

        props.albedo = color;
        props.emission = {color.x * 0.2f, color.y * 0.2f, color.z * 0.2f};

        props.isAnimated = true;
        props.animationType = "wave";
        props.animationSpeed = 1.5f;

        props.enableRimLighting = true;
        props.rimColor = color;
        props.rimStrength = 2.0f;
        props.rimPower = 1.0f;

        return props;
    }

    void MaterialManager::AssignEarthTextures(MaterialProperties &properties, float radius, int detailLevel)
    {
        if (!textureGenerator_)
            return;

        // For now, just assign placeholder texture names
        // In a real implementation, we would generate textures using ProceduralTexture::ProceduralTextureGenerator::generateTexture
        std::string baseId = "earth_" + std::to_string(static_cast<int>(radius)) + "_detail" + std::to_string(detailLevel);

        properties.albedoTexture = baseId + "_albedo";
        properties.normalTexture = baseId + "_normal";
    }

    void MaterialManager::AssignAtmosphereTextures(MaterialProperties &properties, int layer)
    {
        if (!textureGenerator_)
            return;

        std::string baseId = "atmosphere_layer" + std::to_string(layer);
        properties.albedoTexture = baseId + "_albedo";
    }

    void MaterialManager::AssignCloudTextures(MaterialProperties &properties, float coverage)
    {
        if (!textureGenerator_)
            return;

        std::string baseId = "cloud_coverage" + std::to_string(static_cast<int>(coverage * 100));
        properties.albedoTexture = baseId + "_albedo";
    }

    void MaterialManager::AssignContrailTextures(MaterialProperties &properties)
    {
        if (!textureGenerator_)
            return;

        properties.albedoTexture = "contrail_albedo";
    }
}
