#include "DroneBuilder.h"

DroneBuilder::DroneBuilder(std::unique_ptr<IJsonQuery> jsonParser)
    : m_jsonParser(std::move(jsonParser))
{
}

std::unique_ptr<Entity> DroneBuilder::build(const std::string &configPath, EventBus &eventBus)
{
    // TODO: Use JSON parser to load configuration from configPath
    // For now, create a basic drone entity
    auto entity = std::make_unique<Entity>(1); // id 1
    // TODO: Add components based on JSON configuration (TransformC, BatteryC, etc.)
    return entity;
}
