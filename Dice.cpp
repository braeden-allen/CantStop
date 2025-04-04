//----------------------------------------
//File: Dice.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Dice.hpp"

//------------------------------------------------------
// Dice Base Class Implementation
//------------------------------------------------------
Dice::Dice(int n) : nDice(n) {dieValues = new int[nDice];}

Dice::~Dice() {delete [] dieValues;}

const int* Dice::roll(){
    for (int k = 0; k < nDice; k++) {dieValues[k] = (rand() % 6 + 1);}
    return dieValues;
}

ostream& Dice::print(ostream& outfile) {
    for (int k = 0; k < nDice; ++k) {
        outfile << (char)('a' + k) << ":" << dieValues[k] << " ";
    }
    return outfile;
}

//------------------------------------------------------
// Derived CSDice Class Implementation
//------------------------------------------------------
CSDice::CSDice() : Dice(4){} //CS uses 4 dice

const int* CSDice::roll(){

    Dice::roll(); //Roll random values

    cout << "Dice values:" << endl;
    cout << "a: " << dieValues[0] << "  "
         << "b: " << dieValues[1] << "  "
         << "c: " << dieValues[2] << "  "
         << "d: " << dieValues[3] << endl;

    char die1 , die2;
    bool validInput = false;
    do {
        cout << "Choose first pair (e.g., ab): ";
        cin >> die1 >> die2;

        // Validate input
        die1 = tolower(die1);
        die2 = tolower(die2);

        if (die1 < 'a' || die1 > 'd' ||
            die2 < 'a' || die2 > 'd' ||
            die1 == die2) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please choose two different letters a-d.\n";
        } else {
            validInput = true;
        }
    } while (!validInput);

    int index1 = die1 - 'a';
    int index2 = die2 - 'a';
    pairTotals[0] = dieValues[index1] + dieValues[index2];

    //second pair is sum of remaining two
    pairTotals[1] = 0;
    for (int k = 0; k < nDice; ++k) {
        if (k != index1 && k != index2) {pairTotals[1] += dieValues[k];}
    }

    cout << "First pair total: " << pairTotals[0] << endl;
    cout << "Second pair total: " << pairTotals[1] << endl;

    return pairTotals;
}

//------------------------------------------------------
// FakeDice Derived Class Implementation
//------------------------------------------------------
FakeDice::FakeDice(){
    file.open(FAKE_DICE_FILE);
    if (!file.is_open()) {fatal("Failed to open the fake dice file");}
}

const int* FakeDice::roll() {
    int rollValues[4];
    if (!readNextRoll(rollValues)) {fatal("Failed to read from fake dice file");}

    //copy to dieValues for print
    for (int k = 0; k < 4; ++k) {dieValues[k] = rollValues[k];}

    //Pair Calculation
    pairSum[0] = rollValues[0] + rollValues[1];
    pairSum[1] = rollValues[2] + rollValues[3];

    cout << "Fake dice: " << *this << endl;
    cout << "First pair total: " << pairSum[0] << endl;
    cout << "Second pair total: " << pairSum[1] << endl;

    return pairSum;
}

bool FakeDice::readNextRoll(int *values) {
    string line;
    if (!getline(file, line)) {return false;}

    istringstream iss(line);
    for (int k = 0; k < 4; ++k) {if (!(iss >> values[k])) return false;}
    return true;
};