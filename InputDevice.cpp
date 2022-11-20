#include <iostream>
#include <string>

#include "InputDevice.h"

using namespace std;

InputDevice::InputDevice(istream& input) {

    this->input = &input;
}

