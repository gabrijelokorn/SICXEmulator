#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>

#include "FileDevice.h"

using namespace std;

void FileDevice::write(uint8_t val) {
    ofile.open(this->fileName.c_str());
    if (!ofile) ofile.open(this->fileName.c_str(), fstream::app);
    ofile.seekp(this->position);
    ofile << val;
    ofile.close();
    this->position++;
}

int FileDevice::read () {
    ifile.open(this->fileName);
    if (!ifile) ifile.open(this->fileName.c_str(), ifstream::app);
    ifile.seekg(this->position);
    int character = ifile.get();
    ifile.close();
    this->position++;
    return character != -1 ? character : 0;
}

bool FileDevice::test () {
    return true;
}

FileDevice::FileDevice(int num) {

    stringstream fileNameHex;
    if (num < 16) {
        this->fileName = "0";
    }
    fileNameHex << std::hex << num;
    this->fileName = this->fileName + fileNameHex.str();
    // this->fileName << uppercase;
    for (int i = 0; i < fileName.length(); i++) {
        this->fileName[i] = toupper(this->fileName.c_str()[i]);
    }
    this->fileName += ".dev";
    this->position = 0;
}

