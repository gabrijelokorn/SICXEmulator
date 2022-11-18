#include "Memory.h"

#include <iostream>

using namespace std;

void Memory::outOfMemoryError () {
    cout << "Address not in memory range [0, 1048575]!\n";
}

void Memory::invalidByteValueMemoryError () {
    cout << "Value not int range of type byte [-128, 255]!\n";
}

void Memory::invalidWordValueMemoryError () {
    cout << "Value not int range of type word [-8388608, 8388607]!\n";
}

int Memory::getByte(int addr) { 
    if(addr >= 0 && addr <= MAX_ADDRESS) {
        return MEMORY[addr]; 
    } else {
        outOfMemoryError();
    }
    return -1;
}

void Memory::setByte(int addr, int val) {
    if(addr < 0 || addr > MAX_ADDRESS) {
        cout << "bla: " << MAX_ADDRESS;
        outOfMemoryError();
    }

    if (val >= -128 && val <= 255) {
        MEMORY[addr] = val;
    } else {
        invalidByteValueMemoryError();
    }
}

int Memory::getWord(int addr) { 
    if(addr >= 0 && addr <= MAX_ADDRESS) {
        int firstNum = getByte(addr);
        if (firstNum >= 128) {
            firstNum = -128 + (firstNum - 128);
        }
        return (firstNum << 16) + (getByte(addr + 1) << 8) + (getByte(addr + 2)); 
    } else {
        outOfMemoryError();
    }
    return -1;
}

void Memory::setWord(int addr, int val) {
    if(addr < 0 || addr > MAX_ADDRESS) {
        outOfMemoryError();
    }

    if (val >= -8388608 && val <= 8388607) {
        MEMORY[addr + 2] = val;
        val = val >> 8;
        MEMORY[addr + 1] = val;
        val = val >> 8;
        MEMORY[addr] = val;

    } else {
        invalidByteValueMemoryError();
    }
}

void Memory::print(int from, int to) {
    int row = from / 16;
    for (int i = (from / 16) * 16; i < to; i++) {
        if (!(i % 16)) {
            cout << endl;
            printf("0x%05x ", row);
            row++;
        };
        printf("%02x ", getByte(i));
    }
    cout << endl;
}

Memory::Memory() { cout << "Memory works!\n"; }
