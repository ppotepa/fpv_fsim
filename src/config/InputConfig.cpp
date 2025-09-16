#include "InputConfig.h"
#include <algorithm>
#include <unordered_map>

namespace Input
{

    // Helper methods for InputConfiguration
    std::vector<InputBinding> InputConfiguration::getBindingsForAction(const std::string &action) const
    {
        std::vector<InputBinding> result;

        // Check key bindings
        for (const auto &binding : keyBindings)
        {
            if (binding.action == action)
            {
                result.push_back(binding);
            }
        }

        // Check mouse bindings
        for (const auto &binding : mouseBindings)
        {
            if (binding.action == action)
            {
                result.push_back(binding);
            }
        }

        // Check gamepad bindings
        for (const auto &binding : gamepadBindings)
        {
            if (binding.action == action)
            {
                result.push_back(binding);
            }
        }

        return result;
    }

    InputBinding *InputConfiguration::getBindingForKey(KeyCode key)
    {
        for (auto &binding : keyBindings)
        {
            if (binding.keyCode == key)
            {
                return &binding;
            }
        }
        return nullptr;
    }

    InputBinding *InputConfiguration::getBindingForMouseButton(MouseButton button)
    {
        for (auto &binding : mouseBindings)
        {
            if (binding.mouseButton == button)
            {
                return &binding;
            }
        }
        return nullptr;
    }

    InputBinding *InputConfiguration::getBindingForGamepadButton(GamepadButton button)
    {
        for (auto &binding : gamepadBindings)
        {
            if (binding.gamepadButton == button)
            {
                return &binding;
            }
        }
        return nullptr;
    }

    // String to enum conversion functions
    KeyCode stringToKeyCode(const std::string &str)
    {
        static const std::unordered_map<std::string, KeyCode> keyMap = {
            // Letters
            {"A", KeyCode::A},
            {"B", KeyCode::B},
            {"C", KeyCode::C},
            {"D", KeyCode::D},
            {"E", KeyCode::E},
            {"F", KeyCode::F},
            {"G", KeyCode::G},
            {"H", KeyCode::H},
            {"I", KeyCode::I},
            {"J", KeyCode::J},
            {"K", KeyCode::K},
            {"L", KeyCode::L},
            {"M", KeyCode::M},
            {"N", KeyCode::N},
            {"O", KeyCode::O},
            {"P", KeyCode::P},
            {"Q", KeyCode::Q},
            {"R", KeyCode::R},
            {"S", KeyCode::S},
            {"T", KeyCode::T},
            {"U", KeyCode::U},
            {"V", KeyCode::V},
            {"W", KeyCode::W},
            {"X", KeyCode::X},
            {"Y", KeyCode::Y},
            {"Z", KeyCode::Z},

            // Numbers
            {"0", KeyCode::Num0},
            {"1", KeyCode::Num1},
            {"2", KeyCode::Num2},
            {"3", KeyCode::Num3},
            {"4", KeyCode::Num4},
            {"5", KeyCode::Num5},
            {"6", KeyCode::Num6},
            {"7", KeyCode::Num7},
            {"8", KeyCode::Num8},
            {"9", KeyCode::Num9},

            // Function keys
            {"F1", KeyCode::F1},
            {"F2", KeyCode::F2},
            {"F3", KeyCode::F3},
            {"F4", KeyCode::F4},
            {"F5", KeyCode::F5},
            {"F6", KeyCode::F6},
            {"F7", KeyCode::F7},
            {"F8", KeyCode::F8},
            {"F9", KeyCode::F9},
            {"F10", KeyCode::F10},
            {"F11", KeyCode::F11},
            {"F12", KeyCode::F12},

            // Arrow keys
            {"LEFT", KeyCode::LEFT},
            {"UP", KeyCode::UP},
            {"RIGHT", KeyCode::RIGHT},
            {"DOWN", KeyCode::DOWN},

            // Special keys
            {"SPACE", KeyCode::SPACE},
            {"ENTER", KeyCode::ENTER},
            {"ESCAPE", KeyCode::ESCAPE},
            {"TAB", KeyCode::TAB},
            {"BACKSPACE", KeyCode::BACKSPACE},
            {"DELETE", KeyCode::KEY_DELETE},
            {"INSERT", KeyCode::INSERT},
            {"HOME", KeyCode::HOME},
            {"END", KeyCode::END},
            {"PAGE_UP", KeyCode::PAGE_UP},
            {"PAGE_DOWN", KeyCode::PAGE_DOWN},

            // Modifier keys
            {"LSHIFT", KeyCode::LSHIFT},
            {"RSHIFT", KeyCode::RSHIFT},
            {"LCTRL", KeyCode::LCTRL},
            {"RCTRL", KeyCode::RCTRL},
            {"LALT", KeyCode::LALT},
            {"RALT", KeyCode::RALT},

            // Special characters
            {"TILDE", KeyCode::TILDE},
            {"MINUS", KeyCode::MINUS},
            {"EQUALS", KeyCode::EQUALS},
            {"LBRACKET", KeyCode::LBRACKET},
            {"RBRACKET", KeyCode::RBRACKET},
            {"BACKSLASH", KeyCode::BACKSLASH},
            {"SEMICOLON", KeyCode::SEMICOLON},
            {"QUOTE", KeyCode::QUOTE},
            {"COMMA", KeyCode::COMMA},
            {"PERIOD", KeyCode::PERIOD},
            {"SLASH", KeyCode::SLASH}};

        auto it = keyMap.find(str);
        return (it != keyMap.end()) ? it->second : KeyCode::Unknown;
    }

