#pragma once

#include "Package.h"
#include <string>
#include <optional>
#include <memory>

namespace Assets {

// XML parsing result
struct PackageLoadResult {
    bool success = false;
    Package package;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// Simple XML node representation
struct XmlNode {
    std::string name;
    std::unordered_map<std::string, std::string> attributes;
    std::string content;
    std::vector<std::unique_ptr<XmlNode>> children;
    
    // Utility methods
    std::string getAttribute(const std::string& name, const std::string& defaultValue = "") const {
        auto it = attributes.find(name);
        return (it != attributes.end()) ? it->second : defaultValue;
    }
    
    const XmlNode* findChild(const std::string& name) const {
        for (const auto& child : children) {
            if (child->name == name) {
                return child.get();
            }
        }
        return nullptr;
    }
    
    std::vector<const XmlNode*> findChildren(const std::string& name) const {
        std::vector<const XmlNode*> result;
        for (const auto& child : children) {
            if (child->name == name) {
                result.push_back(child.get());
            }
        }
        return result;
    }
};

// Package XML parser
class PackageParser {
public:
    // Load and parse a package from XML file
    PackageLoadResult loadPackage(const std::string& packagePath);
    
private:
    // XML parsing methods
    std::unique_ptr<XmlNode> parseXmlFile(const std::string& filePath);
    std::unique_ptr<XmlNode> parseXmlContent(const std::string& content);
    bool parseElement(const std::string& content, size_t& pos, XmlNode& node);
    
    // Package parsing methods
    bool parsePackageMetadata(const XmlNode& root, Package& package, PackageLoadResult& result);
    bool parseAssets(const XmlNode& root, Package& package, PackageLoadResult& result);
    bool parseScenes(const XmlNode& root, Package& package, PackageLoadResult& result);
    
    // Asset parsing methods
    std::optional<AssetDefinition> parseAsset(const XmlNode& assetNode, PackageLoadResult& result);
    std::optional<MaterialAssetData> parseMaterialAsset(const XmlNode& node, PackageLoadResult& result);
    std::optional<MeshAssetData> parseMeshAsset(const XmlNode& node, PackageLoadResult& result);
    std::optional<TextureAssetData> parseTextureAsset(const XmlNode& node, PackageLoadResult& result);
    std::optional<ShaderAssetData> parseShaderAsset(const XmlNode& node, PackageLoadResult& result);
    std::optional<AudioAssetData> parseAudioAsset(const XmlNode& node, PackageLoadResult& result);
    
    // Scene parsing methods
    std::optional<SceneDefinition> parseScene(const XmlNode& sceneNode, PackageLoadResult& result);
    std::optional<EntityDefinition> parseEntity(const XmlNode& entityNode, PackageLoadResult& result);
    std::optional<Component> parseComponent(const XmlNode& componentNode, PackageLoadResult& result);
    Transform parseTransform(const XmlNode& transformNode);
    BehaviorParams parseBehaviorParams(const XmlNode& paramsNode);
    
    // Utility methods
    AssetType getAssetTypeFromName(const std::string& typeName);
    ComponentType getComponentTypeFromName(const std::string& typeName);
    std::string trim(const std::string& str);
    
    // Error handling
    void addError(PackageLoadResult& result, const std::string& error);
    void addWarning(PackageLoadResult& result, const std::string& warning);
};

} // namespace Assets
