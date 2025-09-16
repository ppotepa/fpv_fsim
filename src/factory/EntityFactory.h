#pragma once

#include "core/Entity.h"
#include "core/EventBus.h"
#include <memory>
#include <string>
#include <unordered_map>

// Forward declarations
namespace Material {
    class MaterialManager;
}

namespace EntityFactory {
    
    /**
     * @brief Simple Entity Factory for creating basic entities
     * 
     * This is a simplified implementation that creates basic entities
     * without complex XML parsing for now.
     */
    class EntityFactory {
    public:
        EntityFactory(EventBus& eventBus, Material::MaterialManager& materialManager);
        ~EntityFactory() = default;

        /**
         * @brief Load configuration from file (simplified implementation)
         */
        bool loadConfiguration(const std::string& configFilePath);

        /**
         * @brief Create entity from template name
         */
        std::unique_ptr<Entity> createFromTemplate(const std::string& templateName, 
                                                 const std::string& entityName, 
                                                 unsigned int entityId);

    private:
        EventBus& eventBus_;
        Material::MaterialManager& materialManager_;
        unsigned int nextEntityId_;
        
        // Simple template storage
        std::unordered_map<std::string, std::string> templates_;
        
        void initializeDefaultTemplates();
    };

} // namespace EntityFactory
