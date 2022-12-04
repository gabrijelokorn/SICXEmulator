#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <fstream>

#include "FileDevice.h"

using namespace std;

void FileDevice::write(uint8_t val) {
    ofile.open(this->fileName.c_str());
    ofile.seekp(this->position);
    // printf("val: %d\n", val);
    // printf("dn: %s\n", this->fileName.c_str());
    ofile << val;
    ofile.close();
    this->position++;
    cout << this->position << endl;
}

uint8_t FileDevice::read () {
    ifile.open(this->fileName);
    ifile.seekg(this->position);
    uint8_t character;
    character = ifile.get();
    ifile.close();
    this->position++;
    return character;
}

bool FileDevice::test () {
    return true;
}

FileDevice::FileDevice(int num) {

    stringstream fileNameHex;
    fileNameHex << std::hex << num;
    this->fileName = fileNameHex.str() + ".dev";
    this->position = 0;
}

