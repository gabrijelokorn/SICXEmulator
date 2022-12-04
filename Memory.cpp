#include <iostream>

#include "Memory.h"
#include "Registry.h"

using namespace std;

void Memory::outOfMemoryError() {
    cout << "Address is not in memory range [0, 1048575]!\n";
}

void Memory::invalidByteValueMemoryError(int val) {
    printf("Value is not int range of type byte [-128, 255]!, your value: %d\n", val);
}

void Memory::invalidWordValueMemoryError(int val) {
    printf("Value is not int range of type word [-8388608, 8388607], your value: %d!\n", val);
}

int Memory::getByte(int addr) {
    if (addr >= 0 && addr <= MAX_ADDRESS) {
        return MEMORY[addr];
    } else {
        outOfMemoryError();
    }
    return -1;
}

void Memory::setByte(int addr, int val) {
    if (addr < 0 || addr > MAX_ADDRESS) {
        cout << "bla: " << MAX_ADDRESS;
        outOfMemoryError();
    }

    if (val >= MIN_BYTE_VALUE && val <= MAX_BYTE_VALUE) {
        MEMORY[addr] = val;
    } else {
        invalidByteValueMemoryError(val);
    }
}

int Memory::getWord(int addr) {
    if (addr >= 0 && addr <= MAX_ADDRESS - 2) {
        int firstNum = getByte(addr);
        if (firstNum >= 128) {
            firstNum = -128 + (firstNum - 128);
        }
        return (firstNum << 16) + (getByte(addr + 1) << 8) +
               (getByte(addr + 2));
    } else {
        outOfMemoryError();
    }
    return -1;
}

void Memory::setWord(int addr, int val) {
    if (addr < 0 || addr > MAX_ADDRESS - 2) {
        outOfMemoryError();
    }

    if (val >= MIN_WORD_VALUE && val <= MAX_WORD_VALUE) {
        int final_value = addr;
        MEMORY[addr + 2] = val;
        val = val >> 8;
        MEMORY[addr + 1] = val;
        val = val >> 8;
        MEMORY[addr] = val;

    } else {
        invalidWordValueMemoryError(val);
    }
}

void Memory::print(int from, int to) {
    int row = from / 16;
    for (int i = (from / 16) * 16; i < to; i++) {
        if (!(i % 16)) {
            cout << endl;
            printf("0x%05X ", row * 16);
            row++;
        };
        printf("%02X ", getByte(i));
    }
    cout << endl;
}

// void Memory::set_base_flag(bool val) {
//     this->base_flag = val;
// }
// void Memory::set_pc_flag(bool val) {
//     this->pc_flag = val;
// }
// void Memory::set_x_flag(bool val) {
//     this->x_flag = val;
// }
// bool Memory::get_base_flag() {
//     return this->base_flag;
// }
// bool Memory::get_pc_flag() {
//     return this->pc_flag;
// }
// bool Memory::get_x_flag() {
//     return this->x_flag;
// }

Memory::Memory() { 
    // set_base_flag(0);
    // set_pc_flag(0);
    // set_x_flag(0);
    cout << "Memory works!\n"; 
}
