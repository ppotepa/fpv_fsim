#ifndef INPUT_CONFIG_PARSER_H
#define INPUT_CONFIG_PARSER_H

#include "InputConfig.h"
#include "../utils/IJsonParserUnified.h"
#include <memory>
#include <string>

namespace Input
{

    /**
     * @class InputConfigParser
     * @brief Parser for input configuration JSON files
     *
     * This class handles loading and parsing input configuration JSON files,
     * converting them into InputConfiguration structures that can be used
     * by the InputSystem.
     */
    class InputConfigParser
    {
    public:
        /**
         * @brief Constructor
         * @param jsonParser JSON parser implementation to use
         */
        explicit InputConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser);

        /**
         * @brief Load input configuration from file
         * @param filePath Path to the input configuration XML file
         * @return InputConfiguration structure, or empty config on failure
         */
        InputConfiguration loadFromFile(const std::string &filePath);

        /**
         * @brief Load input configuration from JSON string
         * @param jsonContent JSON content as string
         * @return InputConfiguration structure, or empty config on failure
         */
        InputConfiguration loadFromString(const std::string &jsonContent);

        /**
         * @brief Save input configuration to file
         * @param config Configuration to save
         * @param filePath Target file path
         * @return True if successful, false otherwise
         */
        bool saveToFile(const InputConfiguration &config, const std::string &filePath);

        /**
         * @brief Get the last error message
         * @return Last error message, empty if no error
         */
        const std::string &getLastError() const { return lastError_; }

    private:
        std::unique_ptr<IJsonParserUnified> m_jsonParser;
        std::string lastError_;

        // Helper methods for parsing different sections
        void parseSettings(InputConfiguration &config);
        void parseKeyBindings(InputConfiguration &config);
        void parseMouseBindings(InputConfiguration &config);
        void parseGamepadBindings(InputConfiguration &config);
        void parseContexts(InputConfiguration &config);

        // Helper methods for parsing individual elements
        InputBinding parseKeyBinding(const std::string &path, int index);
        InputBinding parseMouseBinding(const std::string &path, int index);
        InputBinding parseGamepadBinding(const std::string &path, int index);
        InputContext parseContext(const std::string &path, int index);

        // Utility methods
        void logError(const std::string &message);
    };
}

#endif
