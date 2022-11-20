#include <iostream>

#include "OutputDevice.h"

using namespace std;

OutputDevice::OutputDevice(ostream& output) {

    this->output = &output;
}