#ifndef PHYSICS_CONFIG_PARSER_H
#define PHYSICS_CONFIG_PARSER_H

#include <string>
#include <memory>

/**
 * @brief Configuration structure for physics simulation parameters.
 *
 * This structure holds all configurable physics parameters that were
 * previously hardcoded, allowing for XML-driven physics configuration.
 */
struct PhysicsConfig
{
    // Simulation Clock
    float fixedTimestep = 0.016666667f; // 60Hz default
    int maxSubsteps = 10;

    // Air Density Model (Exponential)
    float seaLevelDensity = 1.225f; // kg/m³
    float scaleHeight = 8500.0f;    // meters

    // Wind Model (Perlin)
    float baseWindSpeed = 5.0f; // m/s
    float turbulenceScale = 100.0f;
    float turbulenceIntensity = 10.0f;
    int randomSeed = 12345;

    // Collision Resolver (Impulse)
    float restitution = 0.2f;
    float friction = 0.8f;
};

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
    static PhysicsConfig loadFromFile(const std::string &configPath);

    /**
     * @brief Load physics configuration from XML string.
     *
     * @param xmlContent XML content as string
     * @return PhysicsConfig structure with loaded parameters, or defaults if parsing fails
     */
    static PhysicsConfig loadFromString(const std::string &xmlContent);

private:
    /**
     * @brief Parse physics configuration from XML content.
     *
     * @param xmlContent The XML content to parse
     * @return PhysicsConfig structure with parsed parameters
     */
    static PhysicsConfig parseConfig(const std::string &xmlContent);

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
