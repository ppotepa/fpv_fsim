#include "AssetManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <pugixml.hpp>

AssetManager::AssetManager() {
    // Initialize with default paths, will be overridden in initialize()
    internalAssetsPath = "internal_assets";
    userAssetsPath = "assets";
}

AssetManager::~AssetManager() {
    // Cleanup if needed
}

bool AssetManager::initialize(const std::string& internalAssetsPath, const std::string& userAssetsPath) {
    this->internalAssetsPath = internalAssetsPath;
    this->userAssetsPath = userAssetsPath;
    
    // Load internal assets first, then user assets
    bool internalLoaded = loadInternalAssets();
    bool userLoaded = loadUserAssets();
    
    initialized = internalLoaded; // We at least need the internal assets
    
    return initialized;
}

std::string AssetManager::getAssetPath(const std::string& assetId) const {
    // First check user assets (they take precedence)
    auto userIt = userAssets.find(assetId);
    if (userIt != userAssets.end()) {
        return userIt->second.path;
    }
    
    // Then check internal assets
    auto internalIt = internalAssets.find(assetId);
    if (internalIt != internalAssets.end()) {
        return internalIt->second.path;
    }
    
    // If not found, return empty string
    return "";
}

std::string AssetManager::getInternalAssetPath(const std::string& assetId) const {
    auto it = internalAssets.find(assetId);
    if (it != internalAssets.end()) {
        return it->second.path;
    }
    return "";
}

std::string AssetManager::getUserAssetPath(const std::string& assetId) const {
    auto it = userAssets.find(assetId);
    if (it != userAssets.end()) {
        return it->second.path;
    }
    return "";
}

bool AssetManager::assetExists(const std::string& assetId) const {
    return userAssetExists(assetId) || internalAssetExists(assetId);
}

bool AssetManager::internalAssetExists(const std::string& assetId) const {
    return internalAssets.find(assetId) != internalAssets.end();
}

bool AssetManager::userAssetExists(const std::string& assetId) const {
    return userAssets.find(assetId) != userAssets.end();
}

AssetManager::AssetType AssetManager::stringToAssetType(const std::string& typeString) {
    if (typeString == "texture") return AssetType::TEXTURE;
    if (typeString == "font") return AssetType::FONT;
    if (typeString == "audio") return AssetType::AUDIO;
    if (typeString == "material") return AssetType::MATERIAL;
    if (typeString == "mesh") return AssetType::MESH;
    if (typeString == "shader") return AssetType::SHADER;
    if (typeString == "scene") return AssetType::SCENE;
    return AssetType::UNKNOWN;
}

std::string AssetManager::assetTypeToString(AssetType type) {
    switch (type) {
        case AssetType::TEXTURE: return "texture";
        case AssetType::FONT: return "font";
        case AssetType::AUDIO: return "audio";
        case AssetType::MATERIAL: return "material";
        case AssetType::MESH: return "mesh";
        case AssetType::SHADER: return "shader";
        case AssetType::SCENE: return "scene";
        default: return "unknown";
    }
}

std::string AssetManager::getFallbackAssetId(AssetType type) const {
    auto it = fallbackAssets.find(type);
    if (it != fallbackAssets.end()) {
        return it->second;
    }
    // If no fallback is defined for this type, use the most generic error asset
    return "texture.error";
}

std::string AssetManager::getFallbackAssetPath(AssetType type) const {
    std::string fallbackId = getFallbackAssetId(type);
    return getAssetPath(fallbackId);
}

std::vector<std::string> AssetManager::getAllAssetIds() const {
    std::vector<std::string> ids;
    
    // Add all internal asset IDs
    for (const auto& pair : internalAssets) {
        ids.push_back(pair.first);
    }
    
    // Add all user asset IDs that don't already exist in the vector
    for (const auto& pair : userAssets) {
        if (std::find(ids.begin(), ids.end(), pair.first) == ids.end()) {
            ids.push_back(pair.first);
        }
    }
    
    return ids;
}

