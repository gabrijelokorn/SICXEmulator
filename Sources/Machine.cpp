#include "Machine.h"

#include <iostream>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"

#define MAX_DEVICES 256

using namespace std;

void Machine::setDevice (int num, Device device) {
    
}

Machine::Machine() {
    cout << "Machine works!\n";
    Registry reg;
    Memory mem;
    Device devices[MAX_DEVICES];


    setDevice(0, InputDevice(std::cin));

}