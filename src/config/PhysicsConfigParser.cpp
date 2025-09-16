/**
 * @file PhysicsConfigParser.cpp
 * @brief Implementation of physics configuration XML parser.
 */

#include "PhysicsConfigParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Load physics configuration from XML file.
 *
 * Reads the specified XML file and parses physics parameters from it.
 * If the file cannot be loaded or parsed, returns default configuration.
 *
 * @param configPath Path to the physics configuration XML file
 * @return PhysicsConfig structure with loaded parameters, or defaults if loading fails
 */
Physics::PhysicsConfig PhysicsConfigParser::loadFromFile(const std::string &configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open())
    {
        std::cerr << "Warning: Could not open physics config file: " << configPath << std::endl;
        std::cerr << "Using default physics parameters." << std::endl;
        return Physics::PhysicsConfig{}; // Return default configuration
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::cout << "Loading physics configuration from: " << configPath << std::endl;
    return parseConfig(content);
}

/**
 * @brief Load physics configuration from XML string.
 *
 * Parses physics parameters directly from the provided XML string content.
 *
 * @param xmlContent XML content as string
 * @return PhysicsConfig structure with loaded parameters, or defaults if parsing fails
 */
Physics::PhysicsConfig PhysicsConfigParser::loadFromString(const std::string &xmlContent)
{
    return parseConfig(xmlContent);
}

/**
 * @brief Parse physics configuration from XML content.
 *
 * Uses simple string-based XML parsing to extract physics parameters.
 * This approach is consistent with other config parsers in the project.
 *
 * @param xmlContent The XML content to parse
 * @return PhysicsConfig structure with parsed parameters
 */
Physics::PhysicsConfig PhysicsConfigParser::parseConfig(const std::string &xmlContent)
{
    Physics::PhysicsConfig config;

    try
    {
        // Parse Simulation Clock parameters
        config.fixedTimestep = extractFloatValue(xmlContent, "FixedTimestep", config.fixedTimestep);
        config.maxSubsteps = extractIntValue(xmlContent, "MaxSubsteps", config.maxSubsteps);

        // Parse Air Density Model parameters
        config.seaLevelDensity = extractFloatValue(xmlContent, "SeaLevelDensity", config.seaLevelDensity);
        config.scaleHeight = extractFloatValue(xmlContent, "ScaleHeight", config.scaleHeight);

        // Parse Wind Model parameters
        config.baseWindSpeed = extractFloatValue(xmlContent, "BaseWindSpeed", config.baseWindSpeed);
        config.turbulenceScale = extractFloatValue(xmlContent, "TurbulenceScale", config.turbulenceScale);
        config.turbulenceIntensity = extractFloatValue(xmlContent, "TurbulenceIntensity", config.turbulenceIntensity);
        config.randomSeed = extractIntValue(xmlContent, "RandomSeed", config.randomSeed);

        // Parse Collision Resolver parameters
        config.restitution = extractFloatValue(xmlContent, "Restitution", config.restitution);
        config.friction = extractFloatValue(xmlContent, "Friction", config.friction);

        std::cout << "Physics configuration loaded successfully:" << std::endl;
        std::cout << "  - Fixed timestep: " << config.fixedTimestep << "s (" << (1.0f / config.fixedTimestep) << " Hz)" << std::endl;
        std::cout << "  - Air density (sea level): " << config.seaLevelDensity << " kg/m³" << std::endl;
        std::cout << "  - Wind base speed: " << config.baseWindSpeed << " m/s" << std::endl;
        std::cout << "  - Collision restitution: " << config.restitution << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing physics configuration: " << e.what() << std::endl;
        std::cerr << "Using default physics parameters." << std::endl;
        config = Physics::PhysicsConfig{}; // Reset to defaults
    }

    return config;
}

/**
 * @brief Extract float value from XML using simple string parsing.
 *
 * @param xml The XML content to search in
 * @param tagName The XML tag name to find
 * @param defaultValue Default value if tag is not found or parsing fails
 * @return Parsed float value or default
 */
float PhysicsConfigParser::extractFloatValue(const std::string &xml, const std::string &tagName, float defaultValue)
{
    std::string openTag = "<" + tagName + ">";
    std::string closeTag = "</" + tagName + ">";

    size_t startPos = xml.find(openTag);
    if (startPos == std::string::npos)
    {
        return defaultValue;
    }

    startPos += openTag.length();
    size_t endPos = xml.find(closeTag, startPos);
    if (endPos == std::string::npos)
    {
        return defaultValue;
    }

    std::string valueStr = xml.substr(startPos, endPos - startPos);

    try
    {
        return std::stof(valueStr);
    }
    catch (const std::exception &)
    {
        std::cerr << "Warning: Could not parse float value for tag " << tagName << ": '" << valueStr << "'" << std::endl;
        return defaultValue;
    }
}

/**
 * @brief Extract integer value from XML using simple string parsing.
 *
 * @param xml The XML content to search in
 * @param tagName The XML tag name to find
 * @param defaultValue Default value if tag is not found or parsing fails
 * @return Parsed integer value or default
 */
int PhysicsConfigParser::extractIntValue(const std::string &xml, const std::string &tagName, int defaultValue)
{
    std::string openTag = "<" + tagName + ">";
    std::string closeTag = "</" + tagName + ">";

    size_t startPos = xml.find(openTag);
    if (startPos == std::string::npos)
    {
        return defaultValue;
    }

    startPos += openTag.length();
    size_t endPos = xml.find(closeTag, startPos);
    if (endPos == std::string::npos)
    {
        return defaultValue;
    }

    std::string valueStr = xml.substr(startPos, endPos - startPos);

    try
    {
        return std::stoi(valueStr);
    }
    catch (const std::exception &)
    {
        std::cerr << "Warning: Could not parse integer value for tag " << tagName << ": '" << valueStr << "'" << std::endl;
        return defaultValue;
    }
}
