#ifndef SICXE_INPUTDEVICE_H
#define SICXE_INPUTDEVICE_H

#include <iostream>

#include "Device.h"

using namespace std;

class InputDevice : public Device {
   private:
    istream* input;
   public:
    InputDevice(istream& input);
};

#endif