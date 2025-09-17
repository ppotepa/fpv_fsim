#include "InputSystem.h"
#include "core/World.h"
#include "events/InputEvents.h"
#include "../platform/NlohmannJsonParser.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "../debug.h"

InputSystem::InputSystem(EventBus &eventBus, IInputDevice &inputDevice)
    : eventBus_(eventBus), inputDevice_(inputDevice), currentContext_("Flight"), debugModeActive_(false)
{
    DEBUG_LOG("Initializing InputSystem with context 'Flight'");
    // Initialize default configuration
    initializeDefaultConfiguration();

    DEBUG_LOG("InputSystem initialized with default configuration");
}

bool InputSystem::loadConfiguration(const std::string &configPath)
{
    DEBUG_LOG("Loading input configuration from '" + configPath + "'");
    try
    {
        auto jsonParser = std::make_unique<NlohmannJsonParser>();
        Input::InputConfigParser parser(std::move(jsonParser));

        config_ = parser.loadFromFile(configPath);

        if (parser.getLastError().empty())
        {
            DEBUG_LOG("Loaded input configuration from: " << configPath);
            DEBUG_LOG("Input bindings loaded:");
            DEBUG_LOG("  Key bindings: " << config_.keyBindings.size());
            DEBUG_LOG("  Mouse bindings: " << config_.mouseBindings.size());
            DEBUG_LOG("  Gamepad bindings: " << config_.gamepadBindings.size());
            DEBUG_LOG("  Contexts: " << config_.contexts.size());

            // Set the default context
            if (!config_.defaultContext.empty())
            {
                setInputContext(config_.defaultContext);
            }

            return true;
        }
        else
        {
            std::cerr << "Failed to load input configuration: " << parser.getLastError() << std::endl;
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception while loading input configuration: " << e.what() << std::endl;
        return false;
    }
}

void InputSystem::setInputContext(const std::string &contextName)
{
    DEBUG_LOG("Setting input context to '" + contextName + "'");
    // Verify the context exists
    bool contextExists = false;
    for (const auto &context : config_.contexts)
    {
        if (context.name == contextName)
        {
            contextExists = true;
            break;
        }
    }

    if (contextExists || contextName == config_.defaultContext)
    {
        currentContext_ = contextName;
        DEBUG_LOG("Input context set to: " << contextName);
    }
    else
    {
        std::cerr << "Unknown input context: " << contextName << std::endl;
    }
}

void InputSystem::update(World &world, float dt)
{
    // Poll the input device
    inputDevice_.poll();

    // Update input states
    updateKeyboardState();
    updateMouseState();
    updateGamepadState();

    // Process input based on current configuration
    processKeyboardInput();
    processMouseInput();
    processGamepadInput();

    // Update previous states for next frame
    updatePreviousStates();
}

void InputSystem::processKeyboardInput()
{
    // Handle F9 debug mode toggle globally (works in any context)
    if (isKeyJustPressed(Input::KeyCode::F9))
    {
        debugModeActive_ = !debugModeActive_;
        eventBus_.publish(DebugModeToggled{debugModeActive_});
        DEBUG_LOG("Debug mode toggled: " << (debugModeActive_ ? "ON" : "OFF"));
    }

    for (const auto &binding : config_.keyBindings)
    {
        if (binding.device == Input::InputDevice::Keyboard &&
            isActionActiveInCurrentContext(binding.action))
        {

            if (isKeyJustPressed(binding.keyCode))
            {
                triggerInputAction(binding.action);
            }
        }
    }
}

void InputSystem::processMouseInput()
{
    for (const auto &binding : config_.mouseBindings)
    {
        if (binding.device == Input::InputDevice::Mouse &&
            isActionActiveInCurrentContext(binding.action))
        {

            if (isMouseButtonJustPressed(binding.mouseButton))
            {
                triggerInputAction(binding.action);
            }
        }
    }
}

void InputSystem::processGamepadInput()
{
    for (const auto &binding : config_.gamepadBindings)
    {
        if (binding.device == Input::InputDevice::Gamepad &&
            isActionActiveInCurrentContext(binding.action))
        {

            if (binding.type == Input::BindingType::GamepadButton)
            {
                if (isGamepadButtonJustPressed(binding.gamepadButton))
                {
                    triggerInputAction(binding.action);
                }
            }
            else if (binding.type == Input::BindingType::GamepadAxis)
            {
                float axisValue = getGamepadAxisValue(binding.gamepadAxis);

                // Handle directional axis bindings
                if (binding.direction == "positive" && axisValue > config_.settings.gamepadDeadzone)
                {
                    triggerInputAction(binding.action);
                }
                else if (binding.direction == "negative" && axisValue < -config_.settings.gamepadDeadzone)
                {
                    triggerInputAction(binding.action);
                }
                else if (binding.direction.empty() && std::abs(axisValue) > config_.settings.gamepadDeadzone)
                {
                    triggerInputAction(binding.action);
                }
            }
            else if (binding.type == Input::BindingType::GamepadTrigger)
            {
                float triggerValue = getGamepadAxisValue(binding.gamepadAxis);
                if (triggerValue > config_.settings.gamepadDeadzone)
                {
                    triggerInputAction(binding.action);
                }
            }
        }
    }
}

void InputSystem::triggerInputAction(const std::string &action)
{
    DEBUG_LOG("Triggering input action '" + action + "'");
    // Handle specific actions
    if (action == "ToggleDebugConsole")
    {
        eventBus_.publish(ConsoleToggleEvent{});
        DEBUG_LOG("Console toggle triggered");
    }
    else if (action == "ToggleWireframe")
    {
        DEBUG_LOG("Wireframe toggle triggered");
        // TODO: Implement wireframe toggle event
    }
    else if (action == "TogglePerfMetrics")
    {
        DEBUG_LOG("Performance metrics toggle triggered");
        // TODO: Implement performance metrics toggle event
    }
    else if (action == "ReloadAssets")
    {
        DEBUG_LOG("Asset reload triggered");
        // TODO: Implement asset reload event
    }
    else if (action == "Quit")
    {
        DEBUG_LOG("Quit triggered");
        // TODO: Implement quit event
    }
    else
    {
        // For other actions, just log for now
        DEBUG_LOG("Input action triggered: " << action);
    }
}

bool InputSystem::isActionActiveInCurrentContext(const std::string &action) const
{
    // Find the current context
    for (const auto &context : config_.contexts)
    {
        if (context.name == currentContext_)
        {
            // Check if the action is in the active bindings list
            return std::find(context.activeBindings.begin(), context.activeBindings.end(), action) != context.activeBindings.end();
        }
    }

    // If context not found, allow all actions
    return true;
}

// Input state checking methods using Windows API
bool InputSystem::isKeyPressed(Input::KeyCode key) const
{
    return (GetAsyncKeyState(static_cast<int>(key)) & 0x8000) != 0;
}

bool InputSystem::isKeyJustPressed(Input::KeyCode key) const
{
    return isKeyPressed(key) && !prevKeyStates_.count(key);
}

bool InputSystem::isMouseButtonPressed(Input::MouseButton button) const
{
    int vkCode = 0;
    switch (button)
    {
    case Input::MouseButton::LEFT:
        vkCode = VK_LBUTTON;
        break;
    case Input::MouseButton::RIGHT:
        vkCode = VK_RBUTTON;
        break;
    case Input::MouseButton::MIDDLE:
        vkCode = VK_MBUTTON;
        break;
    case Input::MouseButton::X1:
        vkCode = VK_XBUTTON1;
        break;
    case Input::MouseButton::X2:
        vkCode = VK_XBUTTON2;
        break;
    default:
        return false;
    }
    return (GetAsyncKeyState(vkCode) & 0x8000) != 0;
}

bool InputSystem::isMouseButtonJustPressed(Input::MouseButton button) const
{
    return isMouseButtonPressed(button) && !prevMouseButtonStates_.count(button);
}

bool InputSystem::isGamepadButtonPressed(Input::GamepadButton button) const
{
    // TODO: Implement gamepad button state checking
    return false;
}

bool InputSystem::isGamepadButtonJustPressed(Input::GamepadButton button) const
{
    return isGamepadButtonPressed(button) && !prevGamepadButtonStates_.count(button);
}

float InputSystem::getGamepadAxisValue(Input::GamepadAxis axis) const
{
    // TODO: Implement gamepad axis value reading
    return 0.0f;
}

void InputSystem::updateKeyboardState()
{
    // Update current key states
    for (const auto &binding : config_.keyBindings)
    {
        Input::KeyCode key = binding.keyCode;
        keyStates_[key] = isKeyPressed(key);
    }
}

void InputSystem::updateMouseState()
{
    // Update current mouse button states
    for (const auto &binding : config_.mouseBindings)
    {
        Input::MouseButton button = binding.mouseButton;
        mouseButtonStates_[button] = isMouseButtonPressed(button);
    }
}

void InputSystem::updateGamepadState()
{
    // TODO: Implement gamepad state updates
}

void InputSystem::updatePreviousStates()
{
    // Update previous frame states
    prevKeyStates_ = keyStates_;
    prevMouseButtonStates_ = mouseButtonStates_;
    prevGamepadButtonStates_ = gamepadButtonStates_;
}

void InputSystem::initializeDefaultConfiguration()
{
    // Initialize basic default configuration
    config_.settings.mouseSensitivity = 1.0f;
    config_.settings.mouseInvertY = false;
    config_.settings.keyboardRepeatDelay = 300;
    config_.settings.keyboardRepeatRate = 50;
    config_.settings.gamepadDeadzone = 0.1f;
    config_.settings.gamepadSensitivity = 1.0f;
    config_.defaultContext = "Flight";

    // Add basic console toggle binding
    Input::InputBinding consoleBinding;
    consoleBinding.action = "ToggleDebugConsole";
    consoleBinding.type = Input::BindingType::Key;
    consoleBinding.device = Input::InputDevice::Keyboard;
    consoleBinding.keyCode = Input::KeyCode::TILDE;
    config_.keyBindings.push_back(consoleBinding);

    // Add basic flight context
    Input::InputContext flightContext;
    flightContext.name = "Flight";
    flightContext.activeBindings = {"ToggleDebugConsole"};
    config_.contexts.push_back(flightContext);
}
