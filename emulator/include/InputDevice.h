#ifndef SICXE_INPUTDEVICE_H
#define SICXE_INPUTDEVICE_H

#include <iostream>
#include <cstdint>

#include "Device.h"

using namespace std;

class InputDevice : public Device {
   private:
    istream* input;
   public:
    int read() override;
    InputDevice(istream& input);
};

#endif