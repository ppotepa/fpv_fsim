#ifndef RENDER_CONFIG_PARSER_H
#define RENDER_CONFIG_PARSER_H

#include "RenderConfig.h"
#include <string>

namespace Render
{

    /**
     * @brief Parser for render configuration XML files
     *
     * Loads render configuration from XML files, providing configurable
     * rendering parameters instead of hardcoded values throughout the system.
     */
    class RenderConfigParser
    {
    public:
        /**
         * @brief Load render configuration from XML file
         *
         * @param filePath Path to the render_config.xml file
         * @return RenderConfiguration Parsed configuration with all render settings
         * @throws std::runtime_error if file cannot be loaded or parsed
         */
        static RenderConfiguration loadFromFile(const std::string &filePath);

        /**
         * @brief Load render configuration from XML string
         *
         * @param xmlContent XML content as string
         * @return RenderConfiguration Parsed configuration
         * @throws std::runtime_error if XML cannot be parsed
         */
        static RenderConfiguration loadFromString(const std::string &xmlContent);

    private:
        /**
         * @brief Parse display configuration from XML content
         */
        static DisplayConfig parseDisplayConfig(const std::string &xmlContent);

        /**
         * @brief Parse camera configuration from XML content
         */
        static CameraConfig parseCameraConfig(const std::string &xmlContent);

        /**
         * @brief Parse 2D projection configuration from XML content
         */
        static Projection2DConfig parseProjection2DConfig(const std::string &xmlContent);

        /**
         * @brief Parse console configuration from XML content
         */
        static ConsoleConfig parseConsoleConfig(const std::string &xmlContent);

        /**
         * @brief Parse anti-aliasing configuration from XML content
         */
        static AntiAliasingConfig parseAntiAliasingConfig(const std::string &xmlContent);

        /**
         * @brief Parse performance configuration from XML content
         */
        static PerformanceConfig parsePerformanceConfig(const std::string &xmlContent);

        /**
         * @brief Parse quality configuration from XML content
         */
        static QualityConfig parseQualityConfig(const std::string &xmlContent);

        /**
         * @brief Parse debug configuration from XML content
         */
        static DebugConfig parseDebugConfig(const std::string &xmlContent);

        /**
         * @brief Parse color from XML attributes
         */
        static Color parseColor(const std::string &xmlContent, const std::string &elementName);

        /**
         * @brief Parse 3D position from XML attributes
         */
        static Position3D parsePosition3D(const std::string &xmlContent, const std::string &elementName);

        /**
         * @brief Extract single value from XML element
         */
        static std::string extractValue(const std::string &xmlContent, const std::string &elementName);

        /**
         * @brief Extract attribute value from XML element
         */
        static std::string extractAttribute(const std::string &xmlContent, const std::string &elementName, const std::string &attributeName);

        /**
         * @brief Convert string to integer with validation
         */
        static int toInt(const std::string &value, int defaultValue = 0);

        /**
         * @brief Convert string to float with validation
         */
        static float toFloat(const std::string &value, float defaultValue = 0.0f);

        /**
         * @brief Convert string to boolean with validation
         */
        static bool toBool(const std::string &value, bool defaultValue = false);
    };

} // namespace Render

#endif // RENDER_CONFIG_PARSER_H
