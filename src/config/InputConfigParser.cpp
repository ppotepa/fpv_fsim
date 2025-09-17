#include "InputConfigParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace Input
{

    InputConfigParser::InputConfigParser(std::unique_ptr<IJsonParserUnified> jsonParser)
        : m_jsonParser(std::move(jsonParser))
    {
    }

    InputConfiguration InputConfigParser::loadFromFile(const std::string &filePath)
    {
        InputConfiguration config;

        try
        {
            if (!m_jsonParser->loadFile(filePath))
            {
                logError("Failed to open file: " + filePath);
                return config;
            }

            return loadFromString("");
        }
        catch (const std::exception &e)
        {
            logError("Exception while loading input config: " + std::string(e.what()));
            return config;
        }
    }

    InputConfiguration InputConfigParser::loadFromString(const std::string &jsonContent)
    {
        InputConfiguration config;

        try
        {
            if (!jsonContent.empty() && !m_jsonParser->loadString(jsonContent))
            {
                logError("Failed to parse JSON content");
                return config;
            }

            // Parse configuration sections
            parseSettings(config);
            parseKeyBindings(config);
            parseContexts(config);

            config.defaultContext = m_jsonParser->getString("defaultContext", "Flight");
        }
        catch (const std::exception &e)
        {
            logError("Exception while parsing input config JSON: " + std::string(e.what()));
        }

        return config;
    }

    bool InputConfigParser::saveToFile(const InputConfiguration &config, const std::string &filePath)
    {
        // TODO: Implement saving configuration back to JSON
        logError("Saving input configuration not yet implemented");
        return false;
    }

    void InputConfigParser::parseSettings(InputConfiguration &config)
    {
        config.settings.mouseSensitivity = m_jsonParser->getFloat("settings.mouseSensitivity", 1.0f);
        config.settings.mouseInvertY = m_jsonParser->getBool("settings.mouseInvertY", false);
        config.settings.keyboardRepeatDelay = m_jsonParser->getInt("settings.keyboardRepeatDelay", 300);
        config.settings.keyboardRepeatRate = m_jsonParser->getInt("settings.keyboardRepeatRate", 50);
        config.settings.gamepadDeadzone = m_jsonParser->getFloat("settings.gamepadDeadzone", 0.1f);
        config.settings.gamepadSensitivity = m_jsonParser->getFloat("settings.gamepadSensitivity", 1.0f);
    }

    void InputConfigParser::parseKeyBindings(InputConfiguration &config)
    {
        // Create default console toggle binding for now
        InputBinding consoleBinding;
        consoleBinding.action = "ToggleDebugConsole";
        consoleBinding.type = BindingType::Key;
        consoleBinding.device = InputDevice::Keyboard;
        consoleBinding.keyCode = KeyCode::TILDE;
        config.keyBindings.push_back(consoleBinding);
    }

    void InputConfigParser::parseMouseBindings(InputConfiguration &config)
    {
        // TODO: Implement mouse bindings parsing
    }

    void InputConfigParser::parseGamepadBindings(InputConfiguration &config)
    {
        // TODO: Implement gamepad bindings parsing
    }

    void InputConfigParser::parseContexts(InputConfiguration &config)
    {
        // Create default flight context
        InputContext flightContext;
        flightContext.name = "Flight";
        flightContext.activeBindings = {"ToggleDebugConsole"};
        config.contexts.push_back(flightContext);
    }

    InputBinding InputConfigParser::parseKeyBinding(const std::string &path, int index)
    {
        InputBinding binding;
        // TODO: Implement actual key binding parsing from JSON
        return binding;
    }

    InputBinding InputConfigParser::parseMouseBinding(const std::string &path, int index)
    {
        return InputBinding{};
    }

    InputBinding InputConfigParser::parseGamepadBinding(const std::string &path, int index)
    {
        return InputBinding{};
    }

    InputContext InputConfigParser::parseContext(const std::string &path, int index)
    {
        InputContext context;
        // TODO: Implement actual context parsing from JSON
        return context;
    }

    void InputConfigParser::logError(const std::string &message)
    {
        lastError_ = message;
        std::cerr << "InputConfigParser Error: " << message << std::endl;
    }

}
