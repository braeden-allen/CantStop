//
// Created by braeden on 1/23/25.
//

#ifndef CANTSTOP_DICE_H
#define CANTSTOP_DICE_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Dice {
    private:
        int nDice;
        int* diceValues;
    public:
        Dice(int n){};
        ~Dice();
        ostream& print(ostream&);
        const int* roll();
};

inline ostream& operator << ( ostream&, Dice& );

#endif //CANTSTOP_DICE_H
