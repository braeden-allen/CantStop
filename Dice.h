//----------------------------------------
//File: Dice.h
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
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
        int getnDice();
};

inline ostream& operator << ( ostream& outfile, Dice& dice){
    return dice.print(outfile);
}