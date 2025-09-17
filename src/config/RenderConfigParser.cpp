#include "RenderConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "../debug.h"

namespace Render
{

    RenderConfigParser::RenderConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser)
        : m_jsonParser(std::move(jsonParser))
    {
    }

    RenderConfiguration RenderConfigParser::loadFromFile(const std::string &filePath)
    {
        if (!m_jsonParser->loadFile(filePath))
        {
            if (Debug())
            {
                DEBUG_LOG("Warning: Cannot open render config file '" << filePath << "', using defaults");
            }
            return RenderConfiguration{};
        }

        return loadFromString("");
    }

    RenderConfiguration RenderConfigParser::loadFromString(const std::string &jsonContent)
    {
        if (!jsonContent.empty() && !m_jsonParser->loadString(jsonContent))
        {
            if (Debug())
            {
                DEBUG_LOG("Warning: Cannot parse render config JSON content, using defaults");
            }
            return RenderConfiguration{};
        }

        RenderConfiguration config;

        try
        {
            config.display = parseDisplayConfig();
            config.camera = parseCameraConfig();
            config.projection2D = parseProjection2DConfig();
            config.console = parseConsoleConfig();
            config.antiAliasing = parseAntiAliasingConfig();
            config.performance = parsePerformanceConfig();
            config.quality = parseQualityConfig();
            config.debug = parseDebugConfig();

            if (Debug())
            {
                DEBUG_LOG("Render configuration loaded successfully");
            }
        }
        catch (const std::exception &e)
        {
            if (Debug())
            {
                DEBUG_LOG("Warning: Error parsing render config: " << e.what() << ", using defaults");
            }
            config = RenderConfiguration{}; // Reset to defaults
        }

        return config;
    }

    DisplayConfig RenderConfigParser::parseDisplayConfig()
    {
        DisplayConfig config;

        config.windowTitle = m_jsonParser->getString("display.windowTitle", "FPV Flight Sim - Scene Loading...");
        config.defaultWidth = m_jsonParser->getInt("display.defaultWidth", 800);
        config.defaultHeight = m_jsonParser->getInt("display.defaultHeight", 600);
        config.fullscreen = m_jsonParser->getBool("display.fullscreen", false);
        config.resizable = m_jsonParser->getBool("display.resizable", true);
        config.vsync = m_jsonParser->getBool("display.vsync", true);

        return config;
    }

    CameraConfig RenderConfigParser::parseCameraConfig()
    {
        CameraConfig config;

        config.fieldOfView = m_jsonParser->getFloat("camera.fieldOfView", 75.0f);
        config.nearPlane = m_jsonParser->getFloat("camera.nearPlane", 0.1f);
        config.farPlane = m_jsonParser->getFloat("camera.farPlane", 10000.0f);
        config.initialPosition = parsePosition3D("camera.initialPosition");
        config.initialTarget = parsePosition3D("camera.initialTarget");

        return config;
    }

    Projection2DConfig RenderConfigParser::parseProjection2DConfig()
    {
        Projection2DConfig config;

        config.screenCenterX = m_jsonParser->getFloat("projection2D.screenCenterX", 400.0f);
        config.screenCenterY = m_jsonParser->getFloat("projection2D.screenCenterY", 300.0f);
        config.worldToScreenScale = m_jsonParser->getFloat("projection2D.worldToScreenScale", 0.01f);
        config.defaultEntityRadius = m_jsonParser->getFloat("projection2D.defaultEntityRadius", 50.0f);

        return config;
    }

    ConsoleConfig RenderConfigParser::parseConsoleConfig()
    {
        ConsoleConfig config;

        config.height = m_jsonParser->getInt("console.height", 200);
        config.backgroundColor = parseColor("console.backgroundColor");
        config.borderColor = parseColor("console.borderColor");
        config.borderWidth = m_jsonParser->getInt("console.borderWidth", 2);
        config.textColor = parseColor("console.textColor");
        config.titleColor = parseColor("console.titleColor");
        config.marginX = m_jsonParser->getInt("console.marginX", 10);
        config.marginY = m_jsonParser->getInt("console.marginY", 20);

        return config;
    }

    AntiAliasingConfig RenderConfigParser::parseAntiAliasingConfig()
    {
        AntiAliasingConfig config;

        config.msaaSamples = m_jsonParser->getInt("antiAliasing.msaaSamples", 4);
        config.enableFXAA = m_jsonParser->getBool("antiAliasing.enableFXAA", false);

        return config;
    }

    PerformanceConfig RenderConfigParser::parsePerformanceConfig()
    {
        PerformanceConfig config;

        config.maxFps = m_jsonParser->getInt("performance.maxFps", 60);
        config.enableFrameLimiting = m_jsonParser->getBool("performance.enableFrameLimiting", true);
        config.renderDistance = m_jsonParser->getFloat("performance.renderDistance", 1000.0f);
        config.lodBias = m_jsonParser->getFloat("performance.lodBias", 1.0f);

        return config;
    }

    QualityConfig RenderConfigParser::parseQualityConfig()
    {
        QualityConfig config;

        config.textureFiltering = m_jsonParser->getString("quality.textureFiltering", "linear");
        config.anisotropicFiltering = m_jsonParser->getInt("quality.anisotropicFiltering", 8);
        config.shadowQuality = m_jsonParser->getString("quality.shadowQuality", "medium");
        config.reflectionQuality = m_jsonParser->getString("quality.reflectionQuality", "low");

        return config;
    }

    DebugConfig RenderConfigParser::parseDebugConfig()
    {
        DebugConfig config;

        config.showFps = m_jsonParser->getBool("debug.showFps", true);
        config.showWireframe = m_jsonParser->getBool("debug.showWireframe", false);
        config.showBoundingBoxes = m_jsonParser->getBool("debug.showBoundingBoxes", false);
        config.showCoordinateAxes = m_jsonParser->getBool("debug.showCoordinateAxes", false);

        return config;
    }

    Color RenderConfigParser::parseColor(const std::string &path)
    {
        Color color;

        color.r = m_jsonParser->getInt(path + ".r", 255);
        color.g = m_jsonParser->getInt(path + ".g", 255);
        color.b = m_jsonParser->getInt(path + ".b", 255);
        color.a = m_jsonParser->getInt(path + ".a", 255);

        return color;
    }

    Position3D RenderConfigParser::parsePosition3D(const std::string &path)
    {
        Position3D position;

        position.x = m_jsonParser->getFloat(path + ".x", 0.0f);
        position.y = m_jsonParser->getFloat(path + ".y", 0.0f);
        position.z = m_jsonParser->getFloat(path + ".z", 0.0f);

        return position;
    }

} // namespace Render
