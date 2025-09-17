#ifndef RENDER_CONFIG_PARSER_H
#define RENDER_CONFIG_PARSER_H

#include "RenderConfig.h"
#include "../utils/IJsonParserUnified.h"
#include <string>
#include <memory>

namespace Render
{

    /**
     * @brief Parser for render configuration JSON files
     *
     * Loads render configuration from JSON files, providing configurable
     * rendering parameters instead of hardcoded values throughout the system.
     */
    class RenderConfigParser
    {
    public:
        /**
         * @brief Constructor
         * @param jsonParser JSON parser implementation to use
         */
        explicit RenderConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser);

        /**
         * @brief Load render configuration from JSON file
         *
         * @param filePath Path to the render_config.json file
         * @return RenderConfiguration Parsed configuration with all render settings
         * @throws std::runtime_error if file cannot be loaded or parsed
         */
        RenderConfiguration loadFromFile(const std::string &filePath);

        /**
         * @brief Load render configuration from JSON string
         *
         * @param jsonContent JSON content as string
         * @return RenderConfiguration Parsed configuration
         * @throws std::runtime_error if JSON cannot be parsed
         */
        RenderConfiguration loadFromString(const std::string &jsonContent);

    private:
        std::unique_ptr<IJsonParserUnified> m_jsonParser;

        /**
         * @brief Parse display configuration from JSON content
         */
        DisplayConfig parseDisplayConfig();

        /**
         * @brief Parse camera configuration from JSON content
         */
        CameraConfig parseCameraConfig();

        /**
         * @brief Parse 2D projection configuration from JSON content
         */
        Projection2DConfig parseProjection2DConfig();

        /**
         * @brief Parse console configuration from JSON content
         */
        ConsoleConfig parseConsoleConfig();

        /**
         * @brief Parse anti-aliasing configuration from JSON content
         */
        AntiAliasingConfig parseAntiAliasingConfig();

        /**
         * @brief Parse performance configuration from JSON content
         */
        PerformanceConfig parsePerformanceConfig();

        /**
         * @brief Parse quality configuration from JSON content
         */
        QualityConfig parseQualityConfig();

        /**
         * @brief Parse debug configuration from JSON content
         */
        DebugConfig parseDebugConfig();

        /**
         * @brief Parse color from JSON object
         */
        Color parseColor(const std::string &path);

        /**
         * @brief Parse 3D position from JSON object
         */
        Position3D parsePosition3D(const std::string &path);
    };

} // namespace Render

#endif // RENDER_CONFIG_PARSER_H
