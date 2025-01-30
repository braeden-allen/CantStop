//----------------------------------------
//File: Dice.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
//----------------------------------------

Dice::Dice(int n) : nDice(n){
    dieValues = new int[nDice]; //new array for Die Values
    srand(time(NULL)); //initialized random number generator
}

Dice::~Dice(){
    delete [] dieValues; //delete dynamic memory of Die Values
}

int Dice::getnDice(){ //needed to include this in order for no memory overflow (shown by test case 1)
    return nDice;
}

ostream& Dice::print(ostream& outfile){
    for (int k = 0; k < nDice; k++) {
        outfile << dieValues[k] << " "; //print each die value seperated by a space
    }
    return outfile;
}

const int* Dice::roll(){
    for (int k = 0; k < nDice; k++) {
        dieValues[k] = (rand() % 6 + 1);  // Assign a random number between 1 and 6
    }
    return dieValues;
}