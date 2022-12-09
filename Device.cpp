#include <iostream>
#include <cstdint>

#include "InputDevice.h"
#include "Device.h"
using namespace std;

int Device::read() {
    return 1;
}
void Device::write(uint8_t val) {
}
bool Device::test() {
    return true;
}