bool AssetManager::loadInternalAssets() {
    try {
        // Load the internal assets configuration file
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file((internalAssetsPath + "/core/internal_assets.xml").c_str());
        
        if (!result) {
            std::cerr << "Failed to load internal assets configuration: " << result.description() << std::endl;
            return false;
        }
        
        // Process core assets
        pugi::xml_node rootNode = doc.child("internal_assets");
        for (pugi::xml_node assetNode : rootNode.children("asset")) {
            std::string id = assetNode.attribute("id").value();
            std::string typeStr = assetNode.attribute("type").value();
            
            // Get the path from child element or attribute
            std::string relativePath;
            pugi::xml_node pathNode = assetNode.child("path");
            if (pathNode) {
                relativePath = pathNode.text().get();
            } else if (assetNode.attribute("path")) {
                relativePath = assetNode.attribute("path").value();
            } else {
                std::cerr << "Asset " << id << " has no path specified" << std::endl;
                continue;
            }
            
            std::string fullPath = internalAssetsPath + "/" + relativePath;
            AssetType type = stringToAssetType(typeStr);
            
            AssetInfo info;
            info.id = id;
            info.path = fullPath;
            info.type = type;
            info.isInternal = true;
            
            internalAssets[id] = info;
        }
        
        // Process fallback assets
        pugi::xml_node fallbacksNode = rootNode.child("fallbacks");
        if (fallbacksNode) {
            for (pugi::xml_node fallbackNode : fallbacksNode.children("fallback")) {
                std::string typeStr = fallbackNode.attribute("type").value();
                std::string id = fallbackNode.attribute("asset_id").value();
                std::string relativePath = fallbackNode.attribute("path").value();
                
                AssetType type = stringToAssetType(typeStr);
                std::string fullPath = internalAssetsPath + "/" + relativePath;
                
                fallbackAssets[type] = id;
                
                AssetInfo info;
                info.id = id;
                info.path = fullPath;
                info.type = type;
                info.isInternal = true;
                
                internalAssets[id] = info;
            }
        }
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading internal assets: " << e.what() << std::endl;
        return false;
    }
}

bool AssetManager::loadUserAssets() {
    try {
        // For each package in the user assets directory, load its configuration
        fs::path packagesPath = fs::path(userAssetsPath) / "packages";
        
        if (!fs::exists(packagesPath)) {
            // No user packages, that's OK
            return true;
        }
        
        for (const auto& entry : fs::directory_iterator(packagesPath)) {
            if (entry.is_directory()) {
                fs::path packageConfig = entry.path() / "package.xml";
                
                if (fs::exists(packageConfig)) {
                    pugi::xml_document doc;
                    pugi::xml_parse_result result = doc.load_file(packageConfig.string().c_str());
                    
                    if (result) {
                        // Process assets in this package
                        pugi::xml_node assetsNode = doc.child("package").child("assets");
                        for (pugi::xml_node assetNode : assetsNode.children("asset")) {
                            std::string id = assetNode.attribute("id").value();
                            std::string typeStr = assetNode.attribute("type").value();
                            
                            AssetType type = stringToAssetType(typeStr);
                            
                            // The path could be specified directly or in a child element
                            std::string relativePath;
                            pugi::xml_node pathNode = assetNode.child("path");
                            
                            if (pathNode) {
                                relativePath = pathNode.text().get();
                            }
                            else if (assetNode.attribute("path")) {
                                relativePath = assetNode.attribute("path").value();
                            }
                            else {
                                // If no path is specified, skip this asset
                                continue;
                            }
                            
                            // Construct the full path to the asset
                            std::string fullPath = entry.path().string() + "/" + relativePath;
                            
                            AssetInfo info;
                            info.id = id;
                            info.path = fullPath;
                            info.type = type;
                            info.isInternal = false;
                            
                            userAssets[id] = info;
                        }
                    }
                    else {
                        std::cerr << "Failed to load package configuration: " << packageConfig.string() << ": " 
                                  << result.description() << std::endl;
                    }
                }
            }
        }
        
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading user assets: " << e.what() << std::endl;
        return false;
    }
}
