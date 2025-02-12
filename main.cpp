//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
#include "Player.hpp"
#include "tools.hpp"
#include "Column.hpp"
//----------------------------------------

void unitDice();
void unitPlayer();
void unitColumn();

int main(int argc , char* argv[]) {
    srand(time(NULL)); //initialized random number generator

    banner();

    // unitDice();
    // unitPlayer();
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

    Column column(7); //testing column availability
    outFile << "State of column: " << column.colStateToString(column.columnState()) << endl;

    Player testPlayer("Mateusz" , ECcolor::Green); //testing a tower start
    outFile << "Test Tower start on Col. 7: ";
    if (column.startTower(&testPlayer) == 1){outFile << "Tower Started" << endl;}

    outFile << "Testing move on Col. 7: "; //test move()
    if(column.move() == 1){outFile << "Successful Move" << endl;}

    outFile << "Stopping marker and returning position: "; //showing marker has moved
    column.stop(&testPlayer);


}