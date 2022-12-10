#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <vector>

#include "Machine.h"
#include "Device.h"
#include "InputDevice.h"
#include "Memory.h"
#include "Registry.h"
#include "SicXeIO.h"
#include "Opcode.h"

using namespace std;

void Machine::notImplemented(string mnemonic)
{
    printf("Warning: The mnemonic %s you used is not implemented\n", mnemonic.c_str());
}

void Machine::invalidOpcode(int opcode)
{
    printf("Warning: The opcode 0x%02x you used is not valid\n", opcode);
}

void Machine::invalidAddressing()
{
    printf("Warning: Addressing is not valid\n");
}

void Machine::stackOverflowWarning() {
    printf("STACK OVERFLOW!\n");
}

void Machine::incrementSMP()
{
    if (reg.getSMP() < MIN_STACK_ADDRESS) {
        stackOverflowWarning();
    }
    reg.setSMP(reg.getSMP() - 3);
}

void Machine::decreaseSMP()
{
    reg.setSMP(reg.getSMP() + 3);
}

void Machine::upadate_SBP() {
    reg.setSBP(reg.getSMP());
}

int Machine::get_previous_SBP() {
    return mem.getWord(reg.getSBP() + 3);
}

void Machine::resetSBP() {
    reg.setSBP(get_previous_SBP());
}

void Machine::push_stack(int val) {
    mem.setWord(reg.getSMP(), val);
    incrementSMP();
}

int Machine::pop_stack() {
    decreaseSMP();
    return mem.getWord(reg.getSMP());
}

void Machine::POPL() {
    reg.setA(mem.getWord(reg.getSBP() - 0 * 3));
    reg.setX(mem.getWord(reg.getSBP() - 1 * 3));
    reg.setL(mem.getWord(reg.getSBP() - 2 * 3));
    reg.setB(mem.getWord(reg.getSBP() - 3 * 3));
    reg.setS(mem.getWord(reg.getSBP() - 4 * 3));
    reg.setT(mem.getWord(reg.getSBP() - 5 * 3));
    reg.setSW(mem.getWord(reg.getSBP() - 6 * 3));
    resetSBP();
}
void Machine::POPC() {
    reg.setPC(mem.getWord(reg.getSBP() + 6));
}
void Machine::POPA(int reg1, int reg2) {
    reg.setReg(reg1, mem.getWord(reg.getSBP() - 9));
    reg.setReg(reg2, mem.getWord(reg.getSBP() - 12));
}

void Machine::push_locals() {
    push_stack(reg.getA());
    push_stack(reg.getX());
    push_stack(reg.getL());
    push_stack(reg.getB());
    push_stack(reg.getS());
    push_stack(reg.getT());
    push_stack(reg.getSW());
}

void Machine::PUSHSMP() {
    push_stack(reg.getSBP());
    upadate_SBP();
}

void Machine::PUSHPC() {
    push_stack(reg.getPC());
}
void Machine::PUSHL() {
    PUSHPC();
    PUSHSMP();
    push_locals();
}
void Machine::PUSHA(int reg1, int reg2) {
    push_stack(reg.getReg(reg2));
    push_stack(reg.getReg(reg1));
}

uint8_t Machine::fetch()
{
    int fetchInstruction = this->mem.getByte(this->reg.getPC());
    this->reg.incrementPC();
    return fetchInstruction;
}

bool Machine::execF1(uint8_t command_opcode)
{
    switch (command_opcode)
    {
    case FLOAT:
        notImplemented("FLOAT");
        break;
    case FIX:
        notImplemented("FIX");
        break;
    case NORM:
        notImplemented("NORM");
        break;
    case SIO:
        notImplemented("SIO");
        break;
    case HIO:
        notImplemented("HIO");
        break;
    case TIO:
        notImplemented("TIO");
        break;
    default:
        return false;
    }
    return true;
}

