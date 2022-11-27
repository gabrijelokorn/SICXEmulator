#ifndef SICXE_MEMORY_H
#define SICXE_MEMORY_H

#include <iostream>
#include <cstdint>

#define MAX_ADDRESS 1048575
#define MAX_WORD_VALUE 8388607
#define MIN_WORD_VALUE -8388608
#define MAX_BYTE_VALUE 255
#define MIN_BYTE_VALUE -128

class Memory {
   private:
    uint8_t MEMORY[MAX_ADDRESS + 1];
    // bool base_flag;
    // bool pc_flag;
    // bool x_flag;

   public:
    void outOfMemoryError();
    void invalidByteValueMemoryError();
    void invalidWordValueMemoryError();

    int getByte(int addr);
    void setByte(int addr, int val);

    int getWord(int addr);
    void setWord(int addr, int val);

    // void set_base_flag(bool val);
    // void set_pc_flag(bool val);
    // void set_x_flag(bool val) ;
    // bool get_base_flag();
    // bool get_pc_flag();
    // bool get_x_flag();

    void print(int from, int to);
    explicit Memory();
};

#endif