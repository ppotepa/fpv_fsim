#ifndef ENTITY_CONFIG_PARSER_H
#define ENTITY_CONFIG_PARSER_H

#include "EntityConfig.h"
#include <string>

namespace EntityConfig
{

    /**
     * @brief Parser for entity factory configuration XML files
     *
     * Loads entity templates, factory settings, and resource mappings
     * from XML configuration files for the EntityFactory system.
     */
    class EntityConfigParser
    {
    public:
        /**
         * @brief Load entity factory configuration from XML file
         *
         * @param filePath Path to entity_factory_config.xml
         * @return EntityFactoryConfiguration Parsed configuration
         */
        static EntityFactoryConfiguration loadFromFile(const std::string &filePath);

        /**
         * @brief Load entity factory configuration from XML string
         *
         * @param xmlContent XML content as string
         * @return EntityFactoryConfiguration Parsed configuration
         */
        static EntityFactoryConfiguration loadFromString(const std::string &xmlContent);

    private:
        /**
         * @brief Parse factory settings from XML
         */
        static void parseSettings(const std::string &xmlContent, EntityFactoryConfiguration &config);

        /**
         * @brief Parse entity templates from XML
         */
        static void parseTemplates(const std::string &xmlContent, EntityFactoryConfiguration &config);

        /**
         * @brief Parse single entity template
         */
        static EntityTemplate parseTemplate(const std::string &templateXml);

        /**
         * @brief Parse entity definition from template XML
         */
        static EntityDefinition parseEntityDefinition(const std::string &templateXml);

        /**
         * @brief Parse transform from XML
         */
        static Transform parseTransform(const std::string &xmlContent);

        /**
         * @brief Parse renderable component from XML
         */
        static std::unique_ptr<RenderableComponent> parseRenderableComponent(const std::string &xmlContent);

        /**
         * @brief Parse physics component from XML
         */
        static std::unique_ptr<PhysicsComponent> parsePhysicsComponent(const std::string &xmlContent);

        /**
         * @brief Parse vehicle component from XML
         */
        static std::unique_ptr<VehicleComponent> parseVehicleComponent(const std::string &xmlContent);

        /**
         * @brief Parse resource mappings from XML
         */
        static void parseResourceMappings(const std::string &xmlContent, EntityFactoryConfiguration &config);

        /**
         * @brief Extract element value from XML
         */
        static std::string extractValue(const std::string &xmlContent, const std::string &elementName);

        /**
         * @brief Extract attribute value from XML element
         */
        static std::string extractAttribute(const std::string &xmlContent, const std::string &elementName, const std::string &attributeName);

        /**
         * @brief Extract all template elements from XML
         */
        static std::vector<std::string> extractTemplates(const std::string &xmlContent);

        /**
         * @brief Convert string to appropriate types with validation
         */
        static int toInt(const std::string &value, int defaultValue = 0);
        static float toFloat(const std::string &value, float defaultValue = 0.0f);
        static bool toBool(const std::string &value, bool defaultValue = false);
    };

} // namespace EntityConfig

#endif // ENTITY_CONFIG_PARSER_H

