#include "Machine.h"
#include "Registry.h"
#include "Memory.h"

#include <iostream>

using namespace std;

Machine::Machine() {
  cout << "Machine works!\n";
  Registry reg;
  Memory mem;

  mem.setByte(1, -18);
  mem.setByte(2, 255);

  mem.setWord(4, -80000);
  cout << mem.getWord(4);
  mem.print(5, 42);
}