/**
 * @file PhysicsConfigParser.cpp
 * @brief Implementation of physics configuration JSON parser.
 */

#include "PhysicsConfigParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "../debug.h"

/**
 * @brief Constructor
 * @param jsonParser JSON parser implementation to use
 */
PhysicsConfigParser::PhysicsConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser)
    : m_jsonParser(std::move(jsonParser))
{
}

/**
 * @brief Load physics configuration from JSON file.
 *
 * Reads the specified JSON file and parses physics parameters from it.
 * If the file cannot be loaded or parsed, returns default configuration.
 *
 * @param configPath Path to the physics configuration JSON file
 * @return PhysicsConfig structure with loaded parameters, or defaults if loading fails
 */
Physics::PhysicsConfig PhysicsConfigParser::loadFromFile(const std::string &configPath)
{
    if (!m_jsonParser->loadFile(configPath))
    {
        std::cerr << "Warning: Could not open physics config file: " << configPath << std::endl;
        std::cerr << "Using default physics parameters." << std::endl;
        return Physics::PhysicsConfig{}; // Return default configuration
    }

    if (Debug())
    {
        DEBUG_LOG("Loading physics configuration from: " << configPath);
    }
    return parseConfig("");
}

/**
 * @brief Load physics configuration from JSON string.
 *
 * Parses physics parameters directly from the provided JSON string content.
 *
 * @param jsonContent JSON content as string
 * @return PhysicsConfig structure with loaded parameters, or defaults if parsing fails
 */
Physics::PhysicsConfig PhysicsConfigParser::loadFromString(const std::string &jsonContent)
{
    if (!m_jsonParser->loadString(jsonContent))
    {
        std::cerr << "Warning: Could not parse physics config JSON content." << std::endl;
        std::cerr << "Using default physics parameters." << std::endl;
        return Physics::PhysicsConfig{}; // Return default configuration
    }
    return parseConfig("");
}

/**
 * @brief Parse physics configuration from JSON content.
 *
 * Uses the JSON parser to extract physics parameters.
 * The JSON parser should already have loaded the content.
 *
 * @param jsonContent The JSON content to parse (unused - parser already loaded)
 * @return PhysicsConfig structure with parsed parameters
 */
Physics::PhysicsConfig PhysicsConfigParser::parseConfig(const std::string &jsonContent)
{
    Physics::PhysicsConfig config;

    try
    {
        // Parse Simulation Clock parameters
        config.fixedTimestep = m_jsonParser->getFloat("simulation.fixedTimestep", config.fixedTimestep);
        config.maxSubsteps = m_jsonParser->getInt("simulation.maxSubsteps", config.maxSubsteps);

        // Parse Air Density Model parameters
        config.seaLevelDensity = m_jsonParser->getFloat("airDensity.seaLevelDensity", config.seaLevelDensity);
        config.scaleHeight = m_jsonParser->getFloat("airDensity.scaleHeight", config.scaleHeight);

        // Parse Wind Model parameters
        config.baseWindSpeed = m_jsonParser->getFloat("wind.baseWindSpeed", config.baseWindSpeed);
        config.turbulenceScale = m_jsonParser->getFloat("wind.turbulenceScale", config.turbulenceScale);
        config.turbulenceIntensity = m_jsonParser->getFloat("wind.turbulenceIntensity", config.turbulenceIntensity);
        config.randomSeed = m_jsonParser->getInt("wind.randomSeed", config.randomSeed);

        // Parse Collision Resolver parameters
        config.restitution = m_jsonParser->getFloat("collision.restitution", config.restitution);
        config.friction = m_jsonParser->getFloat("collision.friction", config.friction);

        if (Debug())
        {
            DEBUG_LOG("Physics configuration loaded successfully:");
            DEBUG_LOG("  - Fixed timestep: " << config.fixedTimestep << "s (" << (1.0f / config.fixedTimestep) << " Hz)");
            DEBUG_LOG("  - Air density (sea level): " << config.seaLevelDensity << " kg/m³");
            DEBUG_LOG("  - Wind base speed: " << config.baseWindSpeed << " m/s");
            DEBUG_LOG("  - Collision restitution: " << config.restitution);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing physics configuration: " << e.what() << std::endl;
        std::cerr << "Using default physics parameters." << std::endl;
        config = Physics::PhysicsConfig{}; // Reset to defaults
    }

    return config;
}
