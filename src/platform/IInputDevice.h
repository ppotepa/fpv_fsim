#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H

class IInputDevice
{
public:
    virtual ~IInputDevice() = default;
    virtual void poll() = 0;
    // Add methods for input
};

#endif
