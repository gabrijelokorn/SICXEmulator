#ifndef SICXE_FIILEDEVICE_H
#define SICXE_FIILEDEVICE_H

#include <iostream>
#include <string>
#include <fstream>

#include "Device.h"

using namespace std;

class FileDevice : public Device {
   private:
    string fileName;
    fstream ofile;
    ifstream ifile;
    uint32_t position;

   public:
    void write(uint8_t val) override;
    int read() override;
    bool test() override;
    FileDevice(int fileName);
};

#endif