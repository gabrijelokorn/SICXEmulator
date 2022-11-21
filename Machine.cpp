#include "Machine.h"

#include <iostream>
#include <string>
#include <fstream>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"
#include "SicXeIO.h"
#include "Opcode.h"

using namespace std;


Machine::Machine() {
    cout << "Machine works!\n";
    Registry reg;
    Memory mem;
    SicXeIO SicXeINOUT;
    Opcode opcode;
}