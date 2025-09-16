#include "EntityFactory.h"
#include "systems/MaterialManager.h"
#include "core/Entity.h"
#include "core/EventBus.h"
#include <iostream>

namespace EntityFactory {

EntityFactory::EntityFactory(EventBus& eventBus, Material::MaterialManager& materialManager)
    : eventBus_(eventBus), materialManager_(materialManager), nextEntityId_(1) {
    initializeDefaultTemplates();
}

bool EntityFactory::loadConfiguration(const std::string& configFilePath) {
    // Simplified implementation - just return true for now
    // In a full implementation, this would parse XML configuration
    std::cout << "EntityFactory: Loading configuration from " << configFilePath << std::endl;
    return true;
}

std::unique_ptr<Entity> EntityFactory::createFromTemplate(const std::string& templateName, 
                                                         const std::string& entityName, 
                                                         unsigned int entityId) {
    // Create basic entity
    auto entity = std::make_unique<Entity>(entityId);
    
    std::cout << "EntityFactory: Creating entity '" << entityName 
              << "' from template '" << templateName << "' with ID " << entityId << std::endl;
    
    // For now, just create a basic entity without complex components
    // In a full implementation, this would parse the template and add appropriate components
    
    return entity;
}

void EntityFactory::initializeDefaultTemplates() {
    // Initialize basic templates
    templates_["earth_sphere"] = "basic_sphere";
    templates_["basic_drone"] = "aircraft";
    templates_["cloud_object"] = "cloud";
    
    std::cout << "EntityFactory: Initialized with " << templates_.size() << " default templates" << std::endl;
}

} // namespace EntityFactory
