#ifndef SICXE_MEMORY_H
#define SICXE_MEMORY_H

#include <cstdint>
#define MAX_ADDRESS 1048575

class Memory {
   private:
    uint8_t MEMORY[MAX_ADDRESS + 1];

   public:
    void outOfMemoryError();
    void invalidByteValueMemoryError();
    void invalidWordValueMemoryError();

    int getByte(int addr);
    void setByte(int addr, int val);

    int getWord(int addr);
    void setWord(int addr, int val);

    void print(int from, int to);
    Memory();
};

#endif