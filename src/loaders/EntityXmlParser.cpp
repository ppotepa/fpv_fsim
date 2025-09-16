#include "EntityXmlParser.h"
#include "platform/PugiXmlParser.h"
#include <iostream>
#include <memory>
#include "../debug.h"

namespace EntityLoader
{

    EntityXmlParser::EntityXmlParser()
        : xmlParser_(std::make_unique<PugiXmlParser>()){
              DEBUG_LOG("Initializing EntityXmlParser");}

          EntityXmlParser::~EntityXmlParser() = default;

    std::unique_ptr<EntityConfig::EntityDefinition> EntityXmlParser::loadFromFile(const std::string &filePath)
    {
        DEBUG_LOG("Loading entity from XML file '" + filePath + "'");
        if (!xmlParser_->loadFile(filePath))
        {
            std::cerr << "Failed to load entity XML file: " << filePath << std::endl;
            std::cerr << "Error: " << xmlParser_->getLastError() << std::endl;
            return nullptr;
        }

        return parseEntity();
    }

    std::unique_ptr<EntityConfig::EntityDefinition> EntityXmlParser::loadFromString(const std::string &xmlContent)
    {
        DEBUG_LOG("Loading entity from XML string");
        if (!xmlParser_->loadString(xmlContent))
        {
            std::cerr << "Failed to parse entity XML string" << std::endl;
            std::cerr << "Error: " << xmlParser_->getLastError() << std::endl;
            return nullptr;
        }

        return parseEntity();
    }

    std::unique_ptr<EntityConfig::EntityDefinition> EntityXmlParser::parseEntity()
    {
        DEBUG_LOG("Parsing entity from XML");
        auto definition = std::make_unique<EntityConfig::EntityDefinition>();

        // Check if it's a valid entity XML
        std::string rootElement = xmlParser_->getRootElementName();
        if (rootElement != "entity")
        {
            std::cerr << "XML file does not have 'entity' as root element. Found: " << rootElement << std::endl;
            return nullptr;
        }

        // Get entity attributes
        std::string entityId = xmlParser_->getElementAttribute("entity", "id");
        std::string entityType = xmlParser_->getElementAttribute("entity", "type");

        // Type is required, but we can work without ID
        if (entityType.empty())
        {
            std::cerr << "Entity XML is missing required type attribute" << std::endl;
            return nullptr;
        }

        // Parse basic entity info
        definition->entityType = entityType;

        // Try both 'n' and 'name' elements for backward compatibility
        definition->name = xmlParser_->getElementText("entity/info/n");
        if (definition->name.empty())
        {
            definition->name = xmlParser_->getElementText("entity/info/name");
        }

        definition->description = xmlParser_->getElementText("entity/info/description");

        std::string startActiveStr = xmlParser_->getElementText("entity/info/active");
        if (!startActiveStr.empty())
        {
            definition->startActive = (startActiveStr == "true" || startActiveStr == "1");
        }
        std::string lifetimeStr = xmlParser_->getElementText("entity/info/lifetime");
        if (!lifetimeStr.empty())
        {
            try
            {
                definition->lifetime = std::stof(lifetimeStr);
            }
            catch (...)
            {
                std::cerr << "Invalid lifetime value: " << lifetimeStr << std::endl;
            }
        }

        // Parse transform
        parseTransform(*definition);

        // Parse optional components
        parseRenderableComponent(*definition);
        parsePhysicsComponent(*definition);
        parseVehicleComponent(*definition);
        parseAudioComponent(*definition);
        parseLightComponent(*definition);

        // Parse custom properties
        parseCustomProperties(*definition);

        DEBUG_LOG("Successfully parsed entity: " << definition->name << " (Type: " << definition->entityType << ")");

        return definition;
    }

