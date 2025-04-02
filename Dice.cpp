//----------------------------------------
//File: Dice.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Dice.hpp"

//MACRO, need this file
#define FAKE_DICE_FILE "fake_dice.txt"

//------------------------------------------------------
// Dice Base Class Implementation
//------------------------------------------------------
Dice::Dice(int n)
    : nDice(n)
{
    dieValues = new int[nDice];
}

Dice::~Dice(){
    delete [] dieValues;
}

const int* Dice::roll(){
    for (int k = 0; k < nDice; k++) {
        dieValues[k] = rand() % 6 + 1;
    }
    return dieValues;
}

CSDice::~CSDice(){
    //nothing extra needed 
}

const int* CSDice::roll(){
    Dice::roll();

    cout << "Dice values:" << endl;
    cout << "a: " << dieValues[0] << "  "
         << "b: " << dieValues[1] << "  "
         << "c: " << dieValues[2] << "  "
         << "d: " << dieValues[3] << endl;

    int index1, index2;
    bool validInput = false;
    do {
        cout << "Enter two distinct indices (0-3) for your chosen pair: ";
        if(!(cin >> index1 >> index2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter two integers." << endl;
            continue;
        }
        if(index1 < 0 || index1 >= 4 || index2 < 0 || index2 >= 4 || index1 == index2){
            cout << "Indices must be between 0 and 3 and must be different. Try again." << endl;
        } else {
            validInput = true;
        }
    } while(!validInput);

    pairTotals[0] = dieValues[index1] + dieValues[index2];

    int totalAll = dieValues[0] + dieValues[1] + dieValues[2] + dieValues[3];
    pairTotals[1] = totalAll - pairTotals[0];


    cout << "Chosen pair total: " << pairTotals[0] << endl;
    cout << "Remaining pair total: " << pairTotals[1] << endl;

    // Return pointer to pairTotals array.
    return pairTotals;
}

//------------------------------------------------------
// FakeDice Derived Class Implementation
//------------------------------------------------------
FakeDice::FakeDice() : CSDice() {
    file.open(FAKE_DICE_FILE);
    if (!file.is_open()) {
        fatal("Failed to open the fake dice file");
    }
}

FakeDice::~FakeDice() {
    //need to close file
    file.close();
}

const int* FakeDice::roll() {
    int diceValues[4];
    string action;

    if(!(file >> diceValues[0] >> diceValues[1] >> diceValues[2] >> diceValues[3] >> action)){
        fatal("Failed to reading fake dice");
    }

    cout << "Dice values:" << endl;
    cout << "a: " << diceValues[0] << "  "
         << "b: " << diceValues[1] << "  "
         << "c: " << diceValues[2] << "  "
         << "d: " << diceValues[3] << endl;

    pairTotals[0] = diceValues[0] + diceValues[1];
    pairTotals[1] = diceValues[2] + diceValues[3];

    cout << "Chosen pair total: " << pairTotals[0] << endl;
    cout << "Remaining pair total: " << pairTotals[1] << endl;

    return pairTotals;
};