#ifndef SICXE_INPUTDEVICE_H
#define SICXE_INPUTDEVICE_H

#include "Device.h"
#include <iostream>

using namespace std;

class InputDevice : public Device {
   private:
    istream *input;
   public:
    InputDevice(istream& a);
};

#endif