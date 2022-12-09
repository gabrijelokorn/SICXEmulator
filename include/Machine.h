#ifndef SICXE_MACHINE_H
#define SICXE_MACHINE_H

#include <iostream>
#include <fstream>
#include <cstdint>

#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Opcode.h"
#include "Registry.h"
#include "SicXeIO.h"

#define FORMAT3_NEGATIVE_OFFSET -4096
#define FORMAT4_NEGATIVE_OFFSET -1048576

#define DEFAULT_CLOCK_FREQ 100

using namespace std;

class Machine {
   private:
    Memory mem;
    Registry reg;
    SicXeIO sio;
    Opcode oc;

    ifstream file;
    string programName;
    uint32_t programStart;
    uint32_t programLength;

    bool run;
    int speed;

    uint32_t instruction_counter;

    void notImplemented(string mnemonic);
    void invalidOpcode(int opcode);
    void invalidAddressing();

    bool execF1(uint8_t opcode);
    bool execF2(uint8_t opcode, uint8_t operand);
    bool execF3F4(uint8_t opcode, uint8_t ni, uint8_t command_byte_2, uint8_t command_byte_3);

    int takeWord(bool immediate, bool indirect, bool simple, int offset, int address);
    int takeByte(bool immediate, bool indirect, bool simple, int offset, int address);
    void storeWord(bool immediate, bool indirect, bool simple, int offset, int address, int val);
    void storeByte(bool immediate, bool indirect, bool simple, int offset, int address, int val);
   
    uint8_t fetch();
    void execute();

    void lineDecoder(string line);


   public:
    void step();
    void start();
    void stop();

    void setSpeed(int val);    
    int getSpeed();

    void loadProgram(string fileName);
    Machine();
};

#endif