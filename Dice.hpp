//----------------------------------------
//File: Dice.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
//----------------------------------------

using namespace std;

class Dice {
    protected:
        int nDice;
        int* dieValues;
    public:
        Dice(int n);
        //using virtual to ensure proper clean up after the derived class
        virtual ~Dice();
        virtual ostream& print(ostream& outfile);
        virtual const int* roll();
};

inline ostream& operator << ( ostream& outfile, Dice& dice){return dice.print(outfile);}

class CSDice : public Dice {
    protected: 
        int pairTotals[2];
    public:
        CSDice();
        //new virtual
        virtual ~CSDice();
        virtual const int* roll();
};

//new for the FakeDice
class FakeDice : public CSDice {
private:
    ifstream file;  
public:
    FakeDice();                         
    virtual ~FakeDice();                 
    virtual const int* roll() override;  
};