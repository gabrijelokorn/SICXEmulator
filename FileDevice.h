#ifndef SICXE_FIILEDEVICE_H
#define SICXE_FIILEDEVICE_H

#include <iostream>

#include "Device.h"

using namespace std;

class FileDevice : public Device {
   private:
    istream* input;
    ostream* output;
   public:
    uint8_t fileRead(fstream);
    void fileWrite(fstream);
    bool fileTest(fstream);
    FileDevice(int num);
};

#endif