    void EntityXmlParser::parseTransform(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing transform component");
        // Check if transform element exists
        if (!xmlParser_->hasElement("transform", "entity"))
        {
            return;
        }

        // Position
        if (xmlParser_->hasElement("position", "entity/transform"))
        {
            std::string posX = xmlParser_->getElementAttribute("entity/transform/position", "x");
            std::string posY = xmlParser_->getElementAttribute("entity/transform/position", "y");
            std::string posZ = xmlParser_->getElementAttribute("entity/transform/position", "z");

            if (!posX.empty())
                definition.transform.position.x = std::stof(posX);
            if (!posY.empty())
                definition.transform.position.y = std::stof(posY);
            if (!posZ.empty())
                definition.transform.position.z = std::stof(posZ);
        }

        // Rotation (Quaternion)
        if (xmlParser_->hasElement("rotation", "entity/transform"))
        {
            std::string rotX = xmlParser_->getElementAttribute("entity/transform/rotation", "x");
            std::string rotY = xmlParser_->getElementAttribute("entity/transform/rotation", "y");
            std::string rotZ = xmlParser_->getElementAttribute("entity/transform/rotation", "z");
            std::string rotW = xmlParser_->getElementAttribute("entity/transform/rotation", "w");

            if (!rotX.empty())
                definition.transform.rotation.x = std::stof(rotX);
            if (!rotY.empty())
                definition.transform.rotation.y = std::stof(rotY);
            if (!rotZ.empty())
                definition.transform.rotation.z = std::stof(rotZ);
            if (!rotW.empty())
                definition.transform.rotation.w = std::stof(rotW);
        }

        // Scale
        if (xmlParser_->hasElement("scale", "entity/transform"))
        {
            std::string scaleX = xmlParser_->getElementAttribute("entity/transform/scale", "x");
            std::string scaleY = xmlParser_->getElementAttribute("entity/transform/scale", "y");
            std::string scaleZ = xmlParser_->getElementAttribute("entity/transform/scale", "z");

            if (!scaleX.empty())
                definition.transform.scale.x = std::stof(scaleX);
            if (!scaleY.empty())
                definition.transform.scale.y = std::stof(scaleY);
            if (!scaleZ.empty())
                definition.transform.scale.z = std::stof(scaleZ);
        }
    }

    void EntityXmlParser::parseRenderableComponent(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing renderable component");
        if (!xmlParser_->hasElement("renderable", "entity"))
        {
            return;
        }

        auto renderable = std::make_unique<EntityConfig::RenderableComponent>();

        renderable->meshId = xmlParser_->getElementText("entity/renderable/mesh");
        renderable->materialId = xmlParser_->getElementText("entity/renderable/material");

        std::string visibleStr = xmlParser_->getElementText("entity/renderable/visible");
        if (!visibleStr.empty())
        {
            renderable->isVisible = (visibleStr == "true" || visibleStr == "1");
        }

        std::string opacityStr = xmlParser_->getElementText("entity/renderable/opacity");
        if (!opacityStr.empty())
        {
            renderable->opacity = std::stof(opacityStr);
        }

        std::string layerStr = xmlParser_->getElementText("entity/renderable/layer");
        if (!layerStr.empty())
        {
            renderable->renderLayer = std::stoi(layerStr);
        }

        definition.renderable = std::move(renderable);
    }

    void EntityXmlParser::parsePhysicsComponent(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing physics component");
        if (!xmlParser_->hasElement("physics", "entity"))
        {
            return;
        }

        auto physics = std::make_unique<EntityConfig::PhysicsComponent>();

        std::string enabledStr = xmlParser_->getElementText("entity/physics/enabled");
        if (!enabledStr.empty())
        {
            physics->hasPhysics = (enabledStr == "true" || enabledStr == "1");
        }

        std::string massStr = xmlParser_->getElementText("entity/physics/mass");
        if (!massStr.empty())
        {
            physics->mass = std::stof(massStr);
        }

        std::string frictionStr = xmlParser_->getElementText("entity/physics/friction");
        if (!frictionStr.empty())
        {
            physics->friction = std::stof(frictionStr);
        }

        std::string restitutionStr = xmlParser_->getElementText("entity/physics/restitution");
        if (!restitutionStr.empty())
        {
            physics->restitution = std::stof(restitutionStr);
        }

        // Parse collider size
        if (xmlParser_->hasElement("collider-size", "entity/physics"))
        {
            std::string sizeX = xmlParser_->getElementAttribute("entity/physics/collider-size", "x");
            std::string sizeY = xmlParser_->getElementAttribute("entity/physics/collider-size", "y");
            std::string sizeZ = xmlParser_->getElementAttribute("entity/physics/collider-size", "z");

            if (!sizeX.empty())
                physics->colliderSize[0] = std::stof(sizeX);
            if (!sizeY.empty())
                physics->colliderSize[1] = std::stof(sizeY);
            if (!sizeZ.empty())
                physics->colliderSize[2] = std::stof(sizeZ);
        }

        std::string kinematicStr = xmlParser_->getElementText("entity/physics/kinematic");
        if (!kinematicStr.empty())
        {
            physics->isKinematic = (kinematicStr == "true" || kinematicStr == "1");
        }

        std::string useGravityStr = xmlParser_->getElementText("entity/physics/use-gravity");
        if (!useGravityStr.empty())
        {
            physics->useGravity = (useGravityStr == "true" || useGravityStr == "1");
        }

        std::string colliderTypeStr = xmlParser_->getElementText("entity/physics/collider-type");
        if (!colliderTypeStr.empty())
        {
            physics->colliderType = colliderTypeStr;
        }

        definition.physics = std::move(physics);
    }

