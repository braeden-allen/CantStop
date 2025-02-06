//----------------------------------------
//File: Dice.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
//----------------------------------------

Dice::Dice(int n){
    nDice = n;
    dieValues = new int[nDice]; //new array for Die Values
}

Dice::~Dice(){
    delete [] dieValues; //delete dynamic memory of Die Values
}

ostream& Dice::print(ostream& outfile){
    for (int k = 0; k < nDice; k++) {
        outfile << dieValues[k] << " "; //die values seperated by a space
    }
    return outfile;
}

const int* Dice::roll(){
    for (int k = 0; k < nDice; k++) {
        dieValues[k] = (rand() % 6 + 1);  // Results between 1 and 6
    }
    return dieValues;
}