#ifndef SICXE_DEVICE_H
#define SICXE_DEVICE_H

#include <iostream>
#include <cstdint>

using namespace std;

class Device {
   private:
   public:
    virtual uint8_t read();
    void write(uint8_t val);
    bool test();
};

#endif