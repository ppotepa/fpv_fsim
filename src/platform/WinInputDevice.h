/**
 * @file WinInputDevice.h
 * @brief Windows-specific implementation of the input device interface.
 *
 * This file implements the IInputDevice interface for Windows platforms,
 * providing input handling through the Windows API. It manages keyboard,
 * mouse, and other input devices available on Windows systems.
 */

#ifndef WININPUTDEVICE_H
#define WININPUTDEVICE_H

#include "IInputDevice.h"

/**
 * @class WinInputDevice
 * @brief Windows platform implementation of input device handling.
 *
 * This class provides Windows-specific input device management using
 * the Win32 API. It handles polling Windows messages, keyboard state,
 * mouse input, and other Windows-specific input sources.
 */
class WinInputDevice : public IInputDevice
{
public:
    /**
     * @brief Poll Windows input devices for new input events.
     *
     * Processes Windows messages and updates the internal input state.
     * This method should be called regularly in the application's main loop
     * to ensure responsive input handling.
     */
    void poll() override;
};

#endif

