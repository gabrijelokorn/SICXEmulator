#include "Machine.h"

#include <iostream>
#include <string>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"
#include "SicXeIO.h"

#define MAX_DEVICES 256

using namespace std;


Machine::Machine() {
    cout << "Machine works!\n";
    Registry reg;
    Memory mem;
    SicXeIO SicXeINOUT;
}