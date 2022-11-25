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
    printf("Warning: The mnemonic %s you used is not valid\n", mnemonic.c_str());
}

void Machine::invalidOpcode(int opcode) {
    printf("Warning: The opcode %d you used is not valid\n", opcode);
}

void Machine::invalidAddressing() {
    printf("Warning: Addressing is not valid");
}

bool Machine::execF1(uint8_t command_opcode) {
    switch (command_opcode) {
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

bool Machine::execF2(uint8_t command_opcode, uint8_t operand) {

    uint8_t operand_one = (operand & 0b11110000) >> 4;
    uint8_t operand_two = (operand & 0b00001111) >> 00;

    int operand_one_value = reg.getReg(operand_one);
    int operand_two_value = reg.getReg(operand_two);

    switch (command_opcode) {
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
            if (operand_one_value > operand_two_value) reg.setSW(reg.getSW() | 0x03);
            else if (operand_one_value < operand_two_value) reg.setSW(reg.getSW() | 0x02);
            else if (operand_one_value == operand_two_value) reg.setSW(reg.getSW() | 0x01);
            else reg.setSW(0x00);
            break;
        case SHIFTL:
            reg.setReg(operand_one, operand_one << operand_two_value);
            break;
        case SHIFTR:
            reg.setReg(operand_one, operand_one >> operand_two_value);
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
        default: return false;
    }
    return true;
}
bool Machine::execF3F4(uint8_t command_opcode, uint8_t ni, int offset) {

    // bool b_bit = 0x40000000 & offset;
    // bool p_bit = 0x20000000 & offset;
    // bool x_bit = 0x80000000 & offset;

    // uint32_t finalAdress = offset;
    // if (x_bit) finalAdress += reg.getX();
    // if (b_bit) finalAdress += reg.getB();
    // if (p_bit) finalAdress += reg.getPC();

    // int finalValue = finalAdress;
    // if (ni == 1) finalValue = finalValue;
    // else if (ni == 2) finalValue = mem.getWord(mem.getWord(finalValue));
    // else if (ni == 3) finalValue = mem.getWord(finalValue);
    // else printf("\"ni\"value is incorrect! ni = %d\n", ni);
    // uint8_t finalValue_lastByte = finalValue >> 24;

    switch (command_opcode) {
        // load and store
        case LDA:

            break;
        case LDX:

            break;
        case LDL:

            break;
        case STA:
            cout << "checkpoint\n";
            break;
        case STX:

            break;
        case STL:

            break;
        
        // fixed point arithmetic
        case ADD:

            break;
        case SUB:

            break;
        case MUL:

            break;
        case DIV:

            break;
        case COMP:

            break;
        case TIX:

            break;

        // jumps
        case JEQ:

            break;
        case JGT:

            break;
        case JLT:

            break;
        case J:

            break;

        // bit manipulation
        case AND:

            break;
        case OR:

            break;

        // jump to subroutine
        case JSUB:

            break;
        case RSUB:

            break;

        // load and store int
        case LDCH:

            break;
        case STCH:

            break;
        
        // floating point arithmetic
        case ADDF:

            break;
        case SUBF:

            break;
        case MULF:

            break;
        case DIVF:

            break;
        case COMPF:

            break;

        // load and store
        case LDB:

            break;
        case LDS:

            break;
        case LDF:

            break;
        case LDT:

            break;
        case STB:

            break;
        case STS:

            break;
        case STF:

            break;
        case STT:

            break;
        
        // special load and store
        case LPS:

            break;
        case STI:

            break;
        case STSW:

            break;

        // devices
        case RD:

            break;
        case WD:

            break;
        case TD:

            break;

        // system
        case SSK:

            break;

        default: return false;
    }
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
    uint8_t command_opcode = command_byte_1 & ~(3);

    if (execF1(command_opcode)) return;

    uint8_t command_byte_2 = fetch();
    if (execF2(command_opcode, command_byte_2)) return;

    uint8_t command_byte_3 = fetch();
    uint8_t extended_command = command_byte_2 & 0b00010000;
    int offset = extended_command;
    if (extended_command) {
        offset = (offset << 8) | fetch();
    }
    if (execF3F4(command_opcode, ni, offset)) return;
    else invalidOpcode(command_opcode);
}


Machine::Machine() {
    cout << "Machine works!\n";

    mem.setByte(0, 0x0F);
    mem.setByte(1, 0x90);
    mem.setByte(2, 0xA0);
    mem.setByte(3, 0x00);

    execute();
    reg.printRegisters();
}