#ifndef SICXE_DEVICE_H
#define SICXE_DEVICE_H

#include <cstdint>

class Device {
   private:
   public:
    uint8_t read();
    void write();
    bool test();
    Device();
};

#endif