#ifndef SICXE_INPUTDEVICE_H
#define SICXE_INPUTDEVICE_H

#include "Device.h"
#include <iostream>

class InputDevice : public Device {
   public:
    InputDevice(istream&);
};

#endif