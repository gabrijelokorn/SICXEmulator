#ifndef SICXE_MACHINE_H
#define SICXE_MACHINE_H

#include "Device.h"

using namespace std;

class Machine {
   public:
    void setDevice(int num, Device device);
    Machine();
};

#endif