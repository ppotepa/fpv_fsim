#ifndef RENDER_CONFIG_H
#define RENDER_CONFIG_H

#include <string>

namespace Render
{

    /**
     * @brief Color structure for rendering configuration
     */
    struct Color
    {
        int r = 255;
        int g = 255;
        int b = 255;
        int a = 255;

        Color() = default;
        Color(int red, int green, int blue, int alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}
    };

    /**
     * @brief 3D position structure
     */
    struct Position3D
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Position3D() = default;
        Position3D(float x_val, float y_val, float z_val)
            : x(x_val), y(y_val), z(z_val) {}
    };

    /**
     * @brief Display configuration settings
     */
    struct DisplayConfig
    {
        std::string windowTitle = "FPV Flight Sim";
        int defaultWidth = 800;
        int defaultHeight = 600;
        bool fullscreen = false;
        bool resizable = true;
        bool vsync = true;
    };

    /**
     * @brief Camera and projection settings
     */
    struct CameraConfig
    {
        float fieldOfView = 75.0f;
        float nearPlane = 0.1f;
        float farPlane = 10000.0f;
        Position3D initialPosition{0.0f, 100.0f, 0.0f};
        Position3D initialTarget{0.0f, 0.0f, 0.0f};
    };

    /**
     * @brief 2D projection settings for current basic renderer
     */
    struct Projection2DConfig
    {
        float screenCenterX = 400.0f;
        float screenCenterY = 300.0f;
        float worldToScreenScale = 0.01f;
        float defaultEntityRadius = 50.0f;
    };

    /**
     * @brief Console rendering configuration
     */
    struct ConsoleConfig
    {
        int height = 200;
        Color backgroundColor{0, 0, 0, 128};
        Color borderColor{255, 255, 255};
        int borderWidth = 2;
        Color textColor{255, 255, 255};
        Color titleColor{255, 255, 0};
        int marginX = 10;
        int marginY = 20;
    };

    /**
     * @brief Anti-aliasing configuration
     */
    struct AntiAliasingConfig
    {
        int msaaSamples = 4;
        bool enableFXAA = false;
    };

    /**
     * @brief Performance settings
     */
    struct PerformanceConfig
    {
        int maxFps = 60;
        bool enableFrameLimiting = true;
        float renderDistance = 1000.0f;
        float lodBias = 1.0f;
    };

    /**
     * @brief Quality settings
     */
    struct QualityConfig
    {
        std::string textureFiltering = "linear";
        int anisotropicFiltering = 8;
        std::string shadowQuality = "medium";
        std::string reflectionQuality = "low";
    };

    /**
     * @brief Debug rendering settings
     */
    struct DebugConfig
    {
        bool showFps = true;
        bool showWireframe = false;
        bool showBoundingBoxes = false;
        bool showCoordinateAxes = false;
    };

    /**
     * @brief Complete render configuration
     */
    struct RenderConfiguration
    {
        DisplayConfig display;
        CameraConfig camera;
        Projection2DConfig projection2D;
        ConsoleConfig console;
        AntiAliasingConfig antiAliasing;
        PerformanceConfig performance;
        QualityConfig quality;
        DebugConfig debug;

        // Helper methods for accessing commonly used values
        int getWindowWidth() const { return display.defaultWidth; }
        int getWindowHeight() const { return display.defaultHeight; }
        const std::string &getWindowTitle() const { return display.windowTitle; }

        float getScreenCenterX() const { return projection2D.screenCenterX; }
        float getScreenCenterY() const { return projection2D.screenCenterY; }
        float getWorldToScreenScale() const { return projection2D.worldToScreenScale; }
        float getDefaultEntityRadius() const { return projection2D.defaultEntityRadius; }

        int getConsoleHeight() const { return console.height; }
        const Color &getConsoleBackgroundColor() const { return console.backgroundColor; }
        const Color &getConsoleBorderColor() const { return console.borderColor; }
        int getConsoleBorderWidth() const { return console.borderWidth; }
        const Color &getConsoleTextColor() const { return console.textColor; }
        const Color &getConsoleTitleColor() const { return console.titleColor; }
        int getConsoleMarginX() const { return console.marginX; }
        int getConsoleMarginY() const { return console.marginY; }
    };

} // namespace Render

#endif // RENDER_CONFIG_H
