#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

#include "Machine.h"
#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"
#include "SicXeIO.h"
#include "Opcode.h"

using namespace std;

void Machine::notImplemented(string mnemonic) {
    printf("Warning: The mnemonic %s you used is not valid\n", mnemonic);
}

void Machine::invalidOpcode(int opcode) {
    printf("Warning: The opcode %d you used is not valid\n", opcode);
}

void Machine::invalidAddressing() {
    printf("Warning: Addressing is not valid");
}

bool Machine::execF1(uint8_t command_byte_1) {
    switch (command_byte_1) {
        case FLOAT :
            break;
        case FIX :
            break;
        case NORM :
            break;
        case SIO :
            break;
        case HIO :
            break;
        case TIO :
            break;
        default: return false;
    }
    return true;
}

bool Machine::execF2(uint8_t command_byte_1, uint8_t operand) {

    uint8_t operand_one = (operand & 0b11110000) >> 4;
    uint8_t operand_two = (operand & 0b00001111) >> 00;

    int operand_one_value = reg.getReg(operand_one);
    int operand_two_value = reg.getReg(operand_two);

    switch (command_byte_1) {
        case SUBR:
            reg.setReg(operand_two, operand_two_value - operand_one_value);
            break;
        case MULR:
            reg.setReg(operand_two, operand_two_value * operand_one_value);
            break;
        case DIVR:
            reg.setReg(operand_two, operand_two_value / operand_one_value);
            break;
        case COMPR:
            break;
        case SHIFTL:
            break;
        case SHIFTR:
            break;
        case RMO:
            reg.setReg(operand_two, operand_one_value);
            break;
        case SVC:
            break;
        case CLEAR:
            reg.setReg(operand_one, 0);
            break;
        case TIXR:
            break;
    }
    return true;
}
bool Machine::execF3F4(uint8_t command_byte_1, uint8_t ni, uint8_t operand) {

    return true;
}

uint8_t Machine::fetch() {
    int fetchInstruction = this->mem.getByte(this->reg.getPC());
    this->reg.incrementPC();
    return fetchInstruction;
}

void Machine::execute() {
    
    uint8_t command_byte_1 = fetch();
    uint8_t ni = command_byte_1 & 0b00000011;
    command_byte_1 &= ~(3);

    if (execF1(command_byte_1)) return;

    uint8_t command_byte_2 = fetch();
    if (execF2(command_byte_1, command_byte_2)) return;

    uint8_t command_byte_3 = fetch();

}


Machine::Machine() {
    cout << "Machine works!\n";
    reg.printRegisters();

    reg.setA(7);
    reg.setS(-3);
    reg.printRegisters();

    mem.setByte(0, 0x94);
    mem.setByte(1, 0b00000100);

    execute();

    reg.printRegisters();
}