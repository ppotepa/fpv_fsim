#include "PackageParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace Assets {

PackageLoadResult PackageParser::loadPackage(const std::string& packagePath) {
    PackageLoadResult result;
    
    try {
        // Parse XML file
        auto xmlRoot = parseXmlFile(packagePath);
        if (!xmlRoot) {
            addError(result, "Failed to parse XML file: " + packagePath);
            return result;
        }
        
        // Set source path
        result.package.sourcePath = packagePath;
        
        // Parse package metadata
        if (!parsePackageMetadata(*xmlRoot, result.package, result)) {
            return result;
        }
        
        // Parse assets section
        if (!parseAssets(*xmlRoot, result.package, result)) {
            return result;
        }
        
        // Parse scenes section
        if (!parseScenes(*xmlRoot, result.package, result)) {
            return result;
        }
        
        result.success = result.errors.empty();
        
    } catch (const std::exception& e) {
        addError(result, "Exception during parsing: " + std::string(e.what()));
    }
    
    return result;
}

std::unique_ptr<XmlNode> PackageParser::parseXmlFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    return parseXmlContent(content);
}

std::unique_ptr<XmlNode> PackageParser::parseXmlContent(const std::string& content) {
    // Simple XML parser implementation
    // Note: This is a basic implementation. For production, consider using a proper XML library like pugixml
    
    auto root = std::make_unique<XmlNode>();
    size_t pos = 0;
    
    // Find the root element (skip XML declaration)
    pos = content.find('<', pos);
    if (pos == std::string::npos) return nullptr;
    
    // Skip XML declaration if present
    if (content.substr(pos, 5) == "<?xml") {
        pos = content.find('>', pos);
        if (pos == std::string::npos) return nullptr;
        pos++;
        pos = content.find('<', pos);
        if (pos == std::string::npos) return nullptr;
    }
    
    // Parse the root element
    parseElement(content, pos, *root);
    
    return root;
}

bool PackageParser::parseElement(const std::string& content, size_t& pos, XmlNode& node) {
    // This is a simplified XML parser - in production, use a proper XML library
    
    if (pos >= content.length() || content[pos] != '<') {
        return false;
    }
    
    size_t tagStart = pos + 1;
    size_t tagEnd = content.find('>', tagStart);
    if (tagEnd == std::string::npos) return false;
    
    std::string tag = content.substr(tagStart, tagEnd - tagStart);
    
    // Check for self-closing tag
    bool selfClosing = tag.back() == '/';
    if (selfClosing) {
        tag.pop_back();
    }
    
    // Parse tag name and attributes
    std::istringstream tagStream(tag);
    tagStream >> node.name;
    
    // Parse attributes (simplified)
    std::string attr;
    while (tagStream >> attr) {
        size_t eqPos = attr.find('=');
        if (eqPos != std::string::npos) {
            std::string key = attr.substr(0, eqPos);
            std::string value = attr.substr(eqPos + 1);
            // Remove quotes
            if (value.front() == '"' && value.back() == '"') {
                value = value.substr(1, value.length() - 2);
            }
            node.attributes[key] = value;
        }
    }
    
    pos = tagEnd + 1;
    
    if (selfClosing) {
        return true;
    }
    
    // Parse content and children
    std::string closeTag = "</" + node.name + ">";
    size_t closePos = content.find(closeTag, pos);
    if (closePos == std::string::npos) return false;
    
    std::string innerContent = content.substr(pos, closePos - pos);
    
    // Check if this is a text node or has children
    size_t childStart = innerContent.find('<');
    if (childStart == std::string::npos) {
        // Text content
        node.content = trim(innerContent);
    } else {
        // Parse children
        size_t childPos = 0;
        while (childPos < innerContent.length()) {
            childPos = innerContent.find('<', childPos);
            if (childPos == std::string::npos) break;
            
            auto child = std::make_unique<XmlNode>();
            if (parseElement(innerContent, childPos, *child)) {
                node.children.push_back(std::move(child));
            } else {
                break;
            }
        }
    }
    
    pos = closePos + closeTag.length();
    return true;
}

