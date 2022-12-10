#include <iostream>

#include "Registry.h"
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

// TODO
// int Registry::getF() { return this->F; }
// void Registry::setF(int val) { this->F = val; }

int Registry::getPC() { return this->PC; }
void Registry::setPC(int val) { this->PC = val; }

int Registry::getSW() { return this->SW; }
void Registry::setSW(int val) { this->SW = val; }

int Registry::getSMP() { return this->SMP; }
void Registry::setSMP(int val) { this->SMP = val; }

int Registry::getSBP() { return this->SBP; }
void Registry::setSBP(int val) { this->SBP = val; }

int Registry::getReg(int reg)
{
    switch (reg)
    {
    case (0):
    {
        return getA();
    }
    case (1):
    {
        return getX();
    }
    case (2):
    {
        return getL();
    }
    case (3):
    {
        return getB();
    }
    case (4):
    {
        return getS();
    }
    case (5):
    {
        return getT();
    }
    // TODO
    case (6):
    {
        return 0;
    }
    // TODO
    case (7):
    {
        return 0;
    }
    case (8):
    {
        return getPC();
    }
    case (9):
    {
        return getSW();
    }
    case (10):
    {
        return getSMP();
    }
    case (11):
    {
        return getSBP();
    }
    }
    return 0;
}

void Registry::setReg(int reg, int val)
{
    switch (reg)
    {
    case (0):
    {
        setA(val);
        break;
    }
    case (1):
    {
        setX(val);
        break;
    }
    case (2):
    {
        setL(val);
        break;
    }
    case (3):
    {
        setB(val);
        break;
    }
    case (4):
    {
        setS(val);
        break;
    }
    case (5):
    {
        setT(val);
        break;
    }
    // TODO
    // case (6): {
    //     setF(val);
    // }
    case (7):
    {
    }
    case (8):
    {
        setPC(val);
        break;
    }
    case (9):
    {
        setSW(val);
        /*
        SW values:
        0x00 - not equal (undefined)
        0x01 - equal
        0x02 - less than
        0x03 - greater than
        */
        break;
    }
    case (10):
    {
        setSMP(val);
        break;
    }
    case (11):
    {
        setSBP(val);
        break;
    }
    }
}

void Registry::incrementPC()
{
    this->setPC(this->getPC() + 1);
}

void Registry::resetRegisters()
{
    setA(0);
    setX(0);
    setL(0);
    setB(0);
    setS(0);
    setT(0);
    setPC(0);
    setSW(0);
    setSMP(MAX_ADDRESS - 2);
    setSBP(MAX_ADDRESS - 2);
}

void Registry::printRegisters()
{
    printf("A: %02x\nX: %02x\nL: %02x\nB: %02x\nS: %02x\nT: %02x\nF: %02x\nPC: %02x\nSW: %02x\nSMP: %02x\nSBP: %02x\n", getA(), getX(), getL(), getB(), getS(), getT(), 0, getPC(), getSW(), getSMP(), getSBP());
}

Registry::Registry()
{
    resetRegisters();
}