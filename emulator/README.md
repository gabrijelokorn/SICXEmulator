# SICXEmulator

## Prerequisites
1. *g++*

## Upgrading Emulator
Add headers to **include** directory and **source** (cpp) files into src directory.
## Compilation
```bash
g++ `pkg-config gtk+-3.0 --cflags` ./src/*.cpp -I ./include/ -o main `pkg-config gtk+-3.0 --libs`
```
## Execution
```bash
./emulator
```