#include "PackageJsonParser.h"
#include "platform/NlohmannJsonParser.h"
#include <fstream>
#include <iostream>

namespace Assets
{

    PackageJsonParser::PackageJsonParser()
        : jsonParser_(std::make_unique<NlohmannJsonParser>())
    {
    }

    PackageJsonParser::PackageJsonParser(std::unique_ptr<IJsonParserUnified> parser)
        : jsonParser_(std::move(parser))
    {
    }

    PackageLoadResult PackageJsonParser::loadPackage(const std::string &packagePath)
    {
        PackageLoadResult result;

        if (!jsonParser_->loadFile(packagePath))
        {
            result.errors = jsonParser_->getErrors();
            result.success = false;
            return result;
        }

        const auto &rootJson = jsonParser_->getRootJson();

        if (!validatePackageJson(rootJson))
        {
            result.errors = jsonParser_->getErrors();
            result.warnings = jsonParser_->getWarnings();
            result.success = false;
            return result;
        }

        // Parse package data
        bool success = true;
        success &= parsePackageMetadata(rootJson, result.package);
        success &= parseDependencies(rootJson, result.package);
        success &= parseAssets(rootJson, result.package);
        success &= parseScenes(rootJson, result.package);

        result.errors = jsonParser_->getErrors();
        result.warnings = jsonParser_->getWarnings();
        result.success = success && !jsonParser_->hasErrors();

        return result;
    }

    PackageLoadResult PackageJsonParser::loadPackageFromString(const std::string &jsonContent)
    {
        PackageLoadResult result;

        if (!jsonParser_->loadString(jsonContent))
        {
            result.errors = jsonParser_->getErrors();
            result.success = false;
            return result;
        }

        const auto &rootJson = jsonParser_->getRootJson();

        if (!validatePackageJson(rootJson))
        {
            result.errors = jsonParser_->getErrors();
            result.warnings = jsonParser_->getWarnings();
            result.success = false;
            return result;
        }

        // Parse package data
        bool success = true;
        success &= parsePackageMetadata(rootJson, result.package);
        success &= parseDependencies(rootJson, result.package);
        success &= parseAssets(rootJson, result.package);
        success &= parseScenes(rootJson, result.package);

        result.errors = jsonParser_->getErrors();
        result.warnings = jsonParser_->getWarnings();
        result.success = success && !jsonParser_->hasErrors();

        return result;
    }

    bool PackageJsonParser::validatePackageJson(const nlohmann::json &json)
    {
        // Basic validation - check required fields
        if (!json.is_object())
        {
            addError("Package JSON must be an object");
            return false;
        }

        if (!json.contains("metadata"))
        {
            addError("Package JSON missing required 'metadata' section");
            return false;
        }

        if (!json.contains("assets") && !json.contains("scenes"))
        {
            addWarning("Package contains no assets or scenes");
        }

        const auto &metadata = json["metadata"];
        if (!metadata.contains("id") || !metadata.contains("name") || !metadata.contains("version"))
        {
            addError("Package metadata missing required fields (id, name, version)");
            return false;
        }

        return true;
    }

    bool PackageJsonParser::parsePackageMetadata(const nlohmann::json &json, Package &package)
    {
        if (!json.contains("metadata"))
            return false;

        const auto &metadata = json["metadata"];

        package.metadata.id = metadata.value("id", "");
        package.metadata.name = metadata.value("name", "");
        package.metadata.version = metadata.value("version", "1.0.0");
        package.metadata.description = metadata.value("description", "");
        package.metadata.author = metadata.value("author", "");

        if (package.metadata.id.empty() || package.metadata.name.empty())
        {
            addError("Package ID and name cannot be empty");
            return false;
        }

        return true;
    }