bool Machine::execF2(uint8_t command_opcode, uint8_t operand)
{

    uint8_t operand_one = (operand & 0b11110000) >> 4;
    uint8_t operand_two = (operand & 0b00001111) >> 00;

    int operand_one_value = reg.getReg(operand_one);
    int operand_two_value = reg.getReg(operand_two);

    switch (command_opcode)
    {
    case ADDR:
        reg.setReg(operand_two, operand_two_value + operand_one_value);
        break;
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
        if (operand_one_value > operand_two_value)
            reg.setSW(0x03);
        else if (operand_one_value < operand_two_value)
            reg.setSW(0x02);
        else if (operand_one_value == operand_two_value)
            reg.setSW(0x01);
        else
            reg.setSW(0x00);
        break;
    case SHIFTL:
        reg.setReg(operand_one, operand_one_value << (operand_two + 1));
        break;
    case SHIFTR:
        reg.setReg(operand_one, operand_one_value >> (operand_two + 1));
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
        notImplemented("TIXR");
        break;
    case PUSHR:
        PUSHA(operand_one, operand_two);
        break;
    case POPR:
        POPA(operand_one, operand_two);
        break;
    default:
        return false;
    }
    return true;
}

int Machine::takeWord(bool immediate, bool indirect, bool simple, int offset, int address)
{

    if (immediate)
    {
        return offset;
    }
    else if (simple)
    {
        return mem.getWord(address);
    }
    else if (indirect)
    {
        return mem.getWord(mem.getWord(address));
    }
    return 0;
}
int Machine::takeByte(bool immediate, bool indirect, bool simple, int offset, int address)
{
    offset &= 0xff;
    if (immediate)
    {
        return offset;
    }
    else if (simple)
    {
        return mem.getByte(address);
    }
    else if (indirect)
    {
        return mem.getByte(mem.getWord(address));
    }
    return 0;
}

void Machine::storeWord(bool immediate, bool indirect, bool simple, int offset, int address, int val)
{
    if (immediate | simple)
    {
        mem.setWord(address, val);
    }
    else if (indirect)
    {
        mem.setWord(mem.getWord(address), val);
    }
}

void Machine::storeByte(bool immediate, bool indirect, bool simple, int offset, int address, int val)
{
    if (immediate | simple)
    {
        mem.setByte(address, val & 0x000000ff);
    }
    else if (indirect)
    {
        mem.setByte(mem.getWord(address), val & 0x000000ff);
    }
}