    void EntityXmlParser::parseVehicleComponent(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing vehicle component");
        if (!xmlParser_->hasElement("vehicle", "entity"))
        {
            return;
        }

        auto vehicle = std::make_unique<EntityConfig::VehicleComponent>();

        std::string typeStr = xmlParser_->getElementText("entity/vehicle/type");
        if (!typeStr.empty())
        {
            vehicle->vehicleType = typeStr;
        }

        std::string maxSpeedStr = xmlParser_->getElementText("entity/vehicle/max-speed");
        if (!maxSpeedStr.empty())
        {
            vehicle->maxSpeed = std::stof(maxSpeedStr);
        }

        std::string accelerationStr = xmlParser_->getElementText("entity/vehicle/acceleration");
        if (!accelerationStr.empty())
        {
            vehicle->acceleration = std::stof(accelerationStr);
        }

        std::string maneuverabilityStr = xmlParser_->getElementText("entity/vehicle/maneuverability");
        if (!maneuverabilityStr.empty())
        {
            vehicle->maneuverability = std::stof(maneuverabilityStr);
        }

        std::string controllerTypeStr = xmlParser_->getElementText("entity/vehicle/controller-type");
        if (!controllerTypeStr.empty())
        {
            vehicle->controllerType = controllerTypeStr;
        }

        definition.vehicle = std::move(vehicle);
    }

    void EntityXmlParser::parseAudioComponent(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing audio component");
        if (!xmlParser_->hasElement("audio", "entity"))
        {
            return;
        }

        auto audio = std::make_unique<EntityConfig::AudioComponent>();

        // Try both 'sound-id' and 'sound' elements for backward compatibility
        audio->soundId = xmlParser_->getElementText("entity/audio/sound-id");
        if (audio->soundId.empty())
        {
            audio->soundId = xmlParser_->getElementText("entity/audio/sound");
        }

        std::string volumeStr = xmlParser_->getElementText("entity/audio/volume");
        if (!volumeStr.empty())
        {
            audio->volume = std::stof(volumeStr);
        }

        std::string loopStr = xmlParser_->getElementText("entity/audio/loop");
        if (!loopStr.empty())
        {
            audio->loop = (loopStr == "true" || loopStr == "1");
        }

        definition.audio = std::move(audio);
    }

    void EntityXmlParser::parseLightComponent(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing light component");
        if (!xmlParser_->hasElement("light", "entity"))
        {
            return;
        }

        auto light = std::make_unique<EntityConfig::LightComponent>();

        std::string typeStr = xmlParser_->getElementText("entity/light/type");
        if (!typeStr.empty())
        {
            light->lightType = typeStr;
        }

        // Parse light color
        if (xmlParser_->hasElement("color", "entity/light"))
        {
            std::string colorR = xmlParser_->getElementAttribute("entity/light/color", "r");
            std::string colorG = xmlParser_->getElementAttribute("entity/light/color", "g");
            std::string colorB = xmlParser_->getElementAttribute("entity/light/color", "b");

            if (!colorR.empty())
                light->color[0] = std::stof(colorR);
            if (!colorG.empty())
                light->color[1] = std::stof(colorG);
            if (!colorB.empty())
                light->color[2] = std::stof(colorB);
        }

        std::string intensityStr = xmlParser_->getElementText("entity/light/intensity");
        if (!intensityStr.empty())
        {
            light->intensity = std::stof(intensityStr);
        }

        std::string rangeStr = xmlParser_->getElementText("entity/light/range");
        if (!rangeStr.empty())
        {
            light->range = std::stof(rangeStr);
        }

        definition.light = std::move(light);
    }

    void EntityXmlParser::parseCustomProperties(EntityConfig::EntityDefinition &definition)
    {
        DEBUG_LOG("Parsing custom properties");
        // First try "properties" element (used in existing XML)
        if (xmlParser_->hasElement("properties", "entity"))
        {
            auto propertyElements = xmlParser_->getElementsWithName("property", "entity/properties");

            for (const auto &propertyPath : propertyElements)
            {
                EntityConfig::CustomProperty prop;

                prop.name = xmlParser_->getElementAttribute(propertyPath, "name");
                prop.type = xmlParser_->getElementAttribute(propertyPath, "type");
                prop.value = xmlParser_->getElementText(propertyPath);

                if (!prop.name.empty())
                {
                    definition.customProperties.push_back(prop);
                }
            }
            return;
        }

        // Then try "customProperties" element (newer schema)
        if (xmlParser_->hasElement("customProperties", "entity"))
        {
            auto propertyElements = xmlParser_->getElementsWithName("property", "entity/customProperties");

            for (const auto &propertyPath : propertyElements)
            {
                EntityConfig::CustomProperty prop;

                prop.name = xmlParser_->getElementAttribute(propertyPath, "name");
                prop.type = xmlParser_->getElementAttribute(propertyPath, "type");
                prop.value = xmlParser_->getElementAttribute(propertyPath, "value");

                if (!prop.name.empty())
                {
                    definition.customProperties.push_back(prop);
                }
            }
        }
    }

} // namespace EntityLoader



