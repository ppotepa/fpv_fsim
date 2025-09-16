#include "SceneConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <regex>
#include <iostream>

namespace SceneConfig
{

    // ============================================================================
    // SceneConfigParser Implementation
    // ============================================================================

    SceneConfigParser::SceneConfigParser(const ParserConfig &config) : config_(config)
    {
        // Initialize default values and lookup tables
    }

    ParseResult SceneConfigParser::parseSceneFile(const std::string &filePath)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Read file content
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Failed to open file: " + filePath;
            return currentResult_;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        // Parse the XML content
        auto result = parseSceneString(xmlContent);

        // If successful and asset resolution is enabled, resolve paths relative to the scene file
        if (result.success && config_.loadExternalAssets && result.scene)
        {
            // Simple base directory resolution - just get directory from file path
            size_t lastSlash = filePath.find_last_of("/\\");
            if (lastSlash != std::string::npos)
            {
                std::string baseDirectory = filePath.substr(0, lastSlash + 1);
                resolveAssetPaths(*result.scene, baseDirectory);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        result.parseTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};
        
        try
        {
            // For now, create a minimal scene for loading_indicator type
            auto scene = std::make_shared<Scene>();
            
            // Simple XML attribute extraction - basic implementation
            scene->id = extractAttributeSimple(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttributeSimple(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttributeSimple(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttributeSimple(xmlContent, "scene", "version", "1.0");
            
            // For loading_indicator scenes, we don't need complex parsing
            // Just set up basic structure
            currentResult_.scene = scene;
            currentResult_.success = true;
            currentResult_.errorMessage = "";
            
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = std::string("Parse error: ") + e.what();
        }

        return currentResult_;
    }

    // Simple helper method for basic attribute extraction
    std::string SceneConfigParser::extractAttributeSimple(const std::string &xmlContent, 
                                                         const std::string &elementName,
                                                         const std::string &attributeName, 
                                                         const std::string &defaultValue)
    {
        // Simple regex-based attribute extraction
        std::string pattern = "<" + elementName + "[^>]*" + attributeName + "=\"([^\"]*?)\"";
        std::regex re(pattern);
        std::smatch match;
        
        if (std::regex_search(xmlContent, match, re))
        {
            return match[1].str();
        }
        
        return defaultValue;
    }

    bool SceneConfigParser::resolveAssetPaths(Scene &scene, const std::string &baseDirectory)
    {
        // Simple implementation - just return true for now
        // In a full implementation, this would resolve all asset paths relative to baseDirectory
        return true;
    }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        result.parseTimeMs = static_cast<float>(duration.count());

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Schema validation if enabled
        if (config_.validateSchema && !config_.schemaPath.empty())
        {
            std::vector<std::string> validationErrors;
            if (!validateAgainstSchema(xmlContent, validationErrors))
            {
                currentResult_.success = false;
                currentResult_.errorMessage = "Schema validation failed";
                currentResult_.warnings = validationErrors;
                return currentResult_;
            }
        }

        // Parse the XML document
        auto result = parseXmlDocument(xmlContent);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        result.parseTimeMs = static_cast<float>(duration.count());

        return result;
    }

    ParseResult SceneConfigParser::parseXmlDocument(const std::string &xmlContent)
    {
        // This is a simplified XML parser implementation
        // In a real implementation, you would use a proper XML library

        try
        {
            // Create a new scene
            auto scene = std::make_shared<Scene>();

            // Basic XML parsing simulation
            // In reality, this would use a proper XML DOM parser

            // Extract scene attributes
            scene->id = extractAttribute(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttribute(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttribute(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttribute(xmlContent, "scene", "version", "1.0");

            // Parse materials section
            parseMaterialsSection(xmlContent, *scene);

            // Parse textures section
            parseTexturesSection(xmlContent, *scene);

            // Parse meshes section
            parseMeshesSection(xmlContent, *scene);

            // Parse animations section
            parseAnimationsSection(xmlContent, *scene);

            // Parse entities section
            parseEntitiesSection(xmlContent, *scene);

            // Parse cameras section
            parseCamerasSection(xmlContent, *scene);

            // Parse lights section
            parseLightsSection(xmlContent, *scene);

            // Parse environment settings
            parseEnvironmentSection(xmlContent, *scene);

            // Validate the parsed scene
            std::vector<std::string> validationErrors;
            if (!validateSceneStructure(*scene, validationErrors))
            {
                if (config_.strictParsing)
                {
                    currentResult_.success = false;
                    currentResult_.errorMessage = "Scene validation failed";
                    currentResult_.warnings = validationErrors;
                    return currentResult_;
                }
                else
                {
                    currentResult_.warnings.insert(currentResult_.warnings.end(),
                                                   validationErrors.begin(), validationErrors.end());
                }
            }

            // Success
            currentResult_.success = true;
            currentResult_.scene = scene;
            currentResult_.entitiesLoaded = scene->rootEntities.size();
            currentResult_.materialsLoaded = scene->materials.size();
            currentResult_.texturesLoaded = scene->textures.size();
            currentResult_.animationsLoaded = scene->animations.size();
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Parse error: " + std::string(e.what());
        }

        return currentResult_;
    }

    // ============================================================================
    // Section Parsing Methods
    // ============================================================================

    void SceneConfigParser::parseMaterialsSection(const std::string &xmlContent, Scene &scene)
    {
        // Extract materials section
        auto materialsSection = extractSection(xmlContent, "materials");
        if (materialsSection.empty())
            return;

        // Parse individual material elements
        auto materialElements = extractElements(materialsSection, "material");
        for (const auto &materialXml : materialElements)
        {
            Material material;

            material.id = extractAttribute(materialXml, "material", "id", generateMaterialId(materialCounter_++));
            material.name = extractAttribute(materialXml, "material", "name", material.id);
            material.shader = extractAttribute(materialXml, "material", "shader", "standard");

            // Parse colors
            material.diffuse = parseColorFromXml(materialXml, "diffuse", {1.0f, 1.0f, 1.0f, 1.0f});
            material.ambient = parseColorFromXml(materialXml, "ambient", {0.2f, 0.2f, 0.2f, 1.0f});
            material.specular = parseColorFromXml(materialXml, "specular", {1.0f, 1.0f, 1.0f, 1.0f});
            material.emissive = parseColorFromXml(materialXml, "emissive", {0.0f, 0.0f, 0.0f, 1.0f});

            // Parse material properties
            material.metallic = extractFloatAttribute(materialXml, "material", "metallic", 0.0f);
            material.roughness = extractFloatAttribute(materialXml, "material", "roughness", 0.5f);
            material.shininess = extractFloatAttribute(materialXml, "material", "shininess", 32.0f);
            material.opacity = extractFloatAttribute(materialXml, "material", "opacity", 1.0f);

            // Parse texture references
            material.diffuseTexture = extractAttribute(materialXml, "material", "diffuseTexture", "");
            material.normalTexture = extractAttribute(materialXml, "material", "normalTexture", "");
            material.specularTexture = extractAttribute(materialXml, "material", "specularTexture", "");
            material.emissiveTexture = extractAttribute(materialXml, "material", "emissiveTexture", "");

            // Parse cel-shading properties
            material.celShading = extractBoolAttribute(materialXml, "material", "celShading", false);
            if (material.celShading)
            {
                material.celLevels = extractUintAttribute(materialXml, "material", "celLevels", 3);
                material.celThreshold = extractFloatAttribute(materialXml, "material", "celThreshold", 0.5f);
                material.celOutlineColor = parseColorFromXml(materialXml, "celOutlineColor", {0.0f, 0.0f, 0.0f, 1.0f});
                material.celOutlineWidth = extractFloatAttribute(materialXml, "material", "celOutlineWidth", 0.01f);
            }

            // Parse custom properties
            auto propertiesSection = extractSection(materialXml, "properties");
            material.customProperties = parsePropertiesMap(propertiesSection);

            scene.materials.push_back(material);
            materialLookup_[material.id] = material;
        }
    }

    void SceneConfigParser::parseTexturesSection(const std::string &xmlContent, Scene &scene)
    {
        auto texturesSection = extractSection(xmlContent, "textures");
        if (texturesSection.empty())
            return;

        auto textureElements = extractElements(texturesSection, "texture");
        for (const auto &textureXml : textureElements)
        {
            ProceduralTexture texture;

            texture.id = extractAttribute(textureXml, "texture", "id", generateTextureId(textureCounter_++));
            texture.name = extractAttribute(textureXml, "texture", "name", texture.id);
            texture.type = extractAttribute(textureXml, "texture", "type", "noise");
            texture.width = extractUintAttribute(textureXml, "texture", "width", 256);
            texture.height = extractUintAttribute(textureXml, "texture", "height", 256);
            texture.format = extractAttribute(textureXml, "texture", "format", "RGBA");

            // Parse generation parameters
            auto parametersSection = extractSection(textureXml, "parameters");
            texture.parameters = parsePropertiesMap(parametersSection);

            scene.textures.push_back(texture);
            textureLookup_[texture.id] = texture;
        }
    }

    void SceneConfigParser::parseMeshesSection(const std::string &xmlContent, Scene &scene)
    {
        auto meshesSection = extractSection(xmlContent, "meshes");
        if (meshesSection.empty())
            return;

        auto meshElements = extractElements(meshesSection, "compound");
        for (const auto &meshXml : meshElements)
        {
            CompoundMesh mesh;

            mesh.id = extractAttribute(meshXml, "compound", "id", generateEntityId("mesh", entityCounter_++));
            mesh.name = extractAttribute(meshXml, "compound", "name", mesh.id);
            mesh.materialId = extractAttribute(meshXml, "compound", "material", config_.defaultMaterial);

            // Parse base transform
            auto transformSection = extractSection(meshXml, "transform");
            mesh.baseTransform = parseTransformFromXml(transformSection);

            // Parse animation settings
            mesh.animated = extractBoolAttribute(meshXml, "compound", "animated", false);
            if (mesh.animated)
            {
                mesh.animationType = extractAttribute(meshXml, "compound", "animationType", "");
                auto animParamsSection = extractSection(meshXml, "animationParams");
                mesh.animationParams = parsePropertiesMap(animParamsSection);
            }

            // Parse parts
            auto partsSection = extractSection(meshXml, "parts");
            auto partElements = extractElements(partsSection, "part");
            for (const auto &partXml : partElements)
            {
                VoxelPrimitive part;

                std::string typeStr = extractAttribute(partXml, "part", "type", "cube");
                part.type = Utils::stringToVoxelType(typeStr);

                part.size = extractFloatAttribute(partXml, "part", "size", 1.0f);
                part.radius = extractFloatAttribute(partXml, "part", "radius", 0.5f);
                part.height = extractFloatAttribute(partXml, "part", "height", 1.0f);
                part.subdivisions = extractUintAttribute(partXml, "part", "subdivisions", 1);
                part.materialId = extractAttribute(partXml, "part", "material", mesh.materialId);

                // Parse part transform
                auto partTransformSection = extractSection(partXml, "transform");
                part.transform = parseTransformFromXml(partTransformSection);

                // Parse part animation
                part.animated = extractBoolAttribute(partXml, "part", "animated", false);
                if (part.animated)
                {
                    part.animationType = extractAttribute(partXml, "part", "animationType", "");
                    auto partAnimParamsSection = extractSection(partXml, "animationParams");
                    part.animationParams = parsePropertiesMap(partAnimParamsSection);
                }

                mesh.parts.push_back(part);
            }

            scene.meshes.push_back(mesh);
        }
    }

    void SceneConfigParser::parseAnimationsSection(const std::string &xmlContent, Scene &scene)
    {
        auto animationsSection = extractSection(xmlContent, "animations");
        if (animationsSection.empty())
            return;

        auto animationElements = extractElements(animationsSection, "animation");
        for (const auto &animationXml : animationElements)
        {
            Animation animation;

            animation.id = extractAttribute(animationXml, "animation", "id", generateAnimationId(animationCounter_++));
            animation.name = extractAttribute(animationXml, "animation", "name", animation.id);
            animation.type = extractAttribute(animationXml, "animation", "type", "transform");
            animation.duration = extractFloatAttribute(animationXml, "animation", "duration", 1.0f);
            animation.loop = extractBoolAttribute(animationXml, "animation", "loop", true);
            animation.autoStart = extractBoolAttribute(animationXml, "animation", "autoStart", true);

            animation.targetType = extractAttribute(animationXml, "animation", "targetType", "entity");
            animation.targetId = extractAttribute(animationXml, "animation", "targetId", "");

            // Parse animation parameters
            auto parametersSection = extractSection(animationXml, "parameters");
            animation.parameters = parsePropertiesMap(parametersSection);

            // Parse keyframes if present
            auto keyframesSection = extractSection(animationXml, "keyframes");
            auto keyframeElements = extractElements(keyframesSection, "keyframe");
            for (const auto &keyframeXml : keyframeElements)
            {
                Animation::Keyframe keyframe;
                keyframe.time = extractFloatAttribute(keyframeXml, "keyframe", "time", 0.0f);

                auto valuesSection = extractSection(keyframeXml, "values");
                keyframe.values = parsePropertiesMap(valuesSection);

                animation.keyframes.push_back(keyframe);
            }

            scene.animations.push_back(animation);
            animationLookup_[animation.id] = animation;
        }
    }

    void SceneConfigParser::parseEntitiesSection(const std::string &xmlContent, Scene &scene)
    {
        auto entitiesSection = extractSection(xmlContent, "entities");
        if (entitiesSection.empty())
            return;

        auto entityElements = extractElements(entitiesSection, "entity");
        for (const auto &entityXml : entityElements)
        {
            auto entity = parseEntityFromXml(entityXml);
            if (entity)
            {
                scene.rootEntities.push_back(entity);
                entityLookup_[entity->id] = entity;
            }
        }
    }

    void SceneConfigParser::parseCamerasSection(const std::string &xmlContent, Scene &scene)
    {
        auto camerasSection = extractSection(xmlContent, "cameras");
        if (camerasSection.empty())
        {
            // Create default camera if none specified
            Camera defaultCamera = createCamera("main_camera");
            scene.cameras.push_back(defaultCamera);
            return;
        }

        auto cameraElements = extractElements(camerasSection, "camera");
        for (const auto &cameraXml : cameraElements)
        {
            Camera camera;

            camera.id = extractAttribute(cameraXml, "camera", "id", "camera_" + std::to_string(scene.cameras.size()));

            std::string typeStr = extractAttribute(cameraXml, "camera", "type", "perspective");
            camera.type = Utils::stringToCameraType(typeStr);

            // Parse transform
            auto transformSection = extractSection(cameraXml, "transform");
            camera.transform = parseTransformFromXml(transformSection);

            // Parse camera parameters
            if (camera.type == Camera::Type::Perspective)
            {
                camera.fov = extractFloatAttribute(cameraXml, "camera", "fov", 45.0f);
                camera.nearPlane = extractFloatAttribute(cameraXml, "camera", "nearPlane", 0.1f);
                camera.farPlane = extractFloatAttribute(cameraXml, "camera", "farPlane", 1000.0f);
            }
            else
            {
                camera.left = extractFloatAttribute(cameraXml, "camera", "left", -10.0f);
                camera.right = extractFloatAttribute(cameraXml, "camera", "right", 10.0f);
                camera.bottom = extractFloatAttribute(cameraXml, "camera", "bottom", -10.0f);
                camera.top = extractFloatAttribute(cameraXml, "camera", "top", 10.0f);
                camera.nearPlane = extractFloatAttribute(cameraXml, "camera", "nearPlane", 0.1f);
                camera.farPlane = extractFloatAttribute(cameraXml, "camera", "farPlane", 1000.0f);
            }

            // Parse animation
            camera.animated = extractBoolAttribute(cameraXml, "camera", "animated", false);
            if (camera.animated)
            {
                camera.animationId = extractAttribute(cameraXml, "camera", "animationId", "");
            }

            scene.cameras.push_back(camera);
        }
    }

    void SceneConfigParser::parseLightsSection(const std::string &xmlContent, Scene &scene)
    {
        auto lightsSection = extractSection(xmlContent, "lights");
        if (lightsSection.empty())
            return;

        auto lightElements = extractElements(lightsSection, "light");
        for (const auto &lightXml : lightElements)
        {
            Light light;

            light.id = extractAttribute(lightXml, "light", "id", "light_" + std::to_string(scene.lights.size()));
            light.name = extractAttribute(lightXml, "light", "name", light.id);

            std::string typeStr = extractAttribute(lightXml, "light", "type", "directional");
            light.type = Utils::stringToLightType(typeStr);

            // Parse transform
            auto transformSection = extractSection(lightXml, "transform");
            light.transform = parseTransformFromXml(transformSection);

            // Parse light properties
            light.color = parseColorFromXml(lightXml, "color", {1.0f, 1.0f, 1.0f, 1.0f});
            light.intensity = extractFloatAttribute(lightXml, "light", "intensity", 1.0f);

            if (light.type == Light::Type::Point || light.type == Light::Type::Spot)
            {
                light.range = extractFloatAttribute(lightXml, "light", "range", 10.0f);
                light.constantAttenuation = extractFloatAttribute(lightXml, "light", "constantAttenuation", 1.0f);
                light.linearAttenuation = extractFloatAttribute(lightXml, "light", "linearAttenuation", 0.09f);
                light.quadraticAttenuation = extractFloatAttribute(lightXml, "light", "quadraticAttenuation", 0.032f);
            }

            if (light.type == Light::Type::Spot)
            {
                light.innerCone = extractFloatAttribute(lightXml, "light", "innerCone", 30.0f);
                light.outerCone = extractFloatAttribute(lightXml, "light", "outerCone", 45.0f);
            }

            // Parse animation
            light.animated = extractBoolAttribute(lightXml, "light", "animated", false);
            if (light.animated)
            {
                light.animationId = extractAttribute(lightXml, "light", "animationId", "");
            }

            scene.lights.push_back(light);
        }
    }

    void SceneConfigParser::parseEnvironmentSection(const std::string &xmlContent, Scene &scene)
    {
        auto environmentSection = extractSection(xmlContent, "environment");
        if (environmentSection.empty())
            return;

        // Parse background color
        scene.backgroundColor = parseColorFromXml(environmentSection, "backgroundColor", {0.0f, 0.0f, 0.0f, 1.0f});
        scene.ambientLight = parseColorFromXml(environmentSection, "ambientLight", {0.2f, 0.2f, 0.2f, 1.0f});

        // Parse skybox
        scene.skybox = extractAttribute(environmentSection, "environment", "skybox", "");

        // Parse rendering settings
        scene.enableShadows = extractBoolAttribute(environmentSection, "environment", "enableShadows", true);
        scene.enableBloom = extractBoolAttribute(environmentSection, "environment", "enableBloom", false);
        scene.enableSSAO = extractBoolAttribute(environmentSection, "environment", "enableSSAO", false);
        scene.gamma = extractFloatAttribute(environmentSection, "environment", "gamma", 2.2f);
        scene.exposure = extractFloatAttribute(environmentSection, "environment", "exposure", 1.0f);
    }

    // ============================================================================
    // Utility Methods Implementation (simplified for brevity)
    // ============================================================================

    std::string SceneConfigParser::extractAttribute(const std::string &xml, const std::string &element, const std::string &attribute, const std::string &defaultValue)
    {
        // Simplified attribute extraction - in real implementation use proper XML parser
        std::regex pattern(element + R"(\s+[^>]*)" + attribute + R"(\s*=\s*"([^"]*)") ");
            std::smatch match;
        if (std::regex_search(xml, match, pattern))
        {
            return match[1].str();
        }
        return defaultValue;
    }

    float SceneConfigParser::extractFloatAttribute(const std::string &xml, const std::string &element, const std::string &attribute, float defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        try
        {
            return std::stof(value);
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    uint32_t SceneConfigParser::extractUintAttribute(const std::string &xml, const std::string &element, const std::string &attribute, uint32_t defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        try
        {
            return static_cast<uint32_t>(std::stoul(value));
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    bool SceneConfigParser::extractBoolAttribute(const std::string &xml, const std::string &element, const std::string &attribute, bool defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        return (value == "true" || value == "1" || value == "yes");
    }

    Material::Color SceneConfigParser::parseColorFromXml(const std::string &xml, const std::string &colorElement, const Material::Color &defaultValue)
    {
        // Simplified color parsing
        std::string colorStr = extractAttribute(xml, colorElement, "value", "");
        if (colorStr.empty())
            return defaultValue;
        return Utils::parseColorString(colorStr);
    }

    Transform SceneConfigParser::parseTransformFromXml(const std::string &xml)
    {
        Transform transform;

        // Parse position
        transform.position.x = extractFloatAttribute(xml, "position", "x", 0.0f);
        transform.position.y = extractFloatAttribute(xml, "position", "y", 0.0f);
        transform.position.z = extractFloatAttribute(xml, "position", "z", 0.0f);

        // Parse rotation (quaternion)
        transform.rotation.x = extractFloatAttribute(xml, "rotation", "x", 0.0f);
        transform.rotation.y = extractFloatAttribute(xml, "rotation", "y", 0.0f);
        transform.rotation.z = extractFloatAttribute(xml, "rotation", "z", 0.0f);
        transform.rotation.w = extractFloatAttribute(xml, "rotation", "w", 1.0f);

        // Parse scale
        transform.scale.x = extractFloatAttribute(xml, "scale", "x", 1.0f);
        transform.scale.y = extractFloatAttribute(xml, "scale", "y", 1.0f);
        transform.scale.z = extractFloatAttribute(xml, "scale", "z", 1.0f);

        return transform;
    }

    std::shared_ptr<Entity> SceneConfigParser::parseEntityFromXml(const std::string &xml)
    {
        auto entity = std::make_shared<Entity>();

        entity->id = extractAttribute(xml, "entity", "id", generateEntityId("entity", entityCounter_++));
        entity->name = extractAttribute(xml, "entity", "name", entity->id);
        entity->type = extractAttribute(xml, "entity", "type", "mesh");

        // Parse transform
        auto transformSection = extractSection(xml, "transform");
        entity->transform = parseTransformFromXml(transformSection);

        // Parse component references
        entity->meshId = extractAttribute(xml, "entity", "mesh", "");
        entity->materialId = extractAttribute(xml, "entity", "material", "");
        entity->lightId = extractAttribute(xml, "entity", "light", "");
        entity->cameraId = extractAttribute(xml, "entity", "camera", "");

        // Parse animation
        entity->animated = extractBoolAttribute(xml, "entity", "animated", false);
        if (entity->animated)
        {
            entity->animationId = extractAttribute(xml, "entity", "animationId", "");
        }

        // Parse properties
        auto propertiesSection = extractSection(xml, "properties");
        entity->properties = parsePropertiesMap(propertiesSection);

        // Parse child entities
        auto childrenSection = extractSection(xml, "children");
        auto childElements = extractElements(childrenSection, "entity");
        for (const auto &childXml : childElements)
        {
            auto child = parseEntityFromXml(childXml);
            if (child)
            {
                entity->children.push_back(child);
                entityLookup_[child->id] = child;
            }
        }

        return entity;
    }

    std::map<std::string, std::string> SceneConfigParser::parsePropertiesMap(const std::string &xml)
    {
        std::map<std::string, std::string> properties;

        // Extract property elements
        auto propertyElements = extractElements(xml, "property");
        for (const auto &propertyXml : propertyElements)
        {
            std::string name = extractAttribute(propertyXml, "property", "name", "");
            std::string value = extractAttribute(propertyXml, "property", "value", "");
            if (!name.empty())
            {
                properties[name] = value;
            }
        }

        return properties;
    }

    std::string SceneConfigParser::extractSection(const std::string &xml, const std::string &sectionName)
    {
        // Simplified section extraction
        std::regex pattern("<" + sectionName + R"(\s*[^>]*>.*?</)" + sectionName + ">");
        std::smatch match;
        if (std::regex_search(xml, match, pattern))
        {
            return match[0].str();
        }
        return "";
    }

    std::vector<std::string> SceneConfigParser::extractElements(const std::string &xml, const std::string &elementName)
    {
        std::vector<std::string> elements;
        std::regex pattern("<" + elementName + R"(\s*[^>]*>.*?</)" + elementName + ">");
        std::sregex_iterator iter(xml.begin(), xml.end(), pattern);
        std::sregex_iterator end;

        for ( iter != end; ++iter)
        {
            elements.push_back(iter->str());
        }

        return elements;
    }

    // ============================================================================
    // ID Generation Methods
    // ============================================================================

    std::string SceneConfigParser::generateEntityId(const std::string &type, uint32_t index)
    {
        return type + "_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateMaterialId(uint32_t index)
    {
        return "material_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateTextureId(uint32_t index)
    {
        return "texture_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateAnimationId(uint32_t index)
    {
        return "animation_" + std::to_string(index);
    }

    // ============================================================================
    // Validation Methods (simplified)
    // ============================================================================

    bool SceneConfigParser::validateSceneStructure(const Scene &scene, std::vector<std::string> &errors)
    {
        bool isValid = true;

        // Check for required elements
        if (scene.cameras.empty())
        {
            errors.push_back("Scene must have at least one camera");
            isValid = false;
        }

        // Validate entity references
        for (const auto &entity : scene.rootEntities)
        {
            if (!validateEntityReferences(*entity, scene, errors))
            {
                isValid = false;
            }
        }

        return isValid;
    }

    bool SceneConfigParser::validateEntityReferences(const Entity &entity, const Scene &scene, std::vector<std::string> &errors)
    {
        bool isValid = true;

        // Check mesh reference
        if (!entity.meshId.empty())
        {
            bool found = false;
            for (const auto &mesh : scene.meshes)
            {
                if (mesh.id == entity.meshId)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                errors.push_back("Entity '" + entity.id + "' references unknown mesh '" + entity.meshId + "'");
                isValid = false;
            }
        }

        // Check material reference
        if (!entity.materialId.empty())
        {
            bool found = false;
            for (const auto &material : scene.materials)
            {
                if (material.id == entity.materialId)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                errors.push_back("Entity '" + entity.id + "' references unknown material '" + entity.materialId + "'");
                isValid = false;
            }
        }

        // Validate children recursively
        for (const auto &child : entity.children)
        {
            if (!validateEntityReferences(*child, scene, errors))
            {
                isValid = false;
            }
        }

        return isValid;
    }

    // ============================================================================
    // Static Factory Methods
    // ============================================================================

    std::shared_ptr<Entity> SceneConfigParser::createEntity(const std::string &id, const std::string &type)
    {
        auto entity = std::make_shared<Entity>();
        entity->id = id;
        entity->name = id;
        entity->type = type;
        return entity;
    }

    Material SceneConfigParser::createMaterial(const std::string &id, const std::string &shader)
    {
        Material material;
        material.id = id;
        material.name = id;
        material.shader = shader;
        return material;
    }

    ProceduralTexture SceneConfigParser::createTexture(const std::string &id, const std::string &type)
    {
        ProceduralTexture texture;
        texture.id = id;
        texture.name = id;
        texture.type = type;
        return texture;
    }

    Animation SceneConfigParser::createAnimation(const std::string &id, const std::string &type)
    {
        Animation animation;
        animation.id = id;
        animation.name = id;
        animation.type = type;
        return animation;
    }

    Camera SceneConfigParser::createCamera(const std::string &id)
    {
        Camera camera;
        camera.id = id;
        // Set default camera position (looking at origin from a distance)
        camera.transform.position = {0.0f, 0.0f, 5.0f};
        return camera;
    }

    Light SceneConfigParser::createLight(const std::string &id, Light::Type type)
    {
        Light light;
        light.id = id;
        light.name = id;
        light.type = type;
        return light;
    }

} // namespace SceneConfig


