/**
 * @file IInputDevice.h
 * @brief Interface for platform-specific input device handling.
 *
 * This interface defines the contract for input device implementations
 * that handle user input from various sources (keyboard, mouse, gamepads, etc.).
 * Different platforms can provide their own implementations while maintaining
 * a consistent interface for the rest of the application.
 */

#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H

/**
 * @class IInputDevice
 * @brief Abstract interface for handling user input devices.
 *
 * This interface provides a platform-independent way to access user input.
 * Implementations handle polling input devices and providing input state
 * to the application. The interface is designed to be extensible for
 * different types of input devices and platforms.
 */
class IInputDevice
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IInputDevice() = default;

    /**
     * @brief Poll the input devices for new input events.
     *
     * This method should be called regularly to update the internal
     * input state. It handles platform-specific input processing and
     * updates the state of all connected input devices.
     */
    virtual void poll() = 0;

    // TODO: Add methods for querying specific input states
    // virtual bool isKeyPressed(KeyCode key) const = 0;
    // virtual bool isMouseButtonPressed(MouseButton button) const = 0;
    // virtual void getMousePosition(int& x, int& y) const = 0;
};

#endif

