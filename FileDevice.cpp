#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "FileDevice.h"

using namespace std;

void FileDevice::fileWrite(fstream fileName) {

}

uint8_t FileDevice::fileRead (fstream fileName) {

}

bool FileDevice::fileTest (fstream fileName) {

}

FileDevice::FileDevice(int num) {

    stringstream fileName;
    fileName << std::hex << num;

    fstream fileName;

}

