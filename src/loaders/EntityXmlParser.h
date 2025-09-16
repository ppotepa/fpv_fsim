#ifndef ENTITY_XML_PARSER_H
#define ENTITY_XML_PARSER_H

#include "config/EntityConfig.h"
#include <memory>
#include <string>

class IXmlParserUnified;

namespace EntityLoader
{

    /**
     * @brief Parser for entity XML files according to entity.xsd schema
     *
     * This class is responsible for loading and parsing entity definition XML files
     * into EntityConfig::EntityDefinition structures that can be used by the EntityFactory
     * to instantiate entities in the game world.
     */
    class EntityXmlParser
    {
    public:
        EntityXmlParser();
        ~EntityXmlParser();

        /**
         * @brief Load entity definition from XML file
         *
         * @param filePath Path to the entity XML file
         * @return std::unique_ptr<EntityConfig::EntityDefinition> The parsed entity definition or nullptr on failure
         */
        std::unique_ptr<EntityConfig::EntityDefinition> loadFromFile(const std::string &filePath);

        /**
         * @brief Load entity definition from XML string
         *
         * @param xmlContent XML content as string
         * @return std::unique_ptr<EntityConfig::EntityDefinition> The parsed entity definition or nullptr on failure
         */
        std::unique_ptr<EntityConfig::EntityDefinition> loadFromString(const std::string &xmlContent);

    private:
        std::unique_ptr<IXmlParserUnified> xmlParser_;

        /**
         * @brief Parse entity XML into EntityDefinition
         *
         * @return std::unique_ptr<EntityConfig::EntityDefinition> Parsed entity definition
         */
        std::unique_ptr<EntityConfig::EntityDefinition> parseEntity();

        /**
         * @brief Parse transform component
         *
         * @param definition EntityDefinition to populate
         */
        void parseTransform(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse renderable component
         *
         * @param definition EntityDefinition to populate
         */
        void parseRenderableComponent(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse physics component
         *
         * @param definition EntityDefinition to populate
         */
        void parsePhysicsComponent(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse vehicle component
         *
         * @param definition EntityDefinition to populate
         */
        void parseVehicleComponent(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse audio component
         *
         * @param definition EntityDefinition to populate
         */
        void parseAudioComponent(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse light component
         *
         * @param definition EntityDefinition to populate
         */
        void parseLightComponent(EntityConfig::EntityDefinition &definition);

        /**
         * @brief Parse custom properties
         *
         * @param definition EntityDefinition to populate
         */
        void parseCustomProperties(EntityConfig::EntityDefinition &definition);
    };

} // namespace EntityLoader

#endif // ENTITY_XML_PARSER_H

