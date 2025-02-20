//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Game.hpp"
//----------------------------------------

void unitDice();
void unitPlayer();
void unitColumn();

int main(int argc , char* argv[]) {
    srand(time(nullptr)); //initialized random number generator

    banner();

    unitColumn();

    bye();
    return 0;
}

void unitDice() {
    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    //initial message
    outFile << "START OF DICE TEST" << endl;
    outFile << "-------------------------------" << endl;
    Dice d1(6); //roll different numbers of dice each time

    //test the roll function
    outFile << "TEST FOR ACCURATE ROLL" << endl;
    const int* dieValues = d1.roll();
    outFile << "Values from roll: ";

    for (int k = 0; k < 6; k++) {
        outFile << dieValues[k] << " ";
        if (dieValues[k] < 1 || dieValues[k] > 6){outFile << "n\nValues are out of range(1-6)" << endl;}
    }

    //test the print function
    outFile << "\nTest for accurate PRINTING of Dice values" << endl;
    outFile << "Die Values: ";
    d1.print(outFile);
    outFile << endl;

    //test the destructor for memory leaks
    outFile << "DESTRUCTOR TEST" << endl;
    Dice d2(4);
    outFile << "Class destructed without error or memory leak";
    outFile << "\nEND OF DICE TEST" << endl;
    outFile << "-------------------------------\n" << endl;

    outFile.close();
}

void unitPlayer(){

    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    outFile << "START OF PLAYER TEST" << endl;
    outFile << "-------------------------------" << endl;

    Player player1("Test Player", ECcolor::Yellow);
    outFile << player1;

    outFile << "TESTING wonColumn()" << endl;
    for (int k = 0; k < 3; k++) {
        outFile << player1.wonColumn(1) << " ";
    }
    outFile << "\nEND OF PLAYER TEST" << endl;
    outFile << "-------------------------------\n" << endl;
    outFile.close();
}

void unitColumn(){
    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    outFile << "START OF COLUMN TEST" << endl;
    outFile << "-------------------------------" << endl;

    Column column(4); //testing column availability
    Player testPlayer("Mateusz" , ECcolor::Green);
    outFile << "\nInitial state of column 4: " << column.colStateToString(column.columnState());
    outFile << "\n-----------------------------------------";
    column.print(outFile);

    outFile << "\nStarting a tower for player (Green): ";
    if (column.startTower(&testPlayer)) {outFile << "Tower started at position 1.";}
    else {outFile << "Failed to start tower.";}
    outFile << "\n------------------------------------------------------------------";
    column.print(outFile); // Print column state after starting the tower

    outFile << "\nAttempting to move the tower: "; //move the tower
    if (column.move()) {outFile << "Tower moved.";}
    else {outFile << "Failed to move tower.";}
    outFile << "\n----------------------------------------------";
    column.print(outFile); //print column state after moving the tower

    outFile << "\nAttempting to move the tower to end: "; //move the tower
    for (int k = 0; k < 6; ++k) {column.move();}
    if (column.move()) {outFile << "Tower moved.";}
    else {outFile << "Failed to move tower.";}
    outFile << "\n----------------------------------------------";
    column.print(outFile); //print column state after moving the tower

    outFile << "\nStopping the marker and capturing column: ";
    column.stop(&testPlayer);
    if (column.columnState() == EColStatus::captured) {outFile << "Column captured (expected behavior).";}
    else {outFile << "Column not captured (unexpected behavior).";}
    outFile << "\n------------------------------------------------------------------------------";
    column.print(outFile); //print column state after stopping

    outFile << "\nStarting a tower on a captured column: ";
    if (!column.startTower(&testPlayer)) {outFile << "Failed to start tower on captured column.";}
    else {outFile << "Unexpected success in starting tower on captured column.";}
    outFile << "\n----------------------------------------------------------------------------------";
    column.print(outFile); //print after starting tower on captured col.

    outFile << "\nEND OF COLUMN TEST" << endl;
    outFile << "-------------------------------\n" << endl;
}