bool PackageParser::parsePackageMetadata(const XmlNode& root, Package& package, PackageLoadResult& result) {
    if (root.name != "package") {
        addError(result, "Root element must be 'package'");
        return false;
    }
    
    package.metadata.id = root.getAttribute("id");
    package.metadata.name = root.getAttribute("name");
    package.metadata.version = root.getAttribute("version");
    
    if (package.metadata.id.empty()) {
        addError(result, "Package must have an 'id' attribute");
        return false;
    }
    
    // Parse metadata section if present
    const auto* metadataNode = root.findChild("metadata");
    if (metadataNode) {
        const auto* descNode = metadataNode->findChild("description");
        if (descNode) {
            package.metadata.description = descNode->content;
        }
        
        const auto* authorNode = metadataNode->findChild("author");
        if (authorNode) {
            package.metadata.author = authorNode->content;
        }
        
        // Parse dependencies
        const auto* depsNode = metadataNode->findChild("dependencies");
        if (depsNode) {
            auto depNodes = depsNode->findChildren("dependency");
            for (const auto* depNode : depNodes) {
                PackageDependency dep;
                dep.packageId = depNode->getAttribute("package");
                dep.version = depNode->getAttribute("version");
                dep.required = depNode->getAttribute("required", "true") == "true";
                
                if (!dep.packageId.empty()) {
                    package.metadata.dependencies.push_back(dep);
                }
            }
        }
    }
    
    return true;
}

bool PackageParser::parseAssets(const XmlNode& root, Package& package, PackageLoadResult& result) {
    const auto* assetsNode = root.findChild("assets");
    if (!assetsNode) {
        // Assets section is optional
        return true;
    }
    
    for (const auto& child : assetsNode->children) {
        auto asset = parseAsset(*child, result);
        if (asset.has_value()) {
            package.assets.push_back(asset.value());
        }
    }
    
    return true;
}

bool PackageParser::parseScenes(const XmlNode& root, Package& package, PackageLoadResult& result) {
    const auto* scenesNode = root.findChild("scenes");
    if (!scenesNode) {
        // Scenes section is optional
        return true;
    }
    
    auto sceneNodes = scenesNode->findChildren("scene");
    for (const auto* sceneNode : sceneNodes) {
        auto scene = parseScene(*sceneNode, result);
        if (scene.has_value()) {
            package.scenes.push_back(scene.value());
        }
    }
    
    return true;
}

std::optional<AssetDefinition> PackageParser::parseAsset(const XmlNode& assetNode, PackageLoadResult& result) {
    AssetDefinition asset;
    asset.id = assetNode.getAttribute("id");
    asset.type = getAssetTypeFromName(assetNode.name);
    
    if (asset.id.empty()) {
        addError(result, "Asset must have an 'id' attribute");
        return std::nullopt;
    }
    
    switch (asset.type) {
        case AssetType::Material: {
            auto data = parseMaterialAsset(assetNode, result);
            if (!data.has_value()) return std::nullopt;
            asset.data = data.value();
            break;
        }
        case AssetType::Mesh: {
            auto data = parseMeshAsset(assetNode, result);
            if (!data.has_value()) return std::nullopt;
            asset.data = data.value();
            break;
        }
        case AssetType::Texture: {
            auto data = parseTextureAsset(assetNode, result);
            if (!data.has_value()) return std::nullopt;
            asset.data = data.value();
            break;
        }
        case AssetType::Shader: {
            auto data = parseShaderAsset(assetNode, result);
            if (!data.has_value()) return std::nullopt;
            asset.data = data.value();
            break;
        }
        case AssetType::Audio: {
            auto data = parseAudioAsset(assetNode, result);
            if (!data.has_value()) return std::nullopt;
            asset.data = data.value();
            break;
        }
        default:
            addError(result, "Unknown asset type: " + assetNode.name);
            return std::nullopt;
    }
    
    return asset;
}

std::optional<MaterialAssetData> PackageParser::parseMaterialAsset(const XmlNode& node, PackageLoadResult& result) {
    MaterialAssetData data;
    
    const auto* shaderNode = node.findChild("shader");
    if (shaderNode) {
        data.shaderReference = shaderNode->content;
    }
    
    const auto* propsNode = node.findChild("properties");
    if (propsNode) {
        for (const auto& child : propsNode->children) {
            data.properties[child->name] = child->content;
        }
    }
    
    const auto* texturesNode = node.findChild("textures");
    if (texturesNode) {
        for (const auto& child : texturesNode->children) {
            data.textureReferences[child->name] = child->content;
        }
    }
    
    return data;
}

