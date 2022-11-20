#ifndef SICXE_REGISTRY_H
#define SICXE_REGISTRY_H

#include <iostream>

#include "Machine.h"

using namespace std;

class Registry {
   private:
    int A;
    int X;
    int L;
    int B;
    int S;
    int T;
    double F;
    int PC;
    int SW;

   public:
    Registry();

    int getA();
    void setA(int);

    int getX();
    void setX(int);

    int getL();
    void setL(int);

    int getB();
    void setB(int);

    int getS();
    void setS(int);

    int getT();
    void setT(int);

    int getF();
    void setF(int);

    int getPC();
    void setPC(int);

    int getSW();
    void setSW(int);

    int getReg(int);
    void setReg(int, int);
};

#endif