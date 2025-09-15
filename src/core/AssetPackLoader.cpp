#include "AssetPackLoader.h"
#include "../utils/PugiXmlParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

AssetPackLoader::AssetPackLoader(AssetRegistry &registry)
    : registry_(registry)
{
}

AssetPackLoader::~AssetPackLoader() {}

bool AssetPackLoader::loadPackage(const std::string &packagePath)
{
    // Read XML file
    std::ifstream file(packagePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open package file: " << packagePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xmlContent = buffer.str();
    file.close();

    // Extract package name from path
    size_t lastSlash = packagePath.find_last_of("/\\");
    size_t secondLastSlash = packagePath.find_last_of("/\\", lastSlash - 1);
    std::string packageName = packagePath.substr(secondLastSlash + 1, lastSlash - secondLastSlash - 1);

    // Parse assets and configurations
    if (!parseAssets(xmlContent, packageName))
    {
        std::cerr << "Failed to parse assets from package: " << packageName << std::endl;
        return false;
    }

    if (!parseConfigurations(xmlContent, packageName))
    {
        std::cerr << "Failed to parse configurations from package: " << packageName << std::endl;
        return false;
    }

    registry_.markPackageLoaded(packageName);
    std::cout << "Successfully loaded package: " << packageName << std::endl;
    return true;
}

bool AssetPackLoader::loadDeveloperPackage()
{
    return loadPackage("assets/packages/DeveloperPackage/package.xml");
}

bool AssetPackLoader::parseAssets(const std::string &xmlContent, const std::string &packageName)
{
    // Simple XML parsing - in a real implementation this would use pugixml properly
    // For now, we'll do basic string parsing to extract asset information

    size_t assetsStart = xmlContent.find("<assets>");
    size_t assetsEnd = xmlContent.find("</assets>");

    if (assetsStart == std::string::npos || assetsEnd == std::string::npos)
    {
        return true; // No assets section is OK
    }

    std::string assetsSection = xmlContent.substr(assetsStart, assetsEnd - assetsStart);

    // Parse font assets
    size_t pos = 0;
    while ((pos = assetsSection.find("<asset type=\"font\"", pos)) != std::string::npos)
    {
        size_t endPos = assetsSection.find("</asset>", pos);
        if (endPos == std::string::npos)
            break;

        std::string assetXml = assetsSection.substr(pos, endPos - pos + 8);
        auto fontAsset = parseFontAsset(assetXml);
        if (fontAsset)
        {
            // Extract ID
            size_t idStart = assetXml.find("id=\"") + 4;
            size_t idEnd = assetXml.find("\"", idStart);
            std::string id = assetXml.substr(idStart, idEnd - idStart);

            registry_.registerFont(packageName + "::" + id, std::move(fontAsset));
        }
        pos = endPos;
    }

    // Similar parsing for other asset types would go here
    // For brevity, implementing only basic structure

    return true;
}

bool AssetPackLoader::parseConfigurations(const std::string &xmlContent, const std::string &packageName)
{
    // Find the configurations section
    size_t configStart = xmlContent.find("<configurations>");
    size_t configEnd = xmlContent.find("</configurations>");

    if (configStart == std::string::npos || configEnd == std::string::npos)
    {
        return true; // No configurations section is OK
    }

    std::string configSection = xmlContent.substr(configStart, configEnd - configStart);

    // Parse scene configurations
    size_t pos = 0;
    while ((pos = configSection.find("<scene_config", pos)) != std::string::npos)
    {
        size_t endPos = configSection.find("</scene_config>", pos);
        if (endPos == std::string::npos)
            break;

        std::string sceneXml = configSection.substr(pos, endPos - pos + 15);
        
        // Extract scene ID
        size_t idStart = sceneXml.find("id=\"") + 4;
        size_t idEnd = sceneXml.find("\"", idStart);
        std::string sceneId = sceneXml.substr(idStart, idEnd - idStart);

        // For DefaultSphereWorldScene, register it as the default scene
        if (sceneId == "DefaultSphereWorldScene")
        {
            registry_.registerSceneConfig(packageName + "::" + sceneId, sceneXml);
            registry_.setDefaultScene(packageName + "::" + sceneId);
            std::cout << "Registered default scene: " << packageName << "::" << sceneId << std::endl;
        }

        pos = endPos;
    }

    return true;
}

std::unique_ptr<FontAsset> AssetPackLoader::parseFontAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<FontAsset>();

    // Extract path
    size_t pathStart = xmlNode.find("<path>") + 6;
    size_t pathEnd = xmlNode.find("</path>", pathStart);
    if (pathStart != std::string::npos && pathEnd != std::string::npos)
    {
        asset->path = xmlNode.substr(pathStart, pathEnd - pathStart);
    }

    // Extract size
    size_t sizeStart = xmlNode.find("size=\"") + 6;
    size_t sizeEnd = xmlNode.find("\"", sizeStart);
    if (sizeStart != std::string::npos && sizeEnd != std::string::npos)
    {
        asset->size = std::stoi(xmlNode.substr(sizeStart, sizeEnd - sizeStart));
    }

    // Extract antialiasing
    size_t aaStart = xmlNode.find("antialiasing=\"") + 14;
    size_t aaEnd = xmlNode.find("\"", aaStart);
    if (aaStart != std::string::npos && aaEnd != std::string::npos)
    {
        asset->antialiasing = xmlNode.substr(aaStart, aaEnd - aaStart) == "true";
    }

    return asset;
}

