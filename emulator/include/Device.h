#ifndef SICXE_DEVICE_H
#define SICXE_DEVICE_H

#include <iostream>
#include <cstdint>

using namespace std;

class Device {
   private:
   public:
    virtual int read();
    virtual void write(uint8_t val);
    virtual bool test();
};

#endif