    bool PackageJsonParser::parseDependencies(const nlohmann::json &json, Package &package)
    {
        if (!json.contains("dependencies"))
            return true; // Dependencies are optional

        const auto &deps = json["dependencies"];
        if (!deps.is_array())
        {
            addError("Dependencies must be an array");
            return false;
        }

        for (const auto &depJson : deps)
        {
            if (!depJson.is_object())
            {
                addWarning("Skipping invalid dependency entry");
                continue;
            }

            PackageDependency dep;
            dep.packageId = depJson.value("id", "");
            dep.version = depJson.value("version", "");
            dep.required = depJson.value("required", true);

            if (!dep.packageId.empty() && !dep.version.empty())
            {
                package.metadata.dependencies.push_back(dep);
            }
            else
            {
                addWarning("Skipping dependency with missing id or version");
            }
        }

        return true;
    }

    bool PackageJsonParser::parseAssets(const nlohmann::json &json, Package &package)
    {
        if (!json.contains("assets"))
            return true; // Assets are optional at package level

        const auto &assets = json["assets"];
        if (!assets.is_object())
        {
            addError("Assets section must be an object");
            return false;
        }

        // Parse different asset types
        if (assets.contains("textures") && assets["textures"].is_array())
        {
            for (const auto &textureJson : assets["textures"])
            {
                package.assets.push_back(parseAssetDefinition(textureJson, AssetType::Texture));
            }
        }

        if (assets.contains("materials") && assets["materials"].is_array())
        {
            for (const auto &materialJson : assets["materials"])
            {
                package.assets.push_back(parseAssetDefinition(materialJson, AssetType::Material));
            }
        }

        if (assets.contains("meshes") && assets["meshes"].is_array())
        {
            for (const auto &meshJson : assets["meshes"])
            {
                package.assets.push_back(parseAssetDefinition(meshJson, AssetType::Mesh));
            }
        }

        if (assets.contains("shaders") && assets["shaders"].is_array())
        {
            for (const auto &shaderJson : assets["shaders"])
            {
                package.assets.push_back(parseAssetDefinition(shaderJson, AssetType::Shader));
            }
        }

        if (assets.contains("audio") && assets["audio"].is_array())
        {
            for (const auto &audioJson : assets["audio"])
            {
                package.assets.push_back(parseAssetDefinition(audioJson, AssetType::Audio));
            }
        }

        return true;
    }

    bool PackageJsonParser::parseScenes(const nlohmann::json &json, Package &package)
    {
        if (!json.contains("scenes"))
            return true; // Scenes are optional

        const auto &scenes = json["scenes"];
        if (!scenes.is_array())
        {
            addError("Scenes section must be an array");
            return false;
        }

        for (const auto &sceneJson : scenes)
        {
            package.scenes.push_back(parseSceneDefinition(sceneJson));
        }

        return true;
    }

    AssetDefinition PackageJsonParser::parseAssetDefinition(const nlohmann::json &json, AssetType type)
    {
        AssetDefinition asset;
        asset.id = json.value("id", "");
        asset.path = json.value("path", "");
        asset.type = type;

        switch (type)
        {
        case AssetType::Texture:
            asset.data = parseTextureAssetData(json);
            break;
        case AssetType::Material:
            asset.data = parseMaterialAssetData(json);
            break;
        case AssetType::Mesh:
            asset.data = parseMeshAssetData(json);
            break;
        case AssetType::Shader:
            asset.data = parseShaderAssetData(json);
            break;
        case AssetType::Audio:
            asset.data = parseAudioAssetData(json);
            break;
        default:
            addWarning("Unknown asset type for asset: " + asset.id);
            break;
        }

        return asset;
    }

    TextureAssetData PackageJsonParser::parseTextureAssetData(const nlohmann::json &json)
    {
        TextureAssetData data;
        data.sourcePath = json.value("path", "");
        data.generateMipmaps = json.value("generateMipmaps", true);
        data.compressionFormat = json.value("compressionFormat", "auto");
        data.compressionQuality = json.value("compressionQuality", 85);
        return data;
    }