std::optional<MeshAssetData> PackageParser::parseMeshAsset(const XmlNode& node, PackageLoadResult& result) {
    MeshAssetData data;
    
    const auto* sourceNode = node.findChild("source");
    if (sourceNode) {
        data.sourcePath = sourceNode->content;
    } else {
        addError(result, "Mesh asset must specify a source path");
        return std::nullopt;
    }
    
    data.optimize = node.getAttribute("optimize", "true") == "true";
    data.generateTangents = node.getAttribute("generateTangents", "false") == "true";
    
    return data;
}

std::optional<TextureAssetData> PackageParser::parseTextureAsset(const XmlNode& node, PackageLoadResult& result) {
    TextureAssetData data;
    
    const auto* sourceNode = node.findChild("source");
    if (sourceNode) {
        data.sourcePath = sourceNode->content;
    } else {
        addError(result, "Texture asset must specify a source path");
        return std::nullopt;
    }
    
    data.generateMipmaps = node.getAttribute("generateMipmaps", "true") == "true";
    data.compressionFormat = node.getAttribute("compressionFormat", "auto");
    
    return data;
}

std::optional<ShaderAssetData> PackageParser::parseShaderAsset(const XmlNode& node, PackageLoadResult& result) {
    ShaderAssetData data;
    
    const auto* vertexNode = node.findChild("vertex");
    if (vertexNode) {
        data.vertexShaderPath = vertexNode->content;
    }
    
    const auto* fragmentNode = node.findChild("fragment");
    if (fragmentNode) {
        data.fragmentShaderPath = fragmentNode->content;
    }
    
    const auto* geometryNode = node.findChild("geometry");
    if (geometryNode) {
        data.geometryShaderPath = geometryNode->content;
    }
    
    return data;
}

std::optional<AudioAssetData> PackageParser::parseAudioAsset(const XmlNode& node, PackageLoadResult& result) {
    AudioAssetData data;
    
    const auto* sourceNode = node.findChild("source");
    if (sourceNode) {
        data.sourcePath = sourceNode->content;
    } else {
        addError(result, "Audio asset must specify a source path");
        return std::nullopt;
    }
    
    data.compressed = node.getAttribute("compressed", "true") == "true";
    
    return data;
}

std::optional<SceneDefinition> PackageParser::parseScene(const XmlNode& sceneNode, PackageLoadResult& result) {
    SceneDefinition scene;
    scene.id = sceneNode.getAttribute("id");
    scene.name = sceneNode.getAttribute("name");
    
    if (scene.id.empty()) {
        addError(result, "Scene must have an 'id' attribute");
        return std::nullopt;
    }
    
    // Parse entities
    auto entityNodes = sceneNode.findChildren("entity");
    for (const auto* entityNode : entityNodes) {
        auto entity = parseEntity(*entityNode, result);
        if (entity.has_value()) {
            scene.entities.push_back(entity.value());
        }
    }
    
    return scene;
}

std::optional<EntityDefinition> PackageParser::parseEntity(const XmlNode& entityNode, PackageLoadResult& result) {
    EntityDefinition entity;
    entity.id = entityNode.getAttribute("id");
    entity.name = entityNode.getAttribute("name");
    entity.behaviorClass = entityNode.getAttribute("codeBehind");
    
    if (entity.id.empty()) {
        addError(result, "Entity must have an 'id' attribute");
        return std::nullopt;
    }
    
    // Parse transform
    const auto* transformNode = entityNode.findChild("transform");
    if (transformNode) {
        entity.transform = parseTransform(*transformNode);
    }
    
    // Parse components
    const auto* componentsNode = entityNode.findChild("components");
    if (componentsNode) {
        for (const auto& child : componentsNode->children) {
            auto component = parseComponent(*child, result);
            if (component.has_value()) {
                entity.components.push_back(component.value());
            }
        }
    }
    
    // Parse behavior parameters
    const auto* paramsNode = entityNode.findChild("params");
    if (paramsNode) {
        entity.behaviorParams = parseBehaviorParams(*paramsNode);
    }
    
    return entity;
}

