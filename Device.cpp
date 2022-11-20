#include <iostream>
#include <cstdint>

#include "InputDevice.h"
#include "Device.h"
using namespace std;

uint8_t Device::read() {
    return 0;
}
void Device::write() {

}
bool Device::test() {
    return true;
}



Device::Device() { 
    // cout << "Device works!\n";
}