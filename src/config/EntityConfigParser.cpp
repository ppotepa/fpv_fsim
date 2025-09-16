#include "EntityConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "../debug.h"

namespace EntityConfig
{

    EntityFactoryConfiguration EntityConfigParser::loadFromFile(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            if (Debug())
            {
                DEBUG_LOG("Warning: Cannot open entity factory config file '" << filePath << "', using defaults");
            }
            return EntityFactoryConfiguration{};
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return loadFromString(buffer.str());
    }

    EntityFactoryConfiguration EntityConfigParser::loadFromString(const std::string &xmlContent)
    {
        EntityFactoryConfiguration config;

        try
        {
            parseSettings(xmlContent, config);
            parseTemplates(xmlContent, config);
            parseResourceMappings(xmlContent, config);

            if (Debug())
            {
                DEBUG_LOG("Entity factory configuration loaded successfully: "
                          << config.templates.size() << " templates");
            }
        }
        catch (const std::exception &e)
        {
            if (Debug())
            {
                DEBUG_LOG("Warning: Error parsing entity factory config: " << e.what() << ", using defaults");
            }
            config = EntityFactoryConfiguration{};
        }

        return config;
    }

    void EntityConfigParser::parseSettings(const std::string &xmlContent, EntityFactoryConfiguration &config)
    {
        config.validateComponents = toBool(extractValue(xmlContent, "validate_components"), true);
        config.logCreation = toBool(extractValue(xmlContent, "log_creation"), false);
        config.enablePooling = toBool(extractValue(xmlContent, "enable_pooling"), false);
        config.maxPoolSize = toInt(extractValue(xmlContent, "max_pool_size"), 100);
    }

    void EntityConfigParser::parseTemplates(const std::string &xmlContent, EntityFactoryConfiguration &config)
    {
        auto templateElements = extractTemplates(xmlContent);

        for (const auto &templateXml : templateElements)
        {
            try
            {
                EntityTemplate entityTemplate = parseTemplate(templateXml);
                config.templates.push_back(std::move(entityTemplate));
            }
            catch (const std::exception &e)
            {
                if (Debug())
                {
                    DEBUG_LOG("Warning: Failed to parse entity template: " << e.what());
                }
            }
        }
    }

    EntityTemplate EntityConfigParser::parseTemplate(const std::string &templateXml)
    {
        EntityTemplate entityTemplate;

        entityTemplate.templateId = extractAttribute(templateXml, "template", "id");
        entityTemplate.category = extractAttribute(templateXml, "template", "category");
        entityTemplate.name = extractValue(templateXml, "name");
        entityTemplate.description = extractValue(templateXml, "description");

        entityTemplate.defaultDefinition = parseEntityDefinition(templateXml);

        return entityTemplate;
    }

    EntityDefinition EntityConfigParser::parseEntityDefinition(const std::string &templateXml)
    {
        EntityDefinition definition;

        definition.entityType = extractValue(templateXml, "entity_type");
        definition.name = extractValue(templateXml, "name");
        definition.description = extractValue(templateXml, "description");
        definition.startActive = toBool(extractValue(templateXml, "start_active"), true);

        std::string lifetimeStr = extractValue(templateXml, "lifetime");
        definition.lifetime = lifetimeStr.empty() ? -1.0f : toFloat(lifetimeStr, -1.0f);

        // Parse transform
        definition.transform = parseTransform(templateXml);

        // Parse optional components
        if (templateXml.find("<renderable>") != std::string::npos)
        {
            definition.renderable = parseRenderableComponent(templateXml);
        }

        if (templateXml.find("<physics>") != std::string::npos)
        {
            definition.physics = parsePhysicsComponent(templateXml);
        }

        if (templateXml.find("<vehicle>") != std::string::npos)
        {
            definition.vehicle = parseVehicleComponent(templateXml);
        }

        return definition;
    }

    Transform EntityConfigParser::parseTransform(const std::string &xmlContent)
    {
        Transform transform;

        // Parse position
        std::string posX = extractAttribute(xmlContent, "position", "x");
        std::string posY = extractAttribute(xmlContent, "position", "y");
        std::string posZ = extractAttribute(xmlContent, "position", "z");

        transform.position.x = toFloat(posX, 0.0f);
        transform.position.y = toFloat(posY, 0.0f);
        transform.position.z = toFloat(posZ, 0.0f);

        // Parse rotation
        std::string rotX = extractAttribute(xmlContent, "rotation", "x");
        std::string rotY = extractAttribute(xmlContent, "rotation", "y");
        std::string rotZ = extractAttribute(xmlContent, "rotation", "z");
        std::string rotW = extractAttribute(xmlContent, "rotation", "w");

        transform.rotation.x = toFloat(rotX, 0.0f);
        transform.rotation.y = toFloat(rotY, 0.0f);
        transform.rotation.z = toFloat(rotZ, 0.0f);
        transform.rotation.w = toFloat(rotW, 1.0f);

        // Parse scale
        std::string scaleX = extractAttribute(xmlContent, "scale", "x");
        std::string scaleY = extractAttribute(xmlContent, "scale", "y");
        std::string scaleZ = extractAttribute(xmlContent, "scale", "z");

        transform.scale.x = toFloat(scaleX, 1.0f);
        transform.scale.y = toFloat(scaleY, 1.0f);
        transform.scale.z = toFloat(scaleZ, 1.0f);

        return transform;
    }