bool Machine::execF3F4(uint8_t command_opcode, uint8_t ni, uint8_t command_byte_2, uint8_t command_byte_3)
{

    bool x_flag = ((0b10000000 & command_byte_2));
    bool b_flag = ((0b01000000 & command_byte_2));
    bool pc_flag = ((0b00100000 & command_byte_2));

    int offset = ((command_byte_2 & 0b00001111) << 8) | command_byte_3;
    bool e_flag = command_byte_2 & 0b00010000;
    bool neg_offset = command_byte_2 & 0b00001000;

    if (e_flag)
    {
        uint8_t command_byte_4 = fetch();
        offset = (offset << 8) | command_byte_4;
    }

    int address = offset;
    if (neg_offset)
    {
        if (e_flag)
        {
            address = FORMAT4_NEGATIVE_OFFSET + address;
        }
        else
        {
            address = FORMAT3_NEGATIVE_OFFSET + address;
        }
    }
    if (x_flag)
    {
        address = address + reg.getX();
    }
    if (b_flag)
    {
        address = address + reg.getB();
    }
    if (pc_flag)
    {
        address = address + reg.getPC();
    }

    int deviceNumber = 0;

    switch (command_opcode)
    {
    // load and store
    case LDA:
        reg.setA(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case LDX:
        reg.setX(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case LDL:
        reg.setL(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case STA:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getA());
        break;
    case STX:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getX());
        break;
    case STL:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getL());
        break;

    // fixed point arithmetic
    case ADD:
        reg.setA(reg.getA() + takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case SUB:
        reg.setA(reg.getA() - takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case MUL:
        reg.setA(reg.getA() * takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case DIV:
        reg.setA(reg.getA() / takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case COMP:
        if (reg.getA() > takeWord(ni == 1, ni == 2, ni == 3, offset, address))
        {
            reg.setSW(0x03);
        }
        else if (reg.getA() < takeWord(ni == 1, ni == 2, ni == 3, offset, address))
        {
            reg.setSW(0x02);
        }
        else if (reg.getA() == takeWord(ni == 1, ni == 2, ni == 3, offset, address))
        {
            reg.setSW(0x01);
        }
        else
        {
            reg.setSW(0x00);
        }
        break;
    case TIX:
        notImplemented("TIX");
        break;

    // jumps
    case JEQ:
        if (reg.getSW() == 0x01)
        {
            if (ni == 1 || ni == 3)
            {
                reg.setPC(address);
            }
            else if (ni == 2)
            {
                reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
            }
        }
        break;
    case JGT:
        if (reg.getSW() == 0x03)
        {
            if (ni == 1 || ni == 3)
            {
                reg.setPC(address);
            }
            else if (ni == 2)
            {
                reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
            }
        }
        break;
    case JLT:
        if (reg.getSW() == 0x02)
        {
            if (ni == 1 || ni == 3)
            {
                reg.setPC(address);
            }
            else if (ni == 2)
            {
                reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
            }
        }
        break;
    case J:
        if (ni == 1 || ni == 3)
        {
            reg.setPC(address);
        }
        else if (ni == 2)
        {
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
        }
        break;

    // bit manipulation
    case AND:
        reg.setA(reg.getA() & takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case OR:
        reg.setA(reg.getA() | takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;

    // jump to subroutine
    case JSUB:
        reg.setL(reg.getPC());
        if (ni == 1 || ni == 3)
        {
            reg.setPC(address);
        }
        else if (ni == 2)
        {
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
        }
        break;
    case RSUB:
        reg.setPC(reg.getL());
        break;

    // load and store int
    case LDCH:
        reg.setA(takeByte(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case STCH:
        storeByte(ni == 1, ni == 2, ni == 3, offset, address, reg.getA());
        break;

    // floating point arithmetic
    case ADDF:
        notImplemented("ADDF");
        break;
    case SUBF:
        notImplemented("SUBF");
        break;
    case MULF:
        notImplemented("MULF");
        break;
    case DIVF:
        notImplemented("DIVF");
        break;
    case COMPF:
        notImplemented("COMPF");
        break;

    // load and store
    case LDB:
        reg.setB(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case LDS:
        reg.setS(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case LDF:
        notImplemented("LDF");
        // reg.setF(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDT:
        reg.setT(takeWord(ni == 1, ni == 2, ni == 3, offset, address));
        break;
    case STB:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getB());
        break;
    case STS:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getS());
        break;
    case STF:
        notImplemented("STF");
        // storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getA());
        break;
    case STT:
        storeWord(ni == 1, ni == 2, ni == 3, offset, address, reg.getT());
        break;

    // special load and store
    case LPS:
        notImplemented("LPS");
        break;
    case STI:
        notImplemented("STI");
        break;
    case STSW:
        notImplemented("STSW");
        break;

    // devices
    case RD:
        if (ni == 1)
        {
            deviceNumber = offset & 0x000000FF;
        }
        else if (ni == 2)
        {
            deviceNumber = (mem.getByte(mem.getWord(offset)) & 0x000000FF);
        }
        else if (ni == 3)
        {
            deviceNumber = (mem.getByte(offset) & 0x000000FF);
        }
        reg.setA(sio.getDevice(deviceNumber)->read());
        break;
    case WD:
        if (ni == 1)
        {
            deviceNumber = (offset & 0x000000FF);
        }
        else if (ni == 2)
        {
            deviceNumber = (mem.getByte(mem.getWord(offset)) & 0x000000FF);
        }
        else if (ni == 3)
        {
            deviceNumber = (mem.getByte(offset) & 0x000000FF);
        }
        sio.getDevice(deviceNumber)->write(reg.getA() & 0x0000FF);
        break;
    case TD:
        notImplemented("TD");
        break;

    // system
    case SSK:
        notImplemented("SSK");
        break;
    case CALL:
        PUSHPC();
        PUSHL();
        if (ni == 1 || ni == 3)
        {
            reg.setPC(address);
        }
        else if (ni == 2)
        {
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 1, offset, address));
        }
        break;

    case RTN:
        POPC();
        POPL();
        break;

    default:
        return false;
    }
    return true;
}

void Machine::execute()
{
    uint8_t command_byte_1 = fetch();
    uint8_t command_opcode = command_byte_1 & ~(3);
    if (execF1(command_opcode))
        return;

    uint8_t command_byte_2 = fetch();
    if (execF2(command_opcode, command_byte_2))
        return;

    uint8_t command_byte_3 = fetch();
    uint8_t ni = command_byte_1 & 0b00000011;
    if (execF3F4(command_opcode, ni, command_byte_2, command_byte_3))
        return;
    else
        invalidOpcode(command_opcode);
}

void Machine::lineDecoder(string line)
{
    if (line[0] == 'H')
    {
        this->programName = line.substr(1, 6).c_str();

        string programLengthPlaceholder = line.substr(13, 6);
        this->programLength = stoi(programLengthPlaceholder, 0, 16);
    }
    else if (line[0] == 'T')
    {
        string codeAddressPlaceholder = line.substr(1, 6);
        uint32_t codeAddress = stoi(codeAddressPlaceholder, 0, 16);

        string contextLengthPlaceholder = line.substr(7, 2);
        uint32_t contextLength = stoi(contextLengthPlaceholder, 0, 16);

        for (int i = 0; i < contextLength * 2; i += 2)
        {
            string codeContextPlaceHolder = line.substr(9 + i, 2);
            uint32_t codeContext = stoi(codeContextPlaceHolder, 0, 16);

            mem.setByte(codeAddress + (i / 2), codeContext);
        }
    }
    else if (line[0] == 'M')
    {
    }
    else if (line[0] == 'E')
    {
        string programStartPlaceholder = line.substr(1, 6);
        this->programStart = stoi(programStartPlaceholder, 0, 16);
    }
    else if (line[0] == 'D')
    {
    }
    else if (line[0] == 'R')
    {
    }
}

void Machine::loadProgram(string fileName)
{
    this->file.open(fileName.c_str());

    char line[100];
    streamsize lineLength = 100;

    while (this->file.getline(line, lineLength)) {
        lineDecoder(line);
    }

    reg.setPC(programStart);

    this->file.close();
}

void Machine::step()
{
    execute();
    this->instruction_counter++;
}
void Machine::start()
{
    this->run = true;
    while (this->run)
    {
        int finalPc = reg.getPC();

        clock_t start, end;
        start = clock();

        step();

        while (double(clock() - start) / double(CLOCKS_PER_SEC) < this->speed) 
        
        if (reg.getPC() == finalPc) break;
    }
}
void Machine::stop()
{
    this->run = false;
}

void Machine::setSpeed(int hertz)
{
    this->hertz = hertz;
    this->speed = (double) 1 / (double) hertz;
}

int Machine::getSpeed()
{
    return this->hertz;
}

Machine::Machine()
{
    this->hertz = DEFAULT_CLOCK_FREQ;
    this->speed = (double) 1 / (double) DEFAULT_CLOCK_FREQ;
    this->run = true;
    this->instruction_counter = 0;

    // loadProgram("test.obj");
    // setSpeed(10000);
    // start();

}