    MouseButton stringToMouseButton(const std::string &str)
    {
        static const std::unordered_map<std::string, MouseButton> mouseMap = {
            {"LEFT", MouseButton::LEFT},
            {"RIGHT", MouseButton::RIGHT},
            {"MIDDLE", MouseButton::MIDDLE},
            {"X1", MouseButton::X1},
            {"X2", MouseButton::X2}};

        auto it = mouseMap.find(str);
        return (it != mouseMap.end()) ? it->second : MouseButton::Unknown;
    }

    GamepadButton stringToGamepadButton(const std::string &str)
    {
        static const std::unordered_map<std::string, GamepadButton> gamepadMap = {
            {"A", GamepadButton::A},
            {"B", GamepadButton::B},
            {"X", GamepadButton::X},
            {"Y", GamepadButton::Y},
            {"LEFT_SHOULDER", GamepadButton::LEFT_SHOULDER},
            {"RIGHT_SHOULDER", GamepadButton::RIGHT_SHOULDER},
            {"SELECT", GamepadButton::SELECT},
            {"START", GamepadButton::START},
            {"LEFT_STICK", GamepadButton::LEFT_STICK},
            {"RIGHT_STICK", GamepadButton::RIGHT_STICK},
            {"DPAD_UP", GamepadButton::DPAD_UP},
            {"DPAD_DOWN", GamepadButton::DPAD_DOWN},
            {"DPAD_LEFT", GamepadButton::DPAD_LEFT},
            {"DPAD_RIGHT", GamepadButton::DPAD_RIGHT}};

        auto it = gamepadMap.find(str);
        return (it != gamepadMap.end()) ? it->second : GamepadButton::Unknown;
    }

    GamepadAxis stringToGamepadAxis(const std::string &str)
    {
        static const std::unordered_map<std::string, GamepadAxis> axisMap = {
            {"LEFT_STICK_X", GamepadAxis::LEFT_STICK_X},
            {"LEFT_STICK_Y", GamepadAxis::LEFT_STICK_Y},
            {"RIGHT_STICK_X", GamepadAxis::RIGHT_STICK_X},
            {"RIGHT_STICK_Y", GamepadAxis::RIGHT_STICK_Y},
            {"LEFT_TRIGGER", GamepadAxis::LEFT_TRIGGER},
            {"RIGHT_TRIGGER", GamepadAxis::RIGHT_TRIGGER}};

        auto it = axisMap.find(str);
        return (it != axisMap.end()) ? it->second : GamepadAxis::Unknown;
    }

    InputDevice stringToInputDevice(const std::string &str)
    {
        static const std::unordered_map<std::string, InputDevice> deviceMap = {
            {"Keyboard", InputDevice::Keyboard},
            {"Mouse", InputDevice::Mouse},
            {"Gamepad", InputDevice::Gamepad}};

        auto it = deviceMap.find(str);
        return (it != deviceMap.end()) ? it->second : InputDevice::Unknown;
    }

