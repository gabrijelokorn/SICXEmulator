#ifndef SICXE_MEMORY_H
#define SICXE_MEMORY_H

#include <iostream>
#include <cstdint>

#define MAX_ADDRESS 1048575

#define MAX_F34_VALUE 1048575
#define MIN_F34_VALUE -2048

#define MAX_BYTE_VALUE 255
#define MIN_BYTE_VALUE -128

class Memory {
   private:
    uint8_t MEMORY[MAX_ADDRESS + 1];

   public:
    void outOfMemoryError(int addr);

    int getByte(int addr);
    void setByte(int addr, int val);

    int getWord(int addr);
    void setWord(int addr, int val);

    void print(int from, int to);
    explicit Memory();
};

#endif