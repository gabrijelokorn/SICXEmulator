#include <iostream>

#include "Device.h"
#include "InputDevice.h"
#include "OutputDevice.h"
#include "SicXeIO.h"
#include "FileDevice.h"

using namespace std;

void SicXeIO::setDevice(int num, Device* device) {

    this->devices[num] = device;
    printf("%d\n", (*devices)[0].read());
}

Device SicXeIO::getDevice (int num) {
    printf("%d\n", (*devices)[0].read());
    return (*devices)[num];
}

SicXeIO::SicXeIO() {
    printf("SicXeIO works\n");

    InputDevice* input = new InputDevice(cin);
    OutputDevice output = OutputDevice(cout);
    OutputDevice error = OutputDevice(cerr);

    setDevice(STANDARD_INPUT_DEVICE, input);
    // setDevice(STANDARD_OUTPUT_DEVICE, output);
    // setDevice(STANDARD_ERROR_DEVICE, error);

    // for (int device_index = 3; device_index <= 255; device_index++) {
    //     setDevice(device_index, FileDevice(device_index));
    // }
    printf("%d\n", getDevice(0).read());
}