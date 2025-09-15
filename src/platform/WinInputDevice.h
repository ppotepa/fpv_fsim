#ifndef WININPUTDEVICE_H
#define WININPUTDEVICE_H

#include "IInputDevice.h"

class WinInputDevice : public IInputDevice {
public:
    void poll() override;
};

#endif
