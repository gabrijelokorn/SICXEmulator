#include <iostream>
#include <string>
#include <cstdint>

#include "InputDevice.h"

using namespace std;

uint8_t InputDevice::read () {
    return 16;
}

InputDevice::InputDevice(istream& input) {
    this->input = &input;
}