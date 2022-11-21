#include <iostream>
#include <string>
#include <cstdint>

#include "InputDevice.h"

using namespace std;

uint8_t InputDevice::read () {
    uint8_t character;
    cin >> character;
    return character;
}

InputDevice::InputDevice(istream &input) {
    this->input = &input;
}