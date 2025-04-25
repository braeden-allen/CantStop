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

bool CSDice::validateDiceChars(char d1, char d2) const {
    const char* valid = "abcd";
    d1 = tolower(d1); d2 = tolower(d2);
    if (d1 == d2) throw DuplicateSlot(d1);
    if (!strchr(valid, d1)) throw BadSlot(d1);
    if (!strchr(valid, d2)) throw BadSlot(d2);
    return true;
}

void CSDice::calculatePairs(char d1, char d2) { //helper function to modularize
    pairTotals[0] = dieValues[d1-'a'] + dieValues[d2-'a'];
    pairTotals[1] = 0;
    for (int k = 0; k < 4; ++k) {
        if (k != (d1-'a') && k != (d2-'a')) pairTotals[1] += dieValues[k];
    }
}

const int* CSDice::roll() {
    Dice::roll();
    cout << "\nDice values:\n" << *this << endl;

    while (true) {
        try {
            cout << "Choose two dice (e.g., ab): ";
            char d1, d2;
            cin >> d1;
            if (cin.peek() == '\n') d2 = d1; else cin >> d2;

            validateDiceChars(d1, d2);
            calculatePairs(d1, d2);

            cout << "\nPairs: " << pairTotals[0]
                 << " & " << pairTotals[1] << "\n" << endl;
            return pairTotals;
        }
        catch (const BadChoice& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            e.print();
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
        throw runtime_error("End of test file reached or invalid format");
    }

    //store values
    for (int k = 0; k < 4; ++k) {dieValues[k] = rollValues[k];}
    pairSum[0] = dieValues[0] + dieValues[1];  // ab pair
    pairSum[1] = dieValues[2] + dieValues[3];  // cd pair
    lastAction = action;

    if (lastAction == "BADSLOT") throw BadSlot('a');
    if (lastAction == "DUPSLOT") throw DuplicateSlot('a');
    if (lastAction == "BADCHOICE") throw BadChoice('a');

    // Validate normal actions (without std::set)
    if (!isValidAction(lastAction)) {
        throw runtime_error("Invalid action in test file: " + lastAction);
    }
    logRollResults();
    return pairSum;
}

bool FakeDice::isValidAction(const string& action) const {
    return action == ROLL_ACTION || action == STOP_ACTION || action == QUIT_ACTION ||
           action == "BADSLOT" || action == "DUPSLOT" || action == "BADCHOICE";
}

void FakeDice::logRollResults() const {
    cout << "=== TEST MODE ===" << endl;
    cout << "Dice: ";
    for (int k = 0; k < 4; ++k) {
        cout << char('a' + k) << ":" << dieValues[k] << " ";
    }
    cout << "\nPairs: " << pairSum[0] << " & " << pairSum[1] << endl;
    cout << "Action: " << lastAction << endl << endl;
}

bool FakeDice::readNextRoll(int* values, string& action) {
    string line;
    if (!getline(file, line)) return false;

    istringstream iss(line);
    for (int k = 0; k < 4; ++k) {
        if (!(iss >> values[k]) || values[k] < 1 || values[k] > 6) {
            return false;  // Validate die values
        }
    }
    return !!(iss >> action);  // Extract action
}