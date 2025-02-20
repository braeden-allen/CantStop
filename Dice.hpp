//----------------------------------------
//File: Dice.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
//----------------------------------------

using namespace std;

class Dice {
    private:
        int nDice;
        int* dieValues;
    public:
        Dice(int n);
        ~Dice();
        ostream& print(ostream& outfile);
        const int* roll();
};

inline ostream& operator << ( ostream& outfile, Dice& dice){return dice.print(outfile);}