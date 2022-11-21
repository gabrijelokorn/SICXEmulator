#ifndef SICXE_FIILEDEVICE_H
#define SICXE_FIILEDEVICE_H

#include <iostream>
#include <string>

#include "Device.h"

using namespace std;

class FileDevice : public Device {
   private:
    string fileName;
   public:
    void write(uint8_t val);
    uint8_t read();
    bool test();
    FileDevice(int fileName);
};

#endif