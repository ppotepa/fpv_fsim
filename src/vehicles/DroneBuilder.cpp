#include "DroneBuilder.h"

DroneBuilder::DroneBuilder(IXmlParser &xmlParser) : xmlParser_(xmlParser) {}

std::unique_ptr<Entity> DroneBuilder::build(const std::string &configPath, EventBus &eventBus)
{
    // Stub: parse config, create entity with components
    auto entity = std::make_unique<Entity>(1); // id 1
    // Add components, e.g. TransformC, BatteryC, etc.
    return entity;
}
