#ifndef SICXE_OUTPUTDEVICE_H
#define SICXE_OUTPUTDEVICE_H

#include <iostream>

#include "Device.h"

using namespace std;

class OutputDevice : public Device {
   private:
    ostream* output;

   public:
    void write(uint8_t val) override;
    OutputDevice(ostream& output);
};

#endif