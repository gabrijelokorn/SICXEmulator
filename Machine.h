#ifndef SICXE_MACHINE_H
#define SICXE_MACHINE_H

#include <iostream>
#include <cstdint>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Opcode.h"
#include "Registry.h"
#include "SicXeIO.h"

using namespace std;

class Machine {
   private:
    Memory mem;
    Registry reg;
    SicXeIO sio;
    Opcode oc;

    void notImplemented(string mnemonic);
    void invalidOpcode(int opcode);
    void invalidAddressing();

    bool execF1(uint8_t opcode);
    bool execF2(uint8_t opcode, uint8_t operand);
    bool execF3F4(uint8_t opcode, uint8_t ni, uint8_t operand);
   
    uint8_t fetch();
    void execute();

   public:
    Machine();
};

#endif