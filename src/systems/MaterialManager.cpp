#include "MaterialManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>

namespace Material
{
    MaterialManager::MaterialManager()
        : textureGenerator_(nullptr)
    {
        std::cout << "MaterialManager initialized" << std::endl;
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
            std::cout << "Warning: Overwriting existing material: " << materialId << std::endl;
        }

        materials_[materialId] = material;

        // Apply global cel-shading settings if not specifically set
        if (materials_[materialId].properties.toonSteps == 4)
        {
            ApplyGlobalCelShadingSettings(materials_[materialId].properties);
        }

        std::cout << "Loaded material: " << materialId << " (type: " << material.type << ")" << std::endl;
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

        std::cout << "Updated global cel-shading: " << globalToonSteps_ << " steps, "
                  << globalToonThreshold_ << " threshold, rim: " << (globalRimLighting_ ? "enabled" : "disabled") << std::endl;
    }

    void MaterialManager::EnableOutlinesForMaterial(const std::string &materialId, float width, const Math::float3 &color)
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            it->second.properties.enableOutlines = true;
            it->second.properties.outlineWidth = std::max(0.001f, std::min(width, 0.1f));
            it->second.properties.outlineColor = color;
            std::cout << "Enabled outlines for material: " << materialId << std::endl;
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
            std::cout << "Set animation for material: " << materialId << " (" << animType << ", speed: " << speed << ")" << std::endl;
        }
        else
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
        }
    }

    void MaterialManager::SetTextureGenerator(const ProceduralTexture::ProceduralTextureGenerator *generator)
    {
        textureGenerator_ = generator;
        std::cout << "Texture generator assigned to MaterialManager" << std::endl;
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

            std::cout << "Generated and assigned " << textureType << " texture to material: " << materialId << std::endl;
        }

        return textureId;
    }

    void MaterialManager::LoadDefaultMaterials()
    {
        std::cout << "Loading default materials..." << std::endl;

        // Load materials from the developer package
        if (LoadMaterialsFromFile("assets/packages/DeveloperPackage/materials.xml"))
        {
            std::cout << "Default materials loaded successfully" << std::endl;
            return;
        }

        // Fallback to hardcoded materials if file loading fails
        std::cerr << "Failed to load materials from file, using hardcoded defaults" << std::endl;

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

        std::cout << "Hardcoded default materials loaded" << std::endl;
    }

    bool MaterialManager::LoadMaterialsFromFile(const std::string &filePath)
    {
        // Read XML file
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open materials file: " << filePath << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        size_t materialsStart = xmlContent.find("<materials>");
        size_t materialsEnd = xmlContent.find("</materials>");

        if (materialsStart == std::string::npos || materialsEnd == std::string::npos)
        {
            std::cerr << "Invalid materials file format: " << filePath << std::endl;
            return false;
        }

        std::string materialsSection = xmlContent.substr(
            materialsStart,
            materialsEnd - materialsStart + std::string("</materials>").length());

        // Parse individual material elements using regex
        size_t currentPos = 0;
        while (true)
        {
            size_t materialStart = materialsSection.find("<material", currentPos);
            if (materialStart == std::string::npos)
                break;

            size_t materialEnd = materialsSection.find("</material>", materialStart);
            if (materialEnd == std::string::npos)
                break;

            materialEnd += std::string("</material>").length();

            std::string materialXml = materialsSection.substr(materialStart, materialEnd - materialStart);

            // Extract material attributes
            std::string materialId = ExtractAttributeValue(materialXml, "id");
            std::string materialType = ExtractAttributeValue(materialXml, "type");

            if (materialId.empty() || materialType.empty())
            {
                std::cerr << "Material missing required attributes: " << materialXml << std::endl;
                currentPos = materialEnd;
                continue;
            }

            // Create material
            Material material(materialId, materialType);

            // Parse properties section
            size_t propsStart = materialXml.find("<properties>");
            size_t propsEnd = materialXml.find("</properties>");

            if (propsStart != std::string::npos && propsEnd != std::string::npos)
            {
                std::string propsSection = materialXml.substr(propsStart, propsEnd - propsStart + std::string("</properties>").length());

                // Parse albedo color
                ParseColorProperty(propsSection, "albedo", material.properties.albedo);

                // Parse emission color
                ParseColorProperty(propsSection, "emission", material.properties.emission);

                // Parse rim color
                ParseColorProperty(propsSection, "rimColor", material.properties.rimColor);

                // Parse float properties
                ParseFloatProperty(propsSection, "roughness", material.properties.roughness);
                ParseFloatProperty(propsSection, "metallic", material.properties.metallic);
                ParseFloatProperty(propsSection, "rimPower", material.properties.rimPower);
                ParseFloatProperty(propsSection, "rimStrength", material.properties.rimStrength);

                // Parse integer properties
                ParseIntProperty(propsSection, "toonSteps", material.properties.toonSteps);

                // Parse boolean properties
                ParseBoolProperty(propsSection, "enableRimLighting", material.properties.enableRimLighting);
                ParseBoolProperty(propsSection, "enableOutlines", material.properties.enableOutlines);

                // Parse texture references
                material.properties.albedoTexture = ExtractTagValue(propsSection, "albedoTexture");
                material.properties.normalTexture = ExtractTagValue(propsSection, "normalTexture");
                material.properties.metallicTexture = ExtractTagValue(propsSection, "metallicTexture");
                material.properties.roughnessTexture = ExtractTagValue(propsSection, "roughnessTexture");
                material.properties.emissionTexture = ExtractTagValue(propsSection, "emissionTexture");
            }

            // Load the material
            LoadMaterial(materialId, material);

            currentPos = materialEnd;
        }

        std::cout << "Loaded materials from file: " << filePath << std::endl;
        return true;
    }

    void MaterialManager::ClearAllMaterials()
    {
        size_t count = materials_.size();
        materials_.clear();
        std::cout << "Cleared " << count << " materials" << std::endl;
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
            std::cout << "Material not found: " << materialId << std::endl;
            return;
        }

        const auto &material = it->second;
        const auto &props = material.properties;

        std::cout << "\\n=== Material Info: " << materialId << " ===" << std::endl;
        std::cout << "Type: " << material.type << std::endl;
        std::cout << "Dynamic: " << (material.isDynamic ? "Yes" : "No") << std::endl;
        std::cout << "Albedo: (" << props.albedo.x << ", " << props.albedo.y << ", " << props.albedo.z << ")" << std::endl;
        std::cout << "Metallic: " << props.metallic << ", Roughness: " << props.roughness << std::endl;
        std::cout << "Toon Steps: " << props.toonSteps << ", Threshold: " << props.toonThreshold << std::endl;
        std::cout << "Rim Lighting: " << (props.enableRimLighting ? "Enabled" : "Disabled") << std::endl;
        std::cout << "Outlines: " << (props.enableOutlines ? "Enabled" : "Disabled") << std::endl;
        std::cout << "Animation: " << (props.isAnimated ? props.animationType + " (speed: " + std::to_string(props.animationSpeed) + ")" : "None") << std::endl;
        std::cout << "=========================" << std::endl;
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

    // XML parsing helper methods
    std::string MaterialManager::ExtractAttributeValue(const std::string &xml, const std::string &attributeName)
    {
        std::string searchStr = attributeName + "=\"";
        size_t start = xml.find(searchStr);
        if (start == std::string::npos)
            return "";

        start += searchStr.length();
        size_t end = xml.find("\"", start);
        if (end == std::string::npos)
            return "";

        return xml.substr(start, end - start);
    }

    std::string MaterialManager::ExtractTagValue(const std::string &xml, const std::string &tagName)
    {
        std::string openTag = "<" + tagName + ">";
        std::string closeTag = "</" + tagName + ">";

        size_t start = xml.find(openTag);
        if (start == std::string::npos)
            return "";

        start += openTag.length();
        size_t end = xml.find(closeTag, start);
        if (end == std::string::npos)
            return "";

        return xml.substr(start, end - start);
    }

    void MaterialManager::ParseColorProperty(const std::string &xml, const std::string &propName, Math::float3 &colorValue)
    {
        std::string startTag = "<" + propName;
        size_t start = xml.find(startTag);
        if (start == std::string::npos)
            return;

        std::string r = ExtractAttributeValue(xml.substr(start), "r");
        std::string g = ExtractAttributeValue(xml.substr(start), "g");
        std::string b = ExtractAttributeValue(xml.substr(start), "b");

        if (!r.empty())
            colorValue.x = std::stof(r);
        if (!g.empty())
            colorValue.y = std::stof(g);
        if (!b.empty())
            colorValue.z = std::stof(b);
    }

    void MaterialManager::ParseFloatProperty(const std::string &xml, const std::string &propName, float &floatValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            try
            {
                floatValue = std::stof(value);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error parsing float property " << propName << ": " << e.what() << std::endl;
            }
        }
    }

    void MaterialManager::ParseIntProperty(const std::string &xml, const std::string &propName, int &intValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            try
            {
                intValue = std::stoi(value);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error parsing int property " << propName << ": " << e.what() << std::endl;
            }
        }
    }

    void MaterialManager::ParseBoolProperty(const std::string &xml, const std::string &propName, bool &boolValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            boolValue = (value == "true" || value == "1");
        }
    }
}
