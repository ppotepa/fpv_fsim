#ifndef PHYSICS_CONFIG_PARSER_H
#define PHYSICS_CONFIG_PARSER_H

#include "PhysicsConfig.h"
#include <string>
#include <memory>

/**
 * @brief Parser for physics configuration XML files.
 *
 * This class provides functionality to load physics parameters from XML
 * configuration files, replacing hardcoded values with configurable ones.
 */
class PhysicsConfigParser
{
public:
    /**
     * @brief Load physics configuration from XML file.
     *
     * @param configPath Path to the physics configuration XML file
     * @return PhysicsConfig structure with loaded parameters, or defaults if loading fails
     */
    static Physics::PhysicsConfig loadFromFile(const std::string &configPath);

    /**
     * @brief Load physics configuration from XML string.
     *
     * @param xmlContent XML content as string
     * @return PhysicsConfig structure with loaded parameters, or defaults if parsing fails
     */
    static Physics::PhysicsConfig loadFromString(const std::string &xmlContent);

private:
    /**
     * @brief Parse physics configuration from XML content.
     *
     * @param xmlContent The XML content to parse
     * @return PhysicsConfig structure with parsed parameters
     */
    static Physics::PhysicsConfig parseConfig(const std::string &xmlContent);

    /**
     * @brief Extract float value from XML using simple string parsing.
     *
     * @param xml The XML content to search in
     * @param tagName The XML tag name to find
     * @param defaultValue Default value if tag is not found or parsing fails
     * @return Parsed float value or default
     */
    static float extractFloatValue(const std::string &xml, const std::string &tagName, float defaultValue);

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