std::optional<Component> PackageParser::parseComponent(const XmlNode& componentNode, PackageLoadResult& result) {
    Component component;
    component.type = getComponentTypeFromName(componentNode.name);
    
    switch (component.type) {
        case ComponentType::Mesh: {
            MeshComponent meshComp;
            meshComp.assetRef = componentNode.getAttribute("asset");
            component.data = meshComp;
            break;
        }
        case ComponentType::Material: {
            MaterialComponent matComp;
            matComp.assetRef = componentNode.getAttribute("asset");
            component.data = matComp;
            break;
        }
        case ComponentType::Renderable: {
            RenderableComponent rendComp;
            rendComp.visible = componentNode.getAttribute("visible", "true") == "true";
            rendComp.castShadows = componentNode.getAttribute("castShadows", "true") == "true";
            rendComp.receiveShadows = componentNode.getAttribute("receiveShadows", "true") == "true";
            component.data = rendComp;
            break;
        }
        case ComponentType::Physics: {
            PhysicsComponent physComp;
            physComp.mass = std::stof(componentNode.getAttribute("mass", "1.0"));
            physComp.friction = std::stof(componentNode.getAttribute("friction", "0.8"));
            physComp.restitution = std::stof(componentNode.getAttribute("restitution", "0.2"));
            physComp.isStatic = componentNode.getAttribute("static", "false") == "true";
            component.data = physComp;
            break;
        }
        case ComponentType::Audio: {
            AudioComponent audioComp;
            audioComp.assetRef = componentNode.getAttribute("asset");
            audioComp.autoPlay = componentNode.getAttribute("autoPlay", "false") == "true";
            audioComp.loop = componentNode.getAttribute("loop", "false") == "true";
            audioComp.volume = std::stof(componentNode.getAttribute("volume", "1.0"));
            component.data = audioComp;
            break;
        }
        default:
            addWarning(result, "Unknown component type: " + componentNode.name);
            return std::nullopt;
    }
    
    return component;
}

Transform PackageParser::parseTransform(const XmlNode& transformNode) {
    Transform transform;
    
    const auto* posNode = transformNode.findChild("position");
    if (posNode) {
        transform.position.x = std::stof(posNode->getAttribute("x", "0"));
        transform.position.y = std::stof(posNode->getAttribute("y", "0"));
        transform.position.z = std::stof(posNode->getAttribute("z", "0"));
    }
    
    const auto* rotNode = transformNode.findChild("rotation");
    if (rotNode) {
        transform.rotation.x = std::stof(rotNode->getAttribute("x", "0"));
        transform.rotation.y = std::stof(rotNode->getAttribute("y", "0"));
        transform.rotation.z = std::stof(rotNode->getAttribute("z", "0"));
        transform.rotation.w = std::stof(rotNode->getAttribute("w", "1"));
    }
    
    const auto* scaleNode = transformNode.findChild("scale");
    if (scaleNode) {
        transform.scale.x = std::stof(scaleNode->getAttribute("x", "1"));
        transform.scale.y = std::stof(scaleNode->getAttribute("y", "1"));
        transform.scale.z = std::stof(scaleNode->getAttribute("z", "1"));
    }
    
    return transform;
}

BehaviorParams PackageParser::parseBehaviorParams(const XmlNode& paramsNode) {
    BehaviorParams params;
    
    for (const auto& child : paramsNode.children) {
        params.setParameter(child->name, child->content);
    }
    
    return params;
}

ComponentType PackageParser::getComponentTypeFromName(const std::string& typeName) {
    if (typeName == "mesh") return ComponentType::Mesh;
    if (typeName == "material") return ComponentType::Material;
    if (typeName == "renderable") return ComponentType::Renderable;
    if (typeName == "physics") return ComponentType::Physics;
    if (typeName == "audio") return ComponentType::Audio;
    return ComponentType::Transform; // Default fallback
}

AssetType PackageParser::getAssetTypeFromName(const std::string& typeName) {
    if (typeName == "material") return AssetType::Material;
    if (typeName == "mesh") return AssetType::Mesh;
    if (typeName == "texture") return AssetType::Texture;
    if (typeName == "shader") return AssetType::Shader;
    if (typeName == "audio") return AssetType::Audio;
    return AssetType::Material; // Default fallback
}

std::string PackageParser::trim(const std::string& str) {
    auto start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    auto end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void PackageParser::addError(PackageLoadResult& result, const std::string& error) {
    result.errors.push_back(error);
}

void PackageParser::addWarning(PackageLoadResult& result, const std::string& warning) {
    result.warnings.push_back(warning);
}

} // namespace Assets
