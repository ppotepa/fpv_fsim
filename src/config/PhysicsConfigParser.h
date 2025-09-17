#ifndef PHYSICS_CONFIG_PARSER_H
#define PHYSICS_CONFIG_PARSER_H

#include "PhysicsConfig.h"
#include "../utils/IJsonParserUnified.h"
#include <string>
#include <memory>

/**
 * @brief Parser for physics configuration JSON files.
 *
 * This class provides functionality to load physics parameters from JSON
 * configuration files, replacing hardcoded values with configurable ones.
 */
class PhysicsConfigParser
{
public:
    /**
     * @brief Constructor
     * @param jsonParser JSON parser implementation to use
     */
    explicit PhysicsConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser);

    /**
     * @brief Load physics configuration from JSON file.
     *
     * @param configPath Path to the physics configuration JSON file
     * @return PhysicsConfig structure with loaded parameters, or defaults if loading fails
     */
    Physics::PhysicsConfig loadFromFile(const std::string &configPath);

    /**
     * @brief Load physics configuration from JSON string.
     *
     * @param jsonContent JSON content as string
     * @return PhysicsConfig structure with loaded parameters, or defaults if parsing fails
     */
    Physics::PhysicsConfig loadFromString(const std::string &jsonContent);

private:
    std::unique_ptr<IJsonParserUnified> m_jsonParser;

    /**
     * @brief Parse physics configuration from JSON content.
     *
     * @param jsonContent The JSON content to parse
     * @return PhysicsConfig structure with parsed parameters
     */
    Physics::PhysicsConfig parseConfig(const std::string &jsonContent);

    /**
     * @brief Extract integer value from XML using simple string parsing.
     *
     * @param xml The XML content to search in
     * @param tagName The XML tag name to find
     * @param defaultValue Default value if tag is not found or parsing fails
     * @return Parsed integer value or default
     */
    static int extractIntValue(const std::string &xml, const std::string &tagName, int defaultValue);
};

#endif // PHYSICS_CONFIG_PARSER_H
