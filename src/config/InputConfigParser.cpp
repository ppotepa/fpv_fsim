#include "InputConfigParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace Input
{

    InputConfigParser::InputConfigParser(std::unique_ptr<IXmlParserUnified> xmlParser)
        : xmlParser_(std::move(xmlParser))
    {
    }

    InputConfiguration InputConfigParser::loadFromFile(const std::string &filePath)
    {
        InputConfiguration config;

        try
        {
            // Read file content manually
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                logError("Failed to open file: " + filePath);
                return config;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string xmlContent = buffer.str();
            file.close();

            return loadFromString(xmlContent);
        }
        catch (const std::exception &e)
        {
            logError("Exception while loading input config: " + std::string(e.what()));
            return config;
        }
    }

    InputConfiguration InputConfigParser::loadFromString(const std::string &xmlContent)
    {
        InputConfiguration config;

        try
        {
            // For now, just parse a simple console toggle binding
            // Look for the ToggleDebugConsole binding with TILDE key
            if (xmlContent.find("ToggleDebugConsole") != std::string::npos &&
                xmlContent.find("TILDE") != std::string::npos)
            {

                InputBinding consoleBinding;
                consoleBinding.action = "ToggleDebugConsole";
                consoleBinding.type = BindingType::Key;
                consoleBinding.device = InputDevice::Keyboard;
                consoleBinding.keyCode = KeyCode::TILDE;
                config.keyBindings.push_back(consoleBinding);
            }

            // Set up basic flight context
            InputContext flightContext;
            flightContext.name = "Flight";
            flightContext.activeBindings = {"ToggleDebugConsole"};
            config.contexts.push_back(flightContext);

            config.defaultContext = "Flight";

            // Set default settings
            config.settings.mouseSensitivity = 1.0f;
            config.settings.mouseInvertY = false;
            config.settings.keyboardRepeatDelay = 300;
            config.settings.keyboardRepeatRate = 50;
            config.settings.gamepadDeadzone = 0.1f;
            config.settings.gamepadSensitivity = 1.0f;
        }
        catch (const std::exception &e)
        {
            logError("Exception while parsing input config XML: " + std::string(e.what()));
        }

        return config;
    }

    bool InputConfigParser::saveToFile(const InputConfiguration &config, const std::string &filePath)
    {
        // TODO: Implement saving configuration back to XML
        logError("Saving input configuration not yet implemented");
        return false;
    }

    void InputConfigParser::parseSettings(const std::string &xmlContent, InputConfiguration &config)
    {
        // Simplified - not implemented yet
    }

    void InputConfigParser::parseKeyBindings(const std::string &xmlContent, InputConfiguration &config)
    {
        // Simplified - basic parsing done in loadFromString
    }

    void InputConfigParser::parseMouseBindings(const std::string &xmlContent, InputConfiguration &config)
    {
        // Simplified - not implemented yet
    }

    void InputConfigParser::parseGamepadBindings(const std::string &xmlContent, InputConfiguration &config)
    {
        // Simplified - not implemented yet
    }

    void InputConfigParser::parseContexts(const std::string &xmlContent, InputConfiguration &config)
    {
        // Simplified - basic context setup done in loadFromString
    }

    InputBinding InputConfigParser::parseKeyBinding(const std::string &bindingXml)
    {
        return InputBinding{};
    }

    InputBinding InputConfigParser::parseMouseBinding(const std::string &bindingXml)
    {
        return InputBinding{};
    }

    InputBinding InputConfigParser::parseGamepadBinding(const std::string &bindingXml)
    {
        return InputBinding{};
    }

    InputContext InputConfigParser::parseContext(const std::string &contextXml)
    {
        return InputContext{};
    }

    std::string InputConfigParser::extractAttributeValue(const std::string &xml, const std::string &attributeName)
    {
        return "";
    }

    std::vector<std::string> InputConfigParser::parseActiveBindings(const std::string &activeBindingsStr)
    {
        std::vector<std::string> bindings;
        std::stringstream ss(activeBindingsStr);
        std::string binding;

        while (std::getline(ss, binding, ','))
        {
            // Remove whitespace
            binding.erase(std::remove_if(binding.begin(), binding.end(), ::isspace), binding.end());
            if (!binding.empty())
            {
                bindings.push_back(binding);
            }
        }

        return bindings;
    }

    void InputConfigParser::logError(const std::string &message)
    {
        lastError_ = message;
        std::cerr << "InputConfigParser Error: " << message << std::endl;
    }
}


