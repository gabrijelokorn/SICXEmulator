#ifndef SICXE_INPUTOUTPUT_H
#define SICXE_INPUTOUTPUT_H

#include <iostream>
#include "Device.h"

#define MAX_DEV 256
#define STANDARD_INPUT_DEVICE 0
#define STANDARD_OUTPUT_DEVICE 1
#define STANDARD_ERROR_DEVICE 2

using namespace std;

class SicXeIO {
 private:
  Device* devices[MAX_DEV];
 public:
  void setDevice(int num, Device* dev);
  Device getDevice(int num);
  SicXeIO();
};


#endif