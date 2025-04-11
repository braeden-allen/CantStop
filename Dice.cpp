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

const int* CSDice::roll() {
    Dice::roll(); // Roll random values

    cout << "\nDice values:\n";
    print(cout);
    cout << endl;

    while (true) {
        cout << "Choose two different dice (e.g., ab): ";
        try {
            char die1, die2;
            cin >> die1;

            if (cin.peek() == '\n') {
                die2 = die1; // Will trigger duplicate check
            } else {
                cin >> die2;
            }

            die1 = tolower(die1);
            die2 = tolower(die2);

            const char* validOptions = "abcd";

            if (die1 == die2) throw DuplicateSlot(die1);
            if (!strchr(validOptions, die1)) throw BadSlot(die1);
            if (!strchr(validOptions, die2)) throw BadSlot(die2);

            // Calculate pairs
            pairTotals[0] = dieValues[die1-'a'] + dieValues[die2-'a'];
            pairTotals[1] = 0;
            for (int k = 0; k < nDice; ++k) {
                if (k != (die1-'a') && k != (die2-'a')) {
                    pairTotals[1] += dieValues[k];
                }
            }

            cout << "\nFirst pair total: " << pairTotals[0]
                 << "\nSecond pair total: " << pairTotals[1] << "\n" << endl;
            return pairTotals;
        }
        catch (const BadChoice& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n";
            e.print();
            cout << endl;
        }
    }
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
    string action;

    if (!readNextRoll(rollValues, action)) {
        fatal("Failed to read from fake dice file or end of file reached");
    }

    // Copy to dieValues for printing
    for (int k = 0; k < 4; ++k) {
        dieValues[k] = rollValues[k];
    }

    // Calculate pairs (first two and last two)
    pairSum[0] = rollValues[0] + rollValues[1];
    pairSum[1] = rollValues[2] + rollValues[3];
    lastAction = action;

    cout << "Fake dice roll: " << *this << endl;
    cout << "Action: " << lastAction << endl;

    if (lastAction == "BADSLOT"){
        throw BadSlot('a');
    }else if (lastAction == "DUPSLOT"){
        throw DuplicateSlot('a');
    }else if (lastAction == "BADCHOICE"){
        throw BadSlot('x');
    }else if (lastAction != ROLL_ACTION && lastAction != STOP_ACTION){
        fatal("invalid command in fake_dice.txt");
    }
    return pairSum;
}

bool FakeDice::readNextRoll(int* values, string& action) {
    string line;
    if (!getline(file, line)) return false;
        istringstream iss(line);
        for (int k = 0; k < 4; ++k) {
            if (!(iss >> values[k])) return false;
        }
        iss >> action;
        if (action != ROLL_ACTION && action != STOP_ACTION) {
            return false;
        }
        return true;
}