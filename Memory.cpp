#include <iostream>

#include "Memory.h"
#include "Registry.h"

using namespace std;

void Memory::outOfMemoryError(int addr) {
    printf("Address: %d is not in memory range [0, 1048575]!\n", addr);
}

int Memory::getWord(int addr) {
    if (addr >= 0 && addr <= MAX_ADDRESS - 2) {
        return (MEMORY[addr] << 16) + (MEMORY[addr + 1] << 8) +(MEMORY[addr + 2]);
    } else {
        outOfMemoryError(addr);
    }
    return 0xffffffff;
}

int Memory::getByte(int addr) {
    if (addr >= 0 && addr <= MAX_ADDRESS) {
        return MEMORY[addr];
    } else {
        outOfMemoryError(addr);
    }
    return 0;
}

void Memory::setWord(int addr, int val) {
    if (addr < 0 || addr > MAX_ADDRESS - 2) {
        outOfMemoryError(addr);
        return;
    }
    MEMORY[addr + 2] = val;
    val = val >> 8;
    MEMORY[addr + 1] = val;
    val = val >> 8;
    MEMORY[addr + 0] = val;
}

void Memory::setByte(int addr, int val) {
    if (addr < 0 || addr > MAX_ADDRESS) {
        outOfMemoryError(addr);
        return;
    }
    MEMORY[addr] = val;
}

void Memory::print(int from, int to) {
    int row = from / 16;
    for (int i = (from / 16) * 16; i <= to; i++) {
        if (!(i % 16)) {
            cout << endl;
            printf("0x%05X ", row * 16);
            row++;
        };
        printf("%02X ", getByte(i));
    }
    cout << endl;
}

Memory::Memory() { 
}
