#include <iostream>

#include "Device.h"
#include "InputDevice.h"
#include "OutputDevice.h"
#include "SicXeIO.h"
#include "FileDevice.h"

using namespace std;

void SicXeIO::setDevice(int num, Device* device) {
    this->devices[num] = device;
}

Device* SicXeIO::getDevice (int num) {
    return devices[num];
}

SicXeIO::SicXeIO() {
    setDevice(STANDARD_INPUT_DEVICE, new InputDevice(cin));
    setDevice(STANDARD_OUTPUT_DEVICE, new OutputDevice(cout));
    setDevice(STANDARD_ERROR_DEVICE, new OutputDevice(cerr));

    for (int device_index = 3; device_index <= 255; device_index++) {
        setDevice(device_index, new FileDevice(device_index));
    }


}