    // Enum to string conversion functions
    std::string keyCodeToString(KeyCode key)
    {
        switch (key)
        {
        case KeyCode::A:
            return "A";
        case KeyCode::B:
            return "B";
        case KeyCode::C:
            return "C";
        case KeyCode::D:
            return "D";
        case KeyCode::E:
            return "E";
        case KeyCode::F:
            return "F";
        case KeyCode::G:
            return "G";
        case KeyCode::H:
            return "H";
        case KeyCode::I:
            return "I";
        case KeyCode::J:
            return "J";
        case KeyCode::K:
            return "K";
        case KeyCode::L:
            return "L";
        case KeyCode::M:
            return "M";
        case KeyCode::N:
            return "N";
        case KeyCode::O:
            return "O";
        case KeyCode::P:
            return "P";
        case KeyCode::Q:
            return "Q";
        case KeyCode::R:
            return "R";
        case KeyCode::S:
            return "S";
        case KeyCode::T:
            return "T";
        case KeyCode::U:
            return "U";
        case KeyCode::V:
            return "V";
        case KeyCode::W:
            return "W";
        case KeyCode::X:
            return "X";
        case KeyCode::Y:
            return "Y";
        case KeyCode::Z:
            return "Z";
        case KeyCode::F1:
            return "F1";
        case KeyCode::F2:
            return "F2";
        case KeyCode::F3:
            return "F3";
        case KeyCode::F4:
            return "F4";
        case KeyCode::F5:
            return "F5";
        case KeyCode::F6:
            return "F6";
        case KeyCode::F7:
            return "F7";
        case KeyCode::F8:
            return "F8";
        case KeyCode::F9:
            return "F9";
        case KeyCode::F10:
            return "F10";
        case KeyCode::F11:
            return "F11";
        case KeyCode::F12:
            return "F12";
        case KeyCode::LEFT:
            return "LEFT";
        case KeyCode::UP:
            return "UP";
        case KeyCode::RIGHT:
            return "RIGHT";
        case KeyCode::DOWN:
            return "DOWN";
        case KeyCode::SPACE:
            return "SPACE";
        case KeyCode::ENTER:
            return "ENTER";
        case KeyCode::ESCAPE:
            return "ESCAPE";
        case KeyCode::TILDE:
            return "TILDE";
        case KeyCode::LSHIFT:
            return "LSHIFT";
        case KeyCode::RSHIFT:
            return "RSHIFT";
        default:
            return "Unknown";
        }
    }

    std::string mouseButtonToString(MouseButton button)
    {
        switch (button)
        {
        case MouseButton::LEFT:
            return "LEFT";
        case MouseButton::RIGHT:
            return "RIGHT";
        case MouseButton::MIDDLE:
            return "MIDDLE";
        case MouseButton::X1:
            return "X1";
        case MouseButton::X2:
            return "X2";
        default:
            return "Unknown";
        }
    }

    std::string gamepadButtonToString(GamepadButton button)
    {
        switch (button)
        {
        case GamepadButton::A:
            return "A";
        case GamepadButton::B:
            return "B";
        case GamepadButton::X:
            return "X";
        case GamepadButton::Y:
            return "Y";
        case GamepadButton::SELECT:
            return "SELECT";
        case GamepadButton::START:
            return "START";
        default:
            return "Unknown";
        }
    }

    std::string gamepadAxisToString(GamepadAxis axis)
    {
        switch (axis)
        {
        case GamepadAxis::LEFT_STICK_X:
            return "LEFT_STICK_X";
        case GamepadAxis::LEFT_STICK_Y:
            return "LEFT_STICK_Y";
        case GamepadAxis::RIGHT_STICK_X:
            return "RIGHT_STICK_X";
        case GamepadAxis::RIGHT_STICK_Y:
            return "RIGHT_STICK_Y";
        case GamepadAxis::LEFT_TRIGGER:
            return "LEFT_TRIGGER";
        case GamepadAxis::RIGHT_TRIGGER:
            return "RIGHT_TRIGGER";
        default:
            return "Unknown";
        }
    }

    std::string inputDeviceToString(InputDevice device)
    {
        switch (device)
        {
        case InputDevice::Keyboard:
            return "Keyboard";
        case InputDevice::Mouse:
            return "Mouse";
        case InputDevice::Gamepad:
            return "Gamepad";
        default:
            return "Unknown";
        }
    }
}
