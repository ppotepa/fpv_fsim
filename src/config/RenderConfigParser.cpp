#include "RenderConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "../debug.h"

namespace Render
{

    RenderConfiguration RenderConfigParser::loadFromFile(const std::string &filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            if (Debug())
            {
                std::cout << "Warning: Cannot open render config file '" << filePath << "', using defaults" << std::endl;
            }
            return RenderConfiguration{};
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return loadFromString(buffer.str());
    }

    RenderConfiguration RenderConfigParser::loadFromString(const std::string &xmlContent)
    {
        RenderConfiguration config;

        try
        {
            config.display = parseDisplayConfig(xmlContent);
            config.camera = parseCameraConfig(xmlContent);
            config.projection2D = parseProjection2DConfig(xmlContent);
            config.console = parseConsoleConfig(xmlContent);
            config.antiAliasing = parseAntiAliasingConfig(xmlContent);
            config.performance = parsePerformanceConfig(xmlContent);
            config.quality = parseQualityConfig(xmlContent);
            config.debug = parseDebugConfig(xmlContent);

            if (Debug())
            {
                std::cout << "Render configuration loaded successfully" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            if (Debug())
            {
                std::cout << "Warning: Error parsing render config: " << e.what() << ", using defaults" << std::endl;
            }
            config = RenderConfiguration{}; // Reset to defaults
        }

        return config;
    }

    DisplayConfig RenderConfigParser::parseDisplayConfig(const std::string &xmlContent)
    {
        DisplayConfig config;

        config.windowTitle = extractValue(xmlContent, "window_title");
        if (config.windowTitle.empty())
        {
            config.windowTitle = "FPV Flight Sim - Procedural Earth World";
        }

        config.defaultWidth = toInt(extractValue(xmlContent, "default_width"), 800);
        config.defaultHeight = toInt(extractValue(xmlContent, "default_height"), 600);
        config.fullscreen = toBool(extractValue(xmlContent, "fullscreen"), false);
        config.resizable = toBool(extractValue(xmlContent, "resizable"), true);
        config.vsync = toBool(extractValue(xmlContent, "vsync"), true);

        return config;
    }

    CameraConfig RenderConfigParser::parseCameraConfig(const std::string &xmlContent)
    {
        CameraConfig config;

        config.fieldOfView = toFloat(extractValue(xmlContent, "field_of_view"), 75.0f);
        config.nearPlane = toFloat(extractValue(xmlContent, "near_plane"), 0.1f);
        config.farPlane = toFloat(extractValue(xmlContent, "far_plane"), 10000.0f);
        config.initialPosition = parsePosition3D(xmlContent, "initial_position");
        config.initialTarget = parsePosition3D(xmlContent, "initial_target");

        return config;
    }

    Projection2DConfig RenderConfigParser::parseProjection2DConfig(const std::string &xmlContent)
    {
        Projection2DConfig config;

        config.screenCenterX = toFloat(extractValue(xmlContent, "screen_center_x"), 400.0f);
        config.screenCenterY = toFloat(extractValue(xmlContent, "screen_center_y"), 300.0f);
        config.worldToScreenScale = toFloat(extractValue(xmlContent, "world_to_screen_scale"), 0.01f);
        config.defaultEntityRadius = toFloat(extractValue(xmlContent, "default_entity_radius"), 50.0f);

        return config;
    }

    ConsoleConfig RenderConfigParser::parseConsoleConfig(const std::string &xmlContent)
    {
        ConsoleConfig config;

        config.height = toInt(extractValue(xmlContent, "height"), 200);
        config.backgroundColor = parseColor(xmlContent, "background_color");
        config.borderColor = parseColor(xmlContent, "border_color");
        config.borderWidth = toInt(extractValue(xmlContent, "border_width"), 2);
        config.textColor = parseColor(xmlContent, "text_color");
        config.titleColor = parseColor(xmlContent, "title_color");
        config.marginX = toInt(extractValue(xmlContent, "margin_x"), 10);
        config.marginY = toInt(extractValue(xmlContent, "margin_y"), 20);

        return config;
    }

    AntiAliasingConfig RenderConfigParser::parseAntiAliasingConfig(const std::string &xmlContent)
    {
        AntiAliasingConfig config;

        config.msaaSamples = toInt(extractValue(xmlContent, "msaa_samples"), 4);
        config.enableFXAA = toBool(extractValue(xmlContent, "enable_fxaa"), false);

        return config;
    }

    PerformanceConfig RenderConfigParser::parsePerformanceConfig(const std::string &xmlContent)
    {
        PerformanceConfig config;

        config.maxFps = toInt(extractValue(xmlContent, "max_fps"), 60);
        config.enableFrameLimiting = toBool(extractValue(xmlContent, "enable_frame_limiting"), true);
        config.renderDistance = toFloat(extractValue(xmlContent, "render_distance"), 1000.0f);
        config.lodBias = toFloat(extractValue(xmlContent, "lod_bias"), 1.0f);

        return config;
    }

    QualityConfig RenderConfigParser::parseQualityConfig(const std::string &xmlContent)
    {
        QualityConfig config;

        config.textureFiltering = extractValue(xmlContent, "texture_filtering");
        if (config.textureFiltering.empty())
        {
            config.textureFiltering = "linear";
        }

        config.anisotropicFiltering = toInt(extractValue(xmlContent, "anisotropic_filtering"), 8);

        config.shadowQuality = extractValue(xmlContent, "shadow_quality");
        if (config.shadowQuality.empty())
        {
            config.shadowQuality = "medium";
        }

        config.reflectionQuality = extractValue(xmlContent, "reflection_quality");
        if (config.reflectionQuality.empty())
        {
            config.reflectionQuality = "low";
        }

        return config;
    }

    DebugConfig RenderConfigParser::parseDebugConfig(const std::string &xmlContent)
    {
        DebugConfig config;

        config.showFps = toBool(extractValue(xmlContent, "show_fps"), true);
        config.showWireframe = toBool(extractValue(xmlContent, "show_wireframe"), false);
        config.showBoundingBoxes = toBool(extractValue(xmlContent, "show_bounding_boxes"), false);
        config.showCoordinateAxes = toBool(extractValue(xmlContent, "show_coordinate_axes"), false);

        return config;
    }

    Color RenderConfigParser::parseColor(const std::string &xmlContent, const std::string &elementName)
    {
        Color color;

        // Look for color element with r, g, b, a attributes
        size_t elementPos = xmlContent.find("<" + elementName);
        if (elementPos != std::string::npos)
        {
            size_t endPos = xmlContent.find(">", elementPos);
            if (endPos != std::string::npos)
            {
                std::string element = xmlContent.substr(elementPos, endPos - elementPos + 1);

                color.r = toInt(extractAttribute(element, elementName, "r"), 255);
                color.g = toInt(extractAttribute(element, elementName, "g"), 255);
                color.b = toInt(extractAttribute(element, elementName, "b"), 255);
                color.a = toInt(extractAttribute(element, elementName, "a"), 255);
            }
        }

        return color;
    }

    Position3D RenderConfigParser::parsePosition3D(const std::string &xmlContent, const std::string &elementName)
    {
        Position3D position;

        // Look for position element with x, y, z attributes
        size_t elementPos = xmlContent.find("<" + elementName);
        if (elementPos != std::string::npos)
        {
            size_t endPos = xmlContent.find(">", elementPos);
            if (endPos != std::string::npos)
            {
                std::string element = xmlContent.substr(elementPos, endPos - elementPos + 1);

                position.x = toFloat(extractAttribute(element, elementName, "x"), 0.0f);
                position.y = toFloat(extractAttribute(element, elementName, "y"), 0.0f);
                position.z = toFloat(extractAttribute(element, elementName, "z"), 0.0f);
            }
        }

        return position;
    }

    std::string RenderConfigParser::extractValue(const std::string &xmlContent, const std::string &elementName)
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

    std::string RenderConfigParser::extractAttribute(const std::string &xmlContent, const std::string &elementName, const std::string &attributeName)
    {
        std::string attrPattern = attributeName + "=\"";
        size_t attrPos = xmlContent.find(attrPattern);
        if (attrPos == std::string::npos)
        {
            return "";
        }

        attrPos += attrPattern.length();
        size_t endPos = xmlContent.find("\"", attrPos);
        if (endPos == std::string::npos)
        {
            return "";
        }

        return xmlContent.substr(attrPos, endPos - attrPos);
    }

    int RenderConfigParser::toInt(const std::string &value, int defaultValue)
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

    float RenderConfigParser::toFloat(const std::string &value, float defaultValue)
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

    bool RenderConfigParser::toBool(const std::string &value, bool defaultValue)
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

} // namespace Render
