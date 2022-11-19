#include "Registry.h"
#include <iostream>
#include "Machine.h"

using namespace std;

int Registry::getA() { return this->A; }
void Registry::setA(int val) { this->A = val; }

int Registry::getX() { return this->X; }
void Registry::setX(int val) { this->X = val; }

int Registry::getL() { return this->L; }
void Registry::setL(int val) { this->L = val; }

int Registry::getB() { return this->B; }
void Registry::setB(int val) { this->B = val; }

int Registry::getS() { return this->S; }
void Registry::setS(int val) { this->S = val; }

int Registry::getT() { return this->T; }
void Registry::setT(int val) { this->T = val; }

// int Registry::getF() { return this->F; }
// void Registry::setF(int val) { this->F = val; }

int Registry::getPC() { return this->PC; }
void Registry::setPC(int val) { this->PC = val; }

int Registry::getSW() { return this->SW; }
void Registry::setSW(int val) { this->SW = val; }

int Registry::getReg(int reg) {
    switch (reg) {
        case (0): {
            return getA();
        }
        case (1): {
            return getX();
        }
        case (2): {
            return getL();
        }
        case (3): {
            return getB();
        }
        case (4): {
            return getS();
        }
        case (5): {
            return getT();
        }
        // case (6): {
        //     return getF();
        // }
        // case (7): {
        //     return 0;
        // }
        case (8): {
            return getPC();
        }
        case (9): {
            return getSW();
        }
    }
    return 0;
}

void Registry::setReg(int reg, int val) {
    switch (reg) {
        case (0): {
            setA(val);
        }
        case (1): {
            setX(val);
        }
        case (2): {
            setL(val);
        }
        case (3): {
            setB(val);
        }
        case (4): {
            setS(val);
        }
        case (5): {
            setT(val);
        }
        // case (6): {
        //     setF(val);
        // }
        case (8): {
            setPC(val);
        }
        case (9): {
            setSW(val);
        }
    }
}

Registry::Registry() { cout << "Registry works!\n"; }