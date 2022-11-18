#include "Machine.h"

#ifndef SICXE_REGISTRY_H
#define SICXE_REGISTRY_H

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
    void setA(int val);

    int getX();
    void setX(int val);

    int getL();
    void setL(int val);

    int getB();
    void setB(int val);

    int getS();
    void setS(int val);

    int getT();
    void setT(int val);

    int getF();
    void setF(int val);

    int getPC();
    void setPC(int val);

    int getSW();
    void setSW(int val);

    int getReg(int reg);
    void setReg(int reg, int val);
};

#endif