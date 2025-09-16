#ifndef INPUT_CONFIG_H
#define INPUT_CONFIG_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Input
{

    // Key codes for keyboard input
    enum class KeyCode
    {
        Unknown = 0,

        // Letters
        A = 65,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        // Numbers
        Num0 = 48,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        // Function keys
        F1 = 112,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        // Arrow keys
        LEFT = 37,
        UP,
        RIGHT,
        DOWN,

        // Special keys
        SPACE = 32,
        ENTER = 13,
        ESCAPE = 27,
        TAB = 9,
        BACKSPACE = 8,
        KEY_DELETE = 46,
        INSERT = 45,
        HOME = 36,
        END = 35,
        PAGE_UP = 33,
        PAGE_DOWN = 34,

        // Modifier keys
        LSHIFT = 160,
        RSHIFT = 161,
        LCTRL = 162,
        RCTRL = 163,
        LALT = 164,
        RALT = 165,

        // Special characters
        TILDE = 192,
        MINUS = 189,
        EQUALS = 187,
        LBRACKET = 219,
        RBRACKET = 221,
        BACKSLASH = 220,
        SEMICOLON = 186,
        QUOTE = 222,
        COMMA = 188,
        PERIOD = 190,
        SLASH = 191
    };

    // Mouse buttons
    enum class MouseButton
    {
        Unknown = 0,
        LEFT = 1,
        RIGHT = 2,
        MIDDLE = 3,
        X1 = 4,
        X2 = 5
    };

    // Gamepad buttons (Xbox controller layout)
    enum class GamepadButton
    {
        Unknown = 0,
        A = 1,
        B = 2,
        X = 3,
        Y = 4,
        LEFT_SHOULDER = 5,
        RIGHT_SHOULDER = 6,
        SELECT = 7,
        START = 8,
        LEFT_STICK = 9,
        RIGHT_STICK = 10,
        DPAD_UP = 11,
        DPAD_DOWN = 12,
        DPAD_LEFT = 13,
        DPAD_RIGHT = 14
    };

    // Gamepad axes
    enum class GamepadAxis
    {
        Unknown = 0,
        LEFT_STICK_X = 1,
        LEFT_STICK_Y = 2,
        RIGHT_STICK_X = 3,
        RIGHT_STICK_Y = 4,
        LEFT_TRIGGER = 5,
        RIGHT_TRIGGER = 6
    };

    // Input devices
    enum class InputDevice
    {
        Unknown = 0,
        Keyboard,
        Mouse,
        Gamepad
    };

    // Input binding types
    enum class BindingType
    {
        Key,
        MouseButton,
        GamepadButton,
        GamepadAxis,
        GamepadTrigger
    };

    // Structure to hold a single input binding
    struct InputBinding
    {
        std::string action;
        BindingType type;
        InputDevice device;

        // Union for different input types
        union
        {
            KeyCode keyCode;
            MouseButton mouseButton;
            GamepadButton gamepadButton;
            GamepadAxis gamepadAxis;
        };

        // For axis bindings
        std::string direction; // "positive", "negative", or empty for full range

        InputBinding() : action(""), type(BindingType::Key), device(InputDevice::Unknown), keyCode(KeyCode::Unknown), direction("") {}
    };

    // Input context for different game states
    struct InputContext
    {
        std::string name;
        std::vector<std::string> activeBindings;
    };

    // Global input settings
    struct InputSettings
    {
        float mouseSensitivity = 1.0f;
        bool mouseInvertY = false;
        int keyboardRepeatDelay = 300;
        int keyboardRepeatRate = 50;
        float gamepadDeadzone = 0.1f;
        float gamepadSensitivity = 1.0f;
    };

    // Main input configuration structure
    struct InputConfiguration
    {
        InputSettings settings;
        std::vector<InputBinding> keyBindings;
        std::vector<InputBinding> mouseBindings;
        std::vector<InputBinding> gamepadBindings;
        std::vector<InputContext> contexts;
        std::string defaultContext = "Flight";

        // Helper methods
        std::vector<InputBinding> getBindingsForAction(const std::string &action) const;
        InputBinding *getBindingForKey(KeyCode key);
        InputBinding *getBindingForMouseButton(MouseButton button);
        InputBinding *getBindingForGamepadButton(GamepadButton button);
    };

    // Utility functions for string/enum conversion
    KeyCode stringToKeyCode(const std::string &str);
    MouseButton stringToMouseButton(const std::string &str);
    GamepadButton stringToGamepadButton(const std::string &str);
    GamepadAxis stringToGamepadAxis(const std::string &str);
    InputDevice stringToInputDevice(const std::string &str);

    std::string keyCodeToString(KeyCode key);
    std::string mouseButtonToString(MouseButton button);
    std::string gamepadButtonToString(GamepadButton button);
    std::string gamepadAxisToString(GamepadAxis axis);
    std::string inputDeviceToString(InputDevice device);
}

#endif
