#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "platform/IInputDevice.h"
#include "config/InputConfig.h"
#include "config/InputConfigParser.h"
#include <string>
#include <unordered_map>
#include <memory>

/**
 * @class InputSystem
 * @brief Enhanced input system with configurable key bindings and input handling
 *
 * This system manages user input through configurable key bindings loaded from XML.
 * It supports keyboard, mouse, and gamepad input with context-sensitive binding sets.
 */
class InputSystem : public ISystem
{
public:
    /**
     * @brief Constructor
     * @param eventBus Event bus for publishing input events
     * @param inputDevice Platform-specific input device implementation
     */
    InputSystem(EventBus &eventBus, IInputDevice &inputDevice);

    /**
     * @brief Load input configuration from file
     * @param configPath Path to input configuration XML file
     * @return True if loaded successfully, false otherwise
     */
    bool loadConfiguration(const std::string &configPath);

    /**
     * @brief Set the current input context
     * @param contextName Name of the context to activate
     */
    void setInputContext(const std::string &contextName);

    /**
     * @brief Get the current input context name
     * @return Current context name
     */
    const std::string &getCurrentContext() const { return currentContext_; }

    /**
     * @brief Get input configuration settings
     * @return Reference to input settings
     */
    const Input::InputSettings &getSettings() const { return config_.settings; }

    /**
     * @brief Update the input system
     * @param world Reference to the world
     * @param dt Delta time
     */
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
    IInputDevice &inputDevice_;
    Input::InputConfiguration config_;
    std::string currentContext_;
    bool debugModeActive_;

    // Input state tracking
    std::unordered_map<Input::KeyCode, bool> keyStates_;
    std::unordered_map<Input::MouseButton, bool> mouseButtonStates_;
    std::unordered_map<Input::GamepadButton, bool> gamepadButtonStates_;
    std::unordered_map<Input::GamepadAxis, float> gamepadAxisValues_;

    // Previous frame state for edge detection
    std::unordered_map<Input::KeyCode, bool> prevKeyStates_;
    std::unordered_map<Input::MouseButton, bool> prevMouseButtonStates_;
    std::unordered_map<Input::GamepadButton, bool> prevGamepadButtonStates_;

    // Input processing methods
    void processKeyboardInput();
    void processMouseInput();
    void processGamepadInput();

    // Event triggering methods
    void triggerInputAction(const std::string &action);
    bool isActionActiveInCurrentContext(const std::string &action) const;

    // State checking helpers
    bool isKeyPressed(Input::KeyCode key) const;
    bool isKeyJustPressed(Input::KeyCode key) const;
    bool isMouseButtonPressed(Input::MouseButton button) const;
    bool isMouseButtonJustPressed(Input::MouseButton button) const;
    bool isGamepadButtonPressed(Input::GamepadButton button) const;
    bool isGamepadButtonJustPressed(Input::GamepadButton button) const;
    float getGamepadAxisValue(Input::GamepadAxis axis) const;

    // Input device integration methods
    void updateKeyboardState();
    void updateMouseState();
    void updateGamepadState();

    // Helper methods
    void updatePreviousStates();
    void initializeDefaultConfiguration();
};

#endif