    MaterialAssetData PackageJsonParser::parseMaterialAssetData(const nlohmann::json &json)
    {
        MaterialAssetData data;
        data.shaderReference = json.value("shader", "");

        if (json.contains("textures") && json["textures"].is_object())
        {
            for (const auto &[key, value] : json["textures"].items())
            {
                if (value.is_string())
                    data.textureReferences[key] = value.get<std::string>();
            }
        }

        if (json.contains("properties") && json["properties"].is_object())
        {
            for (const auto &[key, value] : json["properties"].items())
            {
                if (value.is_string())
                    data.properties[key] = value.get<std::string>();
                else if (value.is_number())
                    data.properties[key] = std::to_string(value.get<float>());
                else if (value.is_boolean())
                    data.properties[key] = value.get<bool>() ? "true" : "false";
            }
        }

        return data;
    }

    MeshAssetData PackageJsonParser::parseMeshAssetData(const nlohmann::json &json)
    {
        MeshAssetData data;
        data.sourcePath = json.value("path", "");
        data.optimize = json.value("optimize", true);
        data.generateTangents = json.value("generateTangents", false);
        data.optimizationLevel = json.value("optimizationLevel", 1);
        return data;
    }

    ShaderAssetData PackageJsonParser::parseShaderAssetData(const nlohmann::json &json)
    {
        ShaderAssetData data;
        data.vertexShaderPath = json.value("vertex", "");
        data.fragmentShaderPath = json.value("fragment", "");
        data.geometryShaderPath = json.value("geometry", "");

        if (json.contains("defines") && json["defines"].is_array())
        {
            for (const auto &define : json["defines"])
            {
                if (define.is_string())
                    data.defines.push_back(define.get<std::string>());
            }
        }

        return data;
    }

    AudioAssetData PackageJsonParser::parseAudioAssetData(const nlohmann::json &json)
    {
        AudioAssetData data;
        data.sourcePath = json.value("path", "");
        data.compressed = json.value("compressed", true);
        data.sampleRate = json.value("sampleRate", 44100);
        data.bitDepth = json.value("bitDepth", 16);
        return data;
    }

    SceneDefinition PackageJsonParser::parseSceneDefinition(const nlohmann::json &json)
    {
        SceneDefinition scene;
        scene.id = json.value("id", "");
        scene.name = json.value("name", "");

        if (json.contains("entities") && json["entities"].is_array())
        {
            for (const auto &entityJson : json["entities"])
            {
                scene.entities.push_back(parseEntityDefinition(entityJson));
            }
        }

        return scene;
    }

    EntityDefinition PackageJsonParser::parseEntityDefinition(const nlohmann::json &json)
    {
        EntityDefinition entity;
        entity.id = json.value("id", "");
        entity.name = json.value("name", "");

        if (json.contains("transform"))
        {
            entity.transform = parseTransform(json["transform"]);
        }

        if (json.contains("components") && json["components"].is_object())
        {
            const auto &components = json["components"];

            // Parse different component types
            if (components.contains("mesh"))
            {
                entity.components.push_back(parseComponent(components["mesh"], ComponentType::Mesh));
            }
            if (components.contains("material"))
            {
                entity.components.push_back(parseComponent(components["material"], ComponentType::Material));
            }
            if (components.contains("renderable"))
            {
                entity.components.push_back(parseComponent(components["renderable"], ComponentType::Renderable));
            }
            if (components.contains("physics"))
            {
                entity.components.push_back(parseComponent(components["physics"], ComponentType::Physics));
            }
            if (components.contains("audio"))
            {
                entity.components.push_back(parseComponent(components["audio"], ComponentType::Audio));
            }
        }

        if (json.contains("behavior"))
        {
            const auto &behavior = json["behavior"];
            entity.behaviorClass = behavior.value("type", "");
            entity.behaviorParams = parseBehaviorParams(behavior);
        }

        return entity;
    }

