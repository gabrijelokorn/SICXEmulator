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
    printf("Warning: Addressing is not valid");
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
            reg.setSW(reg.getSW() | 0x03);
        else if (operand_one_value < operand_two_value)
            reg.setSW(reg.getSW() | 0x02);
        else if (operand_one_value == operand_two_value)
            reg.setSW(reg.getSW() | 0x01);
        else
            reg.setSW(0x00);
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
    default:
        return false;
    }
    return true;
}

void Machine::storeByte(bool immediate, bool indirect, bool simple, int offset, int val)
{
    // TODO: TEST
    if (immediate || simple)
    {
        mem.setByte(offset, (uint8_t)(val && 0x000000FF));
    }
    else if (indirect)
    {
        mem.setByte(mem.getWord(offset), (uint8_t)(val && 0x000000FF));
    }
}

void Machine::storeWord(bool immediate, bool indirect, bool simple, int offset, int val)
{
    // TODO: TEST
    if (immediate || simple)
    {
        mem.setWord(offset, val);
    }
    else if (indirect)
    {
        mem.setWord(mem.getWord(offset), val);
    }
}

int Machine::takeWord(bool immediate, bool indirect, bool simple, int offset)
{
    // TODO: TEST
    if (immediate)
    {
        return offset;
    }
    else if (indirect)
    {
        return mem.getWord(mem.getWord(offset));
    }
    else if (simple)
    {
        return mem.getWord(offset);
    }
    return -1;
}

int Machine::takeByte(bool immediate, bool indirect, bool simple, int offset)
{
    // TODO: TEST
    if (immediate)
    {
        return (uint8_t)(offset & 0x000000FF);
    }
    else if (indirect)
    {
        return (uint8_t)(mem.getByte(mem.getWord(offset)));
    }
    else if (simple)
    {
        return (uint8_t)mem.getByte(offset);
    }
    return -1;
}

