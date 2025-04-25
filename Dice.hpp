//----------------------------------------
//File: Dice.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "exceptions.hpp"
#define FAKE_DICE_FILE "/home/braeden/CSCI 4526/CantStop/fake_dice.txt"
#define ROLL_ACTION "ROLL"
#define STOP_ACTION "STOP"
#define QUIT_ACTION "QUIT"
//----------------------------------------

using namespace std;

class Dice {
protected:
    int nDice;
    int* dieValues;
public:
    Dice() : Dice(6){} //default constructor
    explicit Dice(int n);
    //using virtual to ensure proper cleanup after the derived class
    virtual ~Dice();
    virtual const int* roll();
    ostream& print(ostream& outfile);
};

class CSDice : public Dice {
protected:
    int pairTotals[2]{};
public:
    CSDice();
    ~CSDice() override = default;
    const int* roll() override;

    [[nodiscard]] bool validateDiceChars(char d1, char d2) const;

    void calculatePairs(char d1, char d2);
};

class FakeDice : public CSDice {
private:
    ifstream file;
    int pairSum[2]{};
    bool readNextRoll(int* values, string& action);
public:
    FakeDice();
    ~FakeDice() override { if (file.is_open()) fatal("File Can't Be Opened");}
    const int* roll() override;
    string lastAction;
    void logRollResults() const;
    bool isValidAction(const string &action) const;
};
inline ostream& operator << ( ostream& outfile, Dice& dice){return dice.print(outfile);}