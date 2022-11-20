#include <iostream>

#include "Device.h"
#include "InputDevice.h"
#include "OutputDevice.h"
#include "SicXeIO.h"
#include "FileDevice.h"

using namespace std;

void SicXeIO::setDevice(int num, Device device) {

    this->devices[num] = device;
}

Device SicXeIO::getDevice (int num) {
    return devices[num];
}

SicXeIO::SicXeIO() {
    printf("SicXeIO works\n");

    setDevice(STANDARD_INPUT_DEVICE, InputDevice(cin));
    setDevice(STANDARD_OUTPUT_DEVICE, OutputDevice(cout));
    setDevice(STANDARD_ERROR_DEVICE, OutputDevice(cerr));

    for (int device_index = 3; device_index <= 255; device_index++) {
        setDevice(device_index, FileDevice(device_index));
    }

}