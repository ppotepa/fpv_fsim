#pragma once

#include "core/Entity.h"
#include "core/EventBus.h"
#include "config/EntityConfig.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations
namespace Material
{
    class MaterialManager;
}

namespace EntityFactory
{

    /**
     * @brief Entity Factory for creating entities from XML definitions
     *
     * Creates entities based on XML definitions or templates, and adds
     * appropriate components based on the entity configuration.
     */
    class EntityFactory
    {
    public:
        EntityFactory(EventBus &eventBus, Material::MaterialManager &materialManager);
        ~EntityFactory() = default;

        /**
         * @brief Load configuration from file
         */
        bool loadConfiguration(const std::string &configFilePath);

        /**
         * @brief Create entity from template name
         */
        std::unique_ptr<Entity> createFromTemplate(const std::string &templateName,
                                                   const std::string &entityName,
                                                   unsigned int entityId);

        /**
         * @brief Create entity from XML file
         */
        std::unique_ptr<Entity> createFromXmlFile(const std::string &xmlFilePath,
                                                  unsigned int entityId = 0);

        /**
         * @brief Create entity from EntityDefinition object
         */
        std::unique_ptr<Entity> createFromDefinition(const EntityConfig::EntityDefinition &definition,
                                                     unsigned int entityId = 0);

    private:
        EventBus &eventBus_;
        Material::MaterialManager &materialManager_;
        unsigned int nextEntityId_;

        // Template and configuration storage
        std::unordered_map<std::string, std::string> templates_;
        std::vector<EntityConfig::EntityTemplate> entityTemplates_;

        void initializeDefaultTemplates();

        /**
         * @brief Add components to entity based on EntityDefinition
         */
        void addEntityComponents(Entity &entity, const EntityConfig::EntityDefinition &definition);

        /**
         * @brief Get a unique entity ID if one wasn't provided
         */
        unsigned int getNextEntityId()
        {
            return nextEntityId_++;
        }
    };

} // namespace EntityFactory