    std::unique_ptr<RenderableComponent> EntityConfigParser::parseRenderableComponent(const std::string &xmlContent)
    {
        auto renderable = std::make_unique<RenderableComponent>();

        renderable->meshId = extractValue(xmlContent, "mesh_id");
        renderable->materialId = extractValue(xmlContent, "material_id");
        renderable->isVisible = toBool(extractValue(xmlContent, "visible"), true);
        renderable->opacity = toFloat(extractValue(xmlContent, "opacity"), 1.0f);
        renderable->renderLayer = toInt(extractValue(xmlContent, "render_layer"), 0);

        return renderable;
    }

    std::unique_ptr<PhysicsComponent> EntityConfigParser::parsePhysicsComponent(const std::string &xmlContent)
    {
        auto physics = std::make_unique<PhysicsComponent>();

        physics->hasPhysics = toBool(extractValue(xmlContent, "has_physics"), true);
        physics->mass = toFloat(extractValue(xmlContent, "mass"), 1.0f);
        physics->friction = toFloat(extractValue(xmlContent, "friction"), 0.5f);
        physics->restitution = toFloat(extractValue(xmlContent, "restitution"), 0.3f);
        physics->isKinematic = toBool(extractValue(xmlContent, "is_kinematic"), false);
        physics->useGravity = toBool(extractValue(xmlContent, "use_gravity"), true);
        physics->colliderType = extractValue(xmlContent, "collider_type");
        if (physics->colliderType.empty())
        {
            physics->colliderType = "sphere";
        }

        return physics;
    }

    std::unique_ptr<VehicleComponent> EntityConfigParser::parseVehicleComponent(const std::string &xmlContent)
    {
        auto vehicle = std::make_unique<VehicleComponent>();

        vehicle->vehicleType = extractValue(xmlContent, "vehicle_type");
        if (vehicle->vehicleType.empty())
        {
            vehicle->vehicleType = "drone";
        }

        vehicle->maxSpeed = toFloat(extractValue(xmlContent, "max_speed"), 100.0f);
        vehicle->acceleration = toFloat(extractValue(xmlContent, "acceleration"), 10.0f);
        vehicle->maneuverability = toFloat(extractValue(xmlContent, "maneuverability"), 5.0f);

        vehicle->controllerType = extractValue(xmlContent, "controller_type");
        if (vehicle->controllerType.empty())
        {
            vehicle->controllerType = "manual";
        }

        return vehicle;
    }

    void EntityConfigParser::parseResourceMappings(const std::string &xmlContent, EntityFactoryConfiguration &config)
    {
        // Simple resource mapping parsing - could be enhanced
        // For now, just initialize empty mappings
        config.materialMappings.clear();
        config.meshMappings.clear();
        config.audioclipMappings.clear();
    }

    std::string EntityConfigParser::extractValue(const std::string &xmlContent, const std::string &elementName)
    {
        std::string startTag = "<" + elementName + ">";
        std::string endTag = "</" + elementName + ">";

        size_t startPos = xmlContent.find(startTag);
        if (startPos == std::string::npos)
        {
            return "";
        }

        startPos += startTag.length();
        size_t endPos = xmlContent.find(endTag, startPos);
        if (endPos == std::string::npos)
        {
            return "";
        }

        return xmlContent.substr(startPos, endPos - startPos);
    }

    std::string EntityConfigParser::extractAttribute(const std::string &xmlContent, const std::string &elementName, const std::string &attributeName)
    {
        std::string elementStart = "<" + elementName;
        size_t elementPos = xmlContent.find(elementStart);
        if (elementPos == std::string::npos)
        {
            return "";
        }

        size_t elementEnd = xmlContent.find(">", elementPos);
        if (elementEnd == std::string::npos)
        {
            return "";
        }

        std::string elementTag = xmlContent.substr(elementPos, elementEnd - elementPos + 1);

        std::string attrPattern = attributeName + "=\"";
        size_t attrPos = elementTag.find(attrPattern);
        if (attrPos == std::string::npos)
        {
            return "";
        }

        attrPos += attrPattern.length();
        size_t endPos = elementTag.find("\"", attrPos);
        if (endPos == std::string::npos)
        {
            return "";
        }

        return elementTag.substr(attrPos, endPos - attrPos);
    }

    std::vector<std::string> EntityConfigParser::extractTemplates(const std::string &xmlContent)
    {
        std::vector<std::string> templates;

        size_t pos = 0;
        while (true)
        {
            size_t startPos = xmlContent.find("<template", pos);
            if (startPos == std::string::npos)
            {
                break;
            }

            size_t endPos = xmlContent.find("</template>", startPos);
            if (endPos == std::string::npos)
            {
                break;
            }

            endPos += 11; // length of "</template>"
            std::string templateXml = xmlContent.substr(startPos, endPos - startPos);
            templates.push_back(templateXml);

            pos = endPos;
        }

        return templates;
    }

    int EntityConfigParser::toInt(const std::string &value, int defaultValue)
    {
        if (value.empty())
        {
            return defaultValue;
        }

        try
        {
            return std::stoi(value);
        }
        catch (const std::exception &)
        {
            return defaultValue;
        }
    }

    float EntityConfigParser::toFloat(const std::string &value, float defaultValue)
    {
        if (value.empty())
        {
            return defaultValue;
        }

        try
        {
            return std::stof(value);
        }
        catch (const std::exception &)
        {
            return defaultValue;
        }
    }

    bool EntityConfigParser::toBool(const std::string &value, bool defaultValue)
    {
        if (value.empty())
        {
            return defaultValue;
        }

        if (value == "true" || value == "1" || value == "yes")
        {
            return true;
        }

        if (value == "false" || value == "0" || value == "no")
        {
            return false;
        }

        return defaultValue;
    }

} // namespace EntityConfig


