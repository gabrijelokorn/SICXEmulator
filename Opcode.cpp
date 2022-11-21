#include <iostream>
#include <map>
#include <string>
#include <cinttypes>

#include "Opcode.h"

using namespace std;

Opcode::Opcode() {

    map <uint8_t, string> opCodeMap;

    // load and store
    opCodeMap.insert(pair<uint8_t, string>(0x00, "LDA"));
    opCodeMap.insert(pair<uint8_t, string>(0x04, "LDX"));
    opCodeMap.insert(pair<uint8_t, string>(0x08, "LDL"));
    opCodeMap.insert(pair<uint8_t, string>(0x0C, "STA"));
    opCodeMap.insert(pair<uint8_t, string>(0x10, "STX"));
    opCodeMap.insert(pair<uint8_t, string>(0x14, "STL"));

    // fixed point arithmetic
    opCodeMap.insert(pair<uint8_t, string>(0x18, "ADD"));
    opCodeMap.insert(pair<uint8_t, string>(0x1C, "SUB"));
    opCodeMap.insert(pair<uint8_t, string>(0x20, "MUL"));
    opCodeMap.insert(pair<uint8_t, string>(0x24, "DIV"));
    opCodeMap.insert(pair<uint8_t, string>(0x28, "COMP"));
    opCodeMap.insert(pair<uint8_t, string>(0x2C, "TIX"));

    // jumps
    opCodeMap.insert(pair<uint8_t, string>(0x30, "JEQ"));
    opCodeMap.insert(pair<uint8_t, string>(0x34, "JGT"));
    opCodeMap.insert(pair<uint8_t, string>(0x38, "JLT"));
    opCodeMap.insert(pair<uint8_t, string>(0x3C, "J"));

    // bit manipulation
    opCodeMap.insert(pair<uint8_t, string>(0x40, "AND"));
    opCodeMap.insert(pair<uint8_t, string>(0x44, "OR"));

    // jump to subroutine
    opCodeMap.insert(pair<uint8_t, string>(0x48, "JSUB"));
    opCodeMap.insert(pair<uint8_t, string>(0x4C, "RSUB"));

    // load and store int
    opCodeMap.insert(pair<uint8_t, string>(0x50, "LDCH"));
    opCodeMap.insert(pair<uint8_t, string>(0x54, "STCH"));

    // floating point arithmetic
    opCodeMap.insert(pair<uint8_t, string>(0x58, "ADDF"));
    opCodeMap.insert(pair<uint8_t, string>(0x5C, "SUBF"));
    opCodeMap.insert(pair<uint8_t, string>(0x60, "MULF"));
    opCodeMap.insert(pair<uint8_t, string>(0x64, "DIVF"));
    opCodeMap.insert(pair<uint8_t, string>(0x88, "COMPF"));

    // special load and store
    opCodeMap.insert(pair<uint8_t, string>(0x68, "LDB"));
    opCodeMap.insert(pair<uint8_t, string>(0x6C, "LDS"));
    opCodeMap.insert(pair<uint8_t, string>(0x70, "LDF"));
    opCodeMap.insert(pair<uint8_t, string>(0x74, "LDT"));
    opCodeMap.insert(pair<uint8_t, string>(0x78, "STB"));
    opCodeMap.insert(pair<uint8_t, string>(0x7C, "STS"));
    opCodeMap.insert(pair<uint8_t, string>(0x80, "STF"));
    opCodeMap.insert(pair<uint8_t, string>(0x84, "STT"));

    // special load and store
    opCodeMap.insert(pair<uint8_t, string>(0xD0, "LPS"));
    opCodeMap.insert(pair<uint8_t, string>(0xD4, "STI"));
    opCodeMap.insert(pair<uint8_t, string>(0xE8, "STSW"));

    // devices
    opCodeMap.insert(pair<uint8_t, string>(0xD8, "RD"));  
    opCodeMap.insert(pair<uint8_t, string>(0xDC, "WD"));
    opCodeMap.insert(pair<uint8_t, string>(0xE0, "TD"));

    // system
    opCodeMap.insert(pair<uint8_t, string>(0xEC, "SSK"));
    
    // ***** SIC/XE Format 1 *****
    opCodeMap.insert(pair<uint8_t, string>(0xC0, "FLOAT"));
    opCodeMap.insert(pair<uint8_t, string>(0xC4, "FIX"));
    opCodeMap.insert(pair<uint8_t, string>(0xC8, "NORM"));
    opCodeMap.insert(pair<uint8_t, string>(0xF0, "SIO"));
    opCodeMap.insert(pair<uint8_t, string>(0xF4, "HIO"));
    opCodeMap.insert(pair<uint8_t, string>(0xF8, "TIO"));

    // ***** SIC/XE Format 2 *****
    opCodeMap.insert(pair<uint8_t, string>(0x90, "ADDR"));
    opCodeMap.insert(pair<uint8_t, string>(0x94, "SUBR"));
    opCodeMap.insert(pair<uint8_t, string>(0x98, "MULR"));
    opCodeMap.insert(pair<uint8_t, string>(0x9C, "DIVR"));
    opCodeMap.insert(pair<uint8_t, string>(0xA0, "COMPR"));
    opCodeMap.insert(pair<uint8_t, string>(0xA4, "SHIFTL"));
    opCodeMap.insert(pair<uint8_t, string>(0xA8, "SHIFTR"));
    opCodeMap.insert(pair<uint8_t, string>(0xAC, "RMO"));
    opCodeMap.insert(pair<uint8_t, string>(0xB0, "SVC"));
    opCodeMap.insert(pair<uint8_t, string>(0xB4, "CLEAR"));
    opCodeMap.insert(pair<uint8_t, string>(0xB8, "TIXR"));

    // ************ Directives ******************
    map <uint8_t, string> directivesMap;

    directivesMap.insert(pair<uint8_t, string>(0, "START"));
    directivesMap.insert(pair<uint8_t, string>(1, "END"));
    directivesMap.insert(pair<uint8_t, string>(2, "CSECT"));
    directivesMap.insert(pair<uint8_t, string>(3, "USE"));
    directivesMap.insert(pair<uint8_t, string>(4, "EXTREF"));
    directivesMap.insert(pair<uint8_t, string>(5, "EXTDEF"));
    directivesMap.insert(pair<uint8_t, string>(6, "ORG"));
    directivesMap.insert(pair<uint8_t, string>(7, "LTORG"));
    directivesMap.insert(pair<uint8_t, string>(8, "BASE"));
    directivesMap.insert(pair<uint8_t, string>(9, "NOBASE"));
    directivesMap.insert(pair<uint8_t, string>(10, "EQU"));

    // Storage directives
    map <uint8_t, string> storageMap;

    storageMap.insert(pair<uint8_t, string>(0, "RESB"));
    storageMap.insert(pair<uint8_t, string>(1, "RESW"));
    storageMap.insert(pair<uint8_t, string>(2, "RESF"));
    storageMap.insert(pair<uint8_t, string>(3, "BYTE"));
    storageMap.insert(pair<uint8_t, string>(4, "WORD"));
    storageMap.insert(pair<uint8_t, string>(5, "FLOT"));

}