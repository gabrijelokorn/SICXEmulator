#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <fstream>

#include "FileDevice.h"

using namespace std;

void FileDevice::write(uint8_t val) {
    cout << "test";
}

uint8_t FileDevice::read () {
    return 0;
}

bool FileDevice::test () {
    return true;
}

FileDevice::FileDevice(int num) {

    stringstream fileNameHex;
    fileNameHex << std::hex << num;
    this->fileName = fileNameHex.str() + ".dev";
}