    Component PackageJsonParser::parseComponent(const nlohmann::json &json, ComponentType type)
    {
        Component component;
        component.type = type;

        switch (type)
        {
        case ComponentType::Mesh:
        {
            MeshComponent meshComp;
            meshComp.assetRef = json.value("asset", "");
            component.data = meshComp;
            break;
        }
        case ComponentType::Material:
        {
            MaterialComponent materialComp;
            materialComp.assetRef = json.value("asset", "");
            component.data = materialComp;
            break;
        }
        case ComponentType::Renderable:
        {
            RenderableComponent renderComp;
            renderComp.visible = json.value("visible", true);
            renderComp.castShadows = json.value("castShadows", true);
            renderComp.receiveShadows = json.value("receiveShadows", true);
            renderComp.lodBias = json.value("lodBias", 1.0f);
            component.data = renderComp;
            break;
        }
        case ComponentType::Physics:
        {
            PhysicsComponent physicsComp;
            physicsComp.mass = json.value("mass", 1.0f);
            physicsComp.friction = json.value("friction", 0.8f);
            physicsComp.restitution = json.value("restitution", 0.2f);
            physicsComp.isStatic = json.value("isStatic", false);

            if (json.contains("centerOfMass") && json["centerOfMass"].is_array() && json["centerOfMass"].size() >= 3)
            {
                const auto &com = json["centerOfMass"];
                physicsComp.centerOfMass.x = com[0].get<float>();
                physicsComp.centerOfMass.y = com[1].get<float>();
                physicsComp.centerOfMass.z = com[2].get<float>();
            }

            component.data = physicsComp;
            break;
        }
        case ComponentType::Audio:
        {
            AudioComponent audioComp;
            audioComp.assetRef = json.value("asset", "");
            audioComp.autoPlay = json.value("autoPlay", false);
            audioComp.loop = json.value("loop", false);
            audioComp.volume = json.value("volume", 1.0f);
            audioComp.pitch = json.value("pitch", 1.0f);
            component.data = audioComp;
            break;
        }
        default:
            addWarning("Unknown component type");
            break;
        }

        return component;
    }

    Transform PackageJsonParser::parseTransform(const nlohmann::json &json)
    {
        Transform transform;

        if (json.contains("position") && json["position"].is_array() && json["position"].size() >= 3)
        {
            const auto &pos = json["position"];
            transform.position.x = pos[0].get<float>();
            transform.position.y = pos[1].get<float>();
            transform.position.z = pos[2].get<float>();
        }

        if (json.contains("rotation") && json["rotation"].is_array() && json["rotation"].size() >= 4)
        {
            const auto &rot = json["rotation"];
            transform.rotation.x = rot[0].get<float>();
            transform.rotation.y = rot[1].get<float>();
            transform.rotation.z = rot[2].get<float>();
            transform.rotation.w = rot[3].get<float>();
        }

        if (json.contains("scale") && json["scale"].is_array() && json["scale"].size() >= 3)
        {
            const auto &scale = json["scale"];
            transform.scale.x = scale[0].get<float>();
            transform.scale.y = scale[1].get<float>();
            transform.scale.z = scale[2].get<float>();
        }

        return transform;
    }

    BehaviorParams PackageJsonParser::parseBehaviorParams(const nlohmann::json &json)
    {
        BehaviorParams params;

        if (json.contains("parameters") && json["parameters"].is_object())
        {
            for (const auto &[key, value] : json["parameters"].items())
            {
                if (value.is_string())
                    params.setParameter(key, value.get<std::string>());
                else if (value.is_number_float())
                    params.setParameter(key, std::to_string(value.get<float>()));
                else if (value.is_number_integer())
                    params.setParameter(key, std::to_string(value.get<int>()));
                else if (value.is_boolean())
                    params.setParameter(key, value.get<bool>() ? "true" : "false");
            }
        }

        return params;
    }

    void PackageJsonParser::addError(const std::string &error)
    {
        jsonParser_->addError(error);
    }

    void PackageJsonParser::addWarning(const std::string &warning)
    {
        jsonParser_->addWarning(warning);
    }

} // namespace Assets
