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
    
    mem.setWord(32, 505050);
    mem.setWord(17, -505050);
    mem.print(4, 50);

    InputDevice id(std::cin);

    // devices[0] = InputDevice(id);
}