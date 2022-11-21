#include "Machine.h"

#include <iostream>
#include <string>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"
#include "SicXeIO.h"

using namespace std;


Machine::Machine() {
    cout << "Machine works!\n";
    Registry reg;
    Memory mem;
    SicXeIO SicXeINOUT;
}