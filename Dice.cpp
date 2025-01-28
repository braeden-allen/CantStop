//----------------------------------------
//File: Dice.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
//----------------------------------------

Dice::Dice(int n){
    nDice = n;
    dieValues = new int[nDice]; //new array for Die Values
    srand(time(NULL)); //initialized random number generator
}

Dice::~Dice(){
    delete [] dieValues; //delete dynamic memory of Die Values
}

ostream& Dice::print(ostream& outfile){

    outfile << "Die Values: ";
    for (int k = 0; k < nDice; k++) {
        outfile << dieValues[k] << " ";
    }
    outfile << endl;
    return outfile;
}

const int* Dice::roll(){
    for (int k = 0; k < nDice; k++) {
        dieValues[k] = rand() % 6 + 1;  // Assign a random number between 1 and 6
    }
    return dieValues;
}