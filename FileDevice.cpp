#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <fstream>

#include "FileDevice.h"

using namespace std;

void FileDevice::write(uint8_t val) {
    file.open(this->fileName);
    file.seekp(this->position);
    file << val;
    file.close();
    this->position++;
}

uint8_t FileDevice::read () {
    file.open(this->fileName);
    file.seekp(this->position);
    uint8_t character;
    character = file.get();
    file.close();
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

