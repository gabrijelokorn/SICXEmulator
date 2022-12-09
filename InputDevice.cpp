#include <iostream>
#include <string>
#include <cstdint>

#include "InputDevice.h"

using namespace std;

int InputDevice::read () {
    uint8_t character;
    cin >> character;
    return character;
}

InputDevice::InputDevice(istream &input) {
    this->input = &input;
}