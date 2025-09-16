#ifndef INPUT_CONFIG_PARSER_H
#define INPUT_CONFIG_PARSER_H

#include "InputConfig.h"
#include "../utils/IXmlParserUnified.h"
#include <memory>
#include <string>

namespace Input
{

    /**
     * @class InputConfigParser
     * @brief Parser for input configuration XML files
     *
     * This class handles loading and parsing input configuration XML files,
     * converting them into InputConfiguration structures that can be used
     * by the InputSystem.
     */
    class InputConfigParser
    {
    public:
        /**
         * @brief Constructor
         * @param xmlParser XML parser implementation to use
         */
        explicit InputConfigParser(std::unique_ptr<IXmlParserUnified> xmlParser);

        /**
         * @brief Load input configuration from file
         * @param filePath Path to the input configuration XML file
         * @return InputConfiguration structure, or empty config on failure
         */
        InputConfiguration loadFromFile(const std::string &filePath);

        /**
         * @brief Load input configuration from XML string
         * @param xmlContent XML content as string
         * @return InputConfiguration structure, or empty config on failure
         */
        InputConfiguration loadFromString(const std::string &xmlContent);

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
        std::unique_ptr<IXmlParserUnified> xmlParser_;
        std::string lastError_;

        // Helper methods for parsing different sections
        void parseSettings(const std::string &settingsXml, InputConfiguration &config);
        void parseKeyBindings(const std::string &bindingsXml, InputConfiguration &config);
        void parseMouseBindings(const std::string &bindingsXml, InputConfiguration &config);
        void parseGamepadBindings(const std::string &bindingsXml, InputConfiguration &config);
        void parseContexts(const std::string &contextsXml, InputConfiguration &config);

        // Helper methods for parsing individual elements
        InputBinding parseKeyBinding(const std::string &bindingXml);
        InputBinding parseMouseBinding(const std::string &bindingXml);
        InputBinding parseGamepadBinding(const std::string &bindingXml);
        InputContext parseContext(const std::string &contextXml);

        // Utility methods
        std::string extractAttributeValue(const std::string &xml, const std::string &attributeName);
        std::vector<std::string> parseActiveBindings(const std::string &activeBindingsStr);
        void logError(const std::string &message);
    };
}

#endif

