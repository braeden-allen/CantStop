//----------------------------------------
//File: Dice.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#define FAKE_DICE_FILE "fake_dice.txt"
//----------------------------------------


using namespace std;

class Dice {
protected:
    int nDice;
    int* dieValues;
public:
    Dice() : Dice(6){} //default constructor
    Dice(int n);
    //using virtual to ensure proper clean up after the derived class
    virtual ~Dice();
    virtual const int* roll();
    ostream& print(ostream& outfile);
};

class CSDice : public Dice {
protected:
    int pairTotals[2]{};
public:
    CSDice();
    virtual ~CSDice() = default;
    const int* roll() override;
<<<<<<< Updated upstream
=======

    bool validateDiceChars(char d1, char d2) const;

    void calculatePairs(char d1, char d2);
>>>>>>> Stashed changes
};

class FakeDice : public CSDice {
private:
    ifstream file;
    int pairSum[2]{};
    bool readNextRoll(int* values);
public:
    FakeDice();
    ~FakeDice() override { if (file.is_open()) fatal("File Can't Be Opened");}
    const int* roll() override;
};
inline ostream& operator << ( ostream& outfile, Dice& dice){return dice.print(outfile);}