bool Machine::execF3F4(uint8_t command_opcode, uint8_t ni, uint8_t command_byte_2, uint8_t command_byte_3)
{

    int offset = ((command_byte_2 & 0b00001111) << 8) | command_byte_3;
    bool e_flag = command_byte_2 & 0b00010000;
    if (e_flag)
    {
        offset = (offset << 8) | fetch();
    }

    bool x_flag = ((0b10000000 & command_byte_2));
    bool b_flag = ((0b01000000 & command_byte_2));
    bool pc_flag = ((0b00100000 & command_byte_2));
    if (x_flag)
        offset = offset + reg.getX();
    if (b_flag)
        offset = offset + reg.getB();
    if (pc_flag)
        offset = offset + reg.getPC();
    int deviceNumber = 0;

    switch (command_opcode)
    {
    // load and store
    case LDA:
        reg.setA(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDX:
        reg.setX(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDL:
        reg.setL(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case STA:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getA());
        break;
    case STX:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getX());
        break;
    case STL:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getL());
        break;

    // fixed point arithmetic
    case ADD:
        reg.setA(reg.getA() + takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case SUB:
        reg.setA(reg.getA() - takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case MUL:
        reg.setA(reg.getA() * takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case DIV:
        reg.setA(reg.getA() / takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case COMP:
        if (reg.getA() > takeWord(ni == 1, ni == 2, ni == 3, offset))
            reg.setSW(reg.getSW() | 0x03);
        else if (reg.getA() < takeWord(ni == 1, ni == 2, ni == 3, offset))
            reg.setSW(reg.getSW() | 0x02);
        else if (reg.getA() == takeWord(ni == 1, ni == 2, ni == 3, offset))
            reg.setSW(reg.getSW() | 0x01);
        else
            reg.setSW(0x00);
        break;
    case TIX:
        notImplemented("TIX");
        break;

    // jumps
    case JEQ:
        if (reg.getSW() == 0x01)
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case JGT:
        if (reg.getSW() == 0x03)
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case JLT:
        if (reg.getSW() == 0x02)
            reg.setPC(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case J:
        reg.setPC(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;

    // bit manipulation
    case AND:
        reg.setA(reg.getA() & takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case OR:
        reg.setA(reg.getA() | takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;

    // jump to subroutine
    case JSUB:
        reg.setPC(takeWord(ni == 1, ni == 2, ni == 3, offset));
        reg.setL(reg.getPC());
        break;
    case RSUB:
        reg.setPC(reg.getL());
        break;

    // load and store int
    case LDCH:
        reg.setA(takeByte(ni == 1, ni == 2, ni == 3, offset));
        break;
    case STCH:
        storeByte(ni == 1, ni == 2, ni == 3, offset, reg.getA());
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
        printf("sc: %d\n", command_byte_2);
        printf("tc: %d\n", command_byte_3);
        printf("pc: %d\n", reg.getPC());

        notImplemented("COMPF");
        break;

    // load and store
    case LDB:
        reg.setB(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDS:
        reg.setS(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDF:
        notImplemented("LDF");
        // reg.setF(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case LDT:
        reg.setT(takeWord(ni == 1, ni == 2, ni == 3, offset));
        break;
    case STB:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getB());
        break;
    case STS:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getS());
        break;
    case STF:
        notImplemented("STF");
        // storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getA());
        break;
    case STT:
        storeWord(ni == 1, ni == 2, ni == 3, offset, reg.getT());
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
        // printf("dn:%d\n", deviceNumber);
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
            // printf("nije3: %d\n", deviceNumber);
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

void Machine::lineDecoder (string line) {
    if (line[0] == 'H') {
        // printf("Header Line\n");
        this->programName = line.substr(1, 6).c_str();

        string programLengthPlaceholder = line.substr(13, 6);
        this->programLength = stoi(programLengthPlaceholder, 0, 16);
    } else if (line[0] == 'T') {
        // printf("text Line\n");
        string codeAddressPlaceholder = line.substr(1, 6);
        uint32_t codeAddress = stoi(codeAddressPlaceholder, 0, 16);
        
        string contextLengthPlaceholder = line.substr(7, 2);
        uint32_t contextLength = stoi(contextLengthPlaceholder, 0, 16);

        for (int i = 0; i < contextLength * 2; i+= 2) {
            string codeContextPlaceHolder = line.substr(9 + i, 2);
            uint32_t codeContext = stoi(codeContextPlaceHolder, 0, 16);

            mem.setByte(codeAddress + (i / 2), codeContext);
        }


    } else if (line[0] == 'M') {
        // printf("m Line\n");
    } else if (line[0] == 'E') {
        string programStartPlaceholder = line.substr(1, 6);
        this->programStart = stoi(programStartPlaceholder, 0, 16);
        // printf("end Line\n");
    } else if (line[0] == 'D') {
        // printf("EXPORTING Line\n");
    } else if (line[0] == 'R') {
        // printf("IMPORTING Line\n");
    }
}

void Machine::loadProgram(string fileName){
    this->file.open(fileName.c_str());

    char line[100];
    streamsize lineLength = 100;

    while (this->file.getline(line, lineLength)) lineDecoder(line);
    
    reg.setPC(programStart);

    this->file.close();
}

Machine::Machine() {
    cout << "Machine works!\n";
    loadProgram("fakulteta.obj");

    // printf("%s\n", this->programName);
    // printf("%d\n", this->programStart);
    // printf("%d\n", this->programLength);

    mem.print(0, 500);
    reg.printRegisters();
    for (int i = 0; i < 69; i++) {
        execute();
    }
    mem.print(0, 500);
    reg.printRegisters();
        // // FACulty
    //     mem.setWord(0, 0x011034);
    //     mem.setByte(3, 0x00);
    //     mem.setWord(4, 0x1D0003);
    //     mem.setWord(7, 0x0F20B2);
    //     mem.setWord(10, 0x0F20B2);
    //     mem.setWord(13, 0x4F0000);
    //     mem.setWord(16, 0x0320A9);
    //     mem.setWord(19, 0x1D0003);
    //     mem.setWord(22, 0x0F20A3);
    //     mem.setWord(25, 0x4F0000);
    //     mem.setWord(28, 0x03209D);
    //     mem.setWord(31, 0x190003);
    //     mem.setWord(34, 0x0F2097);
    //     mem.setWord(37, 0x4F0000);
    //     mem.setWord(40, 0x162091);
    //     mem.setWord(43, 0x4B2FE2);
    //     mem.setWord(46, 0x03208E);
    //     mem.setWord(59, 0x0E2088);
    //     mem.setWord(52, 0x032085);
    //     mem.setWord(55, 0x0F2085);
    //     mem.setWord(58, 0x4B2FD3);
    //     mem.setWord(61, 0x03207F);
    //     mem.setWord(64, 0x190006);
    //     mem.setWord(67, 0x0F2082);
    //     mem.setWord(70, 0x02207F);
    //     mem.setWord(73, 0x2B2079);
    //     mem.setWord(76, 0x372021);
    //     mem.setWord(89, 0x750001);
    //     mem.setWord(82, 0x03206A);
    //     mem.setWord(85, 0x190003);
    //     mem.setWord(98, 0x0F2070);
    //     mem.setWord(91, 0x0A206D);
    //     mem.setWord(94, 0x03205E);
    //     mem.setWord(97, 0x190006);
    //     mem.setWord(100, 0x0F2055);
    //     mem.setWord(103, 0x022055);
    //     mem.setWord(106, 0x0F2052);
    //     mem.setWord(119, 0x4F0000);
    //     mem.setWord(112, 0x1D0001);
    //     mem.setWord(115, 0x0E2046);
    //     mem.setWord(128, 0x4B2F97);
    //     mem.setWord(121, 0x4B2FAC);
    //     mem.setWord(124, 0x032040);
    //     mem.setWord(127, 0x190006);
    //     mem.setWord(130, 0x0F2043);
    //     mem.setWord(133, 0x022040);
    //     mem.setByte(136, 0x98);
    //     mem.setByte(137, 0x05);
    //     mem.setWord(138, 0x032032);
    //     mem.setWord(141, 0x190003);
    //     mem.setWord(144, 0x0F2038);
    //     mem.setWord(147, 0x0A2035);
    //     mem.setWord(150, 0x032026);
    //     mem.setWord(153, 0x190006);
    //     mem.setWord(156, 0x0F201D);
    //     mem.setWord(159, 0x02201D);
    //     mem.setWord(162, 0x0F201A);
    //     mem.setWord(165, 0x4F0000);
    //     mem.setByte(168, 0xB4);
    //     mem.setByte(169, 0x00);
    //     mem.setWord(170, 0x4B2F53);
    //     mem.setWord(173, 0x032012);
    //     mem.setWord(176, 0x0E2009);
    //     mem.setWord(179, 0x4B2F5A);
    //     mem.setWord(182, 0x4B2F6F);
    //     mem.setWord(185, 0x3F2FFD);
    //     mem.setWord(188, 0x000000);
    //     mem.setWord(191, 0x000000);
    //     mem.setWord(194, 0x00000A);
    //     mem.setWord(197, 0x000001);
    //     mem.setWord(200, 0x000000);
    //     mem.setWord(203, 0x000000);

    //     reg.printRegisters();
    //     mem.print(0, 80);

    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();
    //     execute();

    //     reg.printRegisters();
    //     mem.print(0, 80);

    // WD TESTS
    // mem.setWord(0, 0x190061);
    // mem.setWord(3, 0xDE2003);
    // mem.setWord(6, 0x3F2FFD);

    // mem.print(0, 80);
    // execute();
    // execute();
    // execute();
    // mem.print(0, 80);

    // RD TESTS
    // printf("a: %d\n", reg.getA());
    // mem.setWord(0, 0xDB2003);
    // mem.setWord(3, 0xDE2003);
    // mem.setWord(6, 0x190000);

    // mem.print(0, 80);
    // execute();
    // execute();
    // mem.print(0, 80);
    // printf("a: %d\n", reg.getA());

    // sio.getDevice(97)->write(97);

    // LDA exercise
    // mem.setWord(0, 0x010032);
    // mem.setWord(3, 0x032009);
    // mem.setWord(6, 0x022006);
    // mem.setWord(9, 0x022006);
    // mem.setWord(15, 0x00001E);
    // mem.setWord(18, 0x010000);
    // mem.setWord(30, 150);

    // mem.print(0, 80);
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // mem.print(0, 80);

    // mem.setByte(0, 0x01);
    // mem.setByte(1, 0x00);
    // mem.setByte(2, 0x17);
    // mem.setByte(3, 0x0d);
    // mem.setByte(4, 0x00);
    // mem.setByte(5, 0x32);
    // mem.setByte(6, 0x0f);
    // mem.setByte(7, 0x20);
    // mem.setByte(8, 0x06);
    // mem.setByte(9, 0x0E);
    // mem.setByte(10, 0x20);
    // mem.setByte(11, 0x03);

    // first   START 0
    //         LDA   #23
    //         STA   #50
    //         STA   mem
    //         STA   @mem
    //         END   first
    // halt    J   halt

    // mem     WORD    30

    // mem.print(0, 80);
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // execute();
    // printf("A: %d\n", reg.getA());
    // mem.print(0, 80);
}