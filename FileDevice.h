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
    string redingFile;
    fstream ofile;
    ifstream ifile;
    uint32_t position;
    void initializeFile();
    void copyFile();

   public:
    void write(uint8_t val) override;
    uint8_t read() override;
    bool test() override;
    FileDevice(int fileName);
};

#endif