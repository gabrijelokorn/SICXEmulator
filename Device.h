#ifndef SICXE_DEVICE_H
#define SICXE_DEVICE_H

#include <iostream>
#include <cstdint>

using namespace std;

class Device {
   private:
   public:
    uint8_t read();
    void write();
    bool test();
    Device();
};

#endif