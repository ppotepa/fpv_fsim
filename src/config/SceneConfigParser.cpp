#include "SceneConfigParser.h"
#include "../platform/PugiXmlParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <regex>
#include <iostream>
#include <filesystem>
#include <stack>
#include "../debug.h"

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
            // Validate XML structure first
            if (!validateXmlStructure(xmlContent))
            {
                currentResult_.success = false;
                currentResult_.errorMessage = "Invalid XML structure";
                return currentResult_;
            }

            // For now, create a minimal scene for loading_indicator type
            auto scene = std::make_shared<Scene>();

            // Enhanced XML attribute extraction with validation
            scene->id = extractAttributeSimple(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttributeSimple(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttributeSimple(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttributeSimple(xmlContent, "scene", "version", "1.0");

            // Validate required fields
            if (scene->id.empty())
            {
                currentResult_.success = false;
                currentResult_.errorMessage = "Scene must have a valid ID";
                return currentResult_;
            }

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

    // Enhanced helper method for robust attribute extraction with validation
    std::string SceneConfigParser::extractAttributeSimple(const std::string &xmlContent,
                                                          const std::string &elementName,
                                                          const std::string &attributeName,
                                                          const std::string &defaultValue)
    {
        try
        {
            // More robust regex pattern with better error handling
            std::string pattern = "<\\s*" + elementName + "(?:\\s+[^>]*)?\\s+" + attributeName + "\\s*=\\s*\"([^\"]*?)\"";
            std::regex re(pattern, std::regex_constants::icase);
            std::smatch match;

            if (std::regex_search(xmlContent, match, re))
            {
                std::string value = match[1].str();
                // Validate the extracted value
                if (!value.empty())
                {
                    return value;
                }
            }

            // Also try with single quotes
            pattern = "<\\s*" + elementName + "(?:\\s+[^>]*)?\\s+" + attributeName + "\\s*=\\s*'([^']*?)'";
            re = std::regex(pattern, std::regex_constants::icase);

            if (std::regex_search(xmlContent, match, re))
            {
                std::string value = match[1].str();
                if (!value.empty())
                {
                    return value;
                }
            }
        }
        catch (const std::regex_error &e)
        {
            std::cerr << "Regex error in XML parsing: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error extracting XML attribute " << attributeName << ": " << e.what() << std::endl;
        }

        return defaultValue;
    }

    bool SceneConfigParser::validateXmlStructure(const std::string &xmlContent)
    {
        try
        {
            // Basic XML well-formedness check
            if (!isWellFormedXml(xmlContent))
            {
                return false;
            }

            // Check for required scene element
            std::regex sceneElementRegex("<\\s*scene[^>]*>");
            if (!std::regex_search(xmlContent, sceneElementRegex))
            {
                std::cerr << "XML validation error: Missing <scene> element" << std::endl;
                return false;
            }

            // Check for matching closing tag
            std::regex closingSceneRegex("</\\s*scene\\s*>");
            if (!std::regex_search(xmlContent, closingSceneRegex))
            {
                std::cerr << "XML validation error: Missing </scene> closing tag" << std::endl;
                return false;
            }

            // Check for required namespace
            std::regex namespaceRegex("xmlns\\s*=\\s*[\"']http://fpvfsim\\.com/scene-schema[\"']");
            if (!std::regex_search(xmlContent, namespaceRegex))
            {
                std::cerr << "XML validation warning: Missing or incorrect namespace" << std::endl;
                // Don't fail for namespace issues for now
            }

            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "XML validation error: " << e.what() << std::endl;
            return false;
        }
    }

    bool SceneConfigParser::isWellFormedXml(const std::string &xmlContent)
    {
        try
        {
            // Basic bracket matching for XML tags
            std::stack<std::string> tagStack;
            std::regex tagRegex("<(/?)(\\w+)[^>]*>");
            std::sregex_iterator iter(xmlContent.begin(), xmlContent.end(), tagRegex);
            std::sregex_iterator end;

            for (; iter != end; ++iter)
            {
                std::smatch match = *iter;
                bool isClosing = !match[1].str().empty();
                std::string tagName = match[2].str();

                if (isClosing)
                {
                    if (tagStack.empty() || tagStack.top() != tagName)
                    {
                        std::cerr << "XML well-formedness error: Mismatched closing tag: " << tagName << std::endl;
                        return false;
                    }
                    tagStack.pop();
                }
                else
                {
                    // Check if it's a self-closing tag
                    std::string fullMatch = match[0].str();
                    if (fullMatch.back() == '>' && fullMatch[fullMatch.length() - 2] == '/')
                    {
                        // Self-closing tag, don't add to stack
                        continue;
                    }
                    tagStack.push(tagName);
                }
            }

            // All tags should be closed
            if (!tagStack.empty())
            {
                std::cerr << "XML well-formedness error: Unclosed tags remaining" << std::endl;
                return false;
            }

            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "XML well-formedness check error: " << e.what() << std::endl;
            return false;
        }
    }

    bool SceneConfigParser::resolveAssetPaths(Scene &scene, const std::string &baseDirectory)
    {
        // Simple implementation - just return true for now
        // In a full implementation, this would resolve all asset paths relative to baseDirectory
        return true;
    }

    ParseResult SceneConfigParser::loadXmlScene(const std::string &sceneId)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        ParseResult result;

        // Construct scene file path based on sceneId
        std::string scenePath = "configs/scenes/" + sceneId + ".xml";

        if (Debug())
        {
            std::cout << "Loading XML scene: " << sceneId << " from " << scenePath << std::endl;
        }

        // Check if file exists
        if (!std::filesystem::exists(scenePath))
        {
            result.success = false;
            result.errorMessage = "Scene file not found: " + scenePath;
            result.parseTimeMs = 0;
            return result;
        }

        // Use PugiXmlParser for robust XML parsing
        PugiXmlParser xmlParser;
        if (!xmlParser.loadFile(scenePath))
        {
            result.success = false;
            result.errorMessage = "Failed to load XML file: " + xmlParser.getLastError();
            result.parseTimeMs = 0;
            return result;
        }

        // For now, delegate to the existing parseSceneFile method
        // This provides proper XML parsing while we enhance the system
        result = parseSceneFile(scenePath);

        auto endTime = std::chrono::high_resolution_clock::now();
        result.parseTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        if (Debug())
        {
            std::cout << "XML scene loading completed in " << result.parseTimeMs << "ms" << std::endl;
        }
        return result;
    }

} // namespace SceneConfig
