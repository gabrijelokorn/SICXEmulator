#include "Machine.h"

#include <iostream>
#include <sstream>
#include <string>

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

    devices[0] = InputDevice(std::cin);
}