std::unique_ptr<TextureAsset> AssetPackLoader::parseTextureAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<TextureAsset>();

    // Extract path
    size_t pathStart = xmlNode.find("<path>") + 6;
    size_t pathEnd = xmlNode.find("</path>", pathStart);
    if (pathStart != std::string::npos && pathEnd != std::string::npos)
    {
        asset->path = xmlNode.substr(pathStart, pathEnd - pathStart);
    }

    // Extract format
    size_t formatStart = xmlNode.find("format=\"") + 8;
    size_t formatEnd = xmlNode.find("\"", formatStart);
    if (formatStart != std::string::npos && formatEnd != std::string::npos)
    {
        asset->format = xmlNode.substr(formatStart, formatEnd - formatStart);
    }

    // Extract mipmaps
    size_t mipsStart = xmlNode.find("mipmaps=\"") + 9;
    size_t mipsEnd = xmlNode.find("\"", mipsStart);
    if (mipsStart != std::string::npos && mipsEnd != std::string::npos)
    {
        asset->mipmaps = xmlNode.substr(mipsStart, mipsEnd - mipsStart) == "true";
    }

    // Extract filter
    size_t filterStart = xmlNode.find("filter=\"") + 8;
    size_t filterEnd = xmlNode.find("\"", filterStart);
    if (filterStart != std::string::npos && filterEnd != std::string::npos)
    {
        asset->filter = xmlNode.substr(filterStart, filterEnd - filterStart);
    }

    return asset;
}

std::unique_ptr<MaterialAsset> AssetPackLoader::parseMaterialAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<MaterialAsset>();

    // Extract shader_id
    size_t shaderStart = xmlNode.find("<shader_id>") + 11;
    size_t shaderEnd = xmlNode.find("</shader_id>", shaderStart);
    if (shaderStart != std::string::npos && shaderEnd != std::string::npos)
    {
        asset->shaderId = xmlNode.substr(shaderStart, shaderEnd - shaderStart);
    }

    // Parse params (simplified)
    size_t paramsStart = xmlNode.find("<params>");
    size_t paramsEnd = xmlNode.find("</params>", paramsStart);
    if (paramsStart != std::string::npos && paramsEnd != std::string::npos)
    {
        std::string paramsSection = xmlNode.substr(paramsStart, paramsEnd - paramsStart);
        // Basic parsing of common parameters would go here
    }

    return asset;
}

std::unique_ptr<MeshRecipeAsset> AssetPackLoader::parseMeshRecipeAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<MeshRecipeAsset>();

    // Extract generator
    size_t genStart = xmlNode.find("<generator>") + 11;
    size_t genEnd = xmlNode.find("</generator>", genStart);
    if (genStart != std::string::npos && genEnd != std::string::npos)
    {
        asset->generator = xmlNode.substr(genStart, genEnd - genStart);
    }

    // Parse params (simplified)
    size_t paramsStart = xmlNode.find("<params>");
    size_t paramsEnd = xmlNode.find("</params>", paramsStart);
    if (paramsStart != std::string::npos && paramsEnd != std::string::npos)
    {
        std::string paramsSection = xmlNode.substr(paramsStart, paramsEnd - paramsStart);
        // Basic parsing of parameters would go here
    }

    return asset;
}
