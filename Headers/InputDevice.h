#ifndef SICXE_INPUTDEVICE_H
#define SICXE_INPUTDEVICE_H

#include "Device.h"
#include <iostream>

class InputDevice : public Device {
   private:
    std::istream input;
   public:
    InputDevice(std::istream&);
};

#endif