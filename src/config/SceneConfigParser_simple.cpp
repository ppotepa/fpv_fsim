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

} // namespace SceneConfig
