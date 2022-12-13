#include <iostream>

#include "OutputDevice.h"

using namespace std;

void OutputDevice::write(uint8_t val) {
    cout << val;
}

OutputDevice::OutputDevice(ostream &output) {

    this->output = &output;
}