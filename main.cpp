//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Board.hpp"
//----------------------------------------

void unitDice();
void unitPlayer();
void unitColumn();
void unitGame();
void unitBoard();

int main(int argc , char* argv[]) {
    srand(time(nullptr)); //initialized random number generator

    banner();
    unitBoard();
    bye();
    return 0;
}

void unitDice() {
    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    fbanner(outFile);

    //initial message
    outFile << "\nSTART OF DICE TEST" << endl;
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

    fbanner(outFile);

    outFile << "\nSTART OF PLAYER TEST" << endl;
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

    fbanner(outFile);

    outFile << "\nSTART OF COLUMN TEST" << endl;
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

void unitGame(){

    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    fbanner(outFile);

    outFile << "\nSTART OF GAME TEST" << endl;
    outFile << "-------------------------------" << endl;

    Game game;

    outFile << "ROLLING 4 DICE" << endl;
    game.getDice()->roll();
    outFile << "Die results: " << endl;
    game.getDice()->print(outFile);
    outFile << endl;

    outFile << "\nPLAYER DETAILS\n" << endl;
    outFile << game.getP1() << endl;
    outFile << game.getP2() << endl;

    outFile << "COLUMN DETAILS" << endl; //print out the column status
    game.getCol2().print(outFile);
    game.getCol7().print(outFile);

    game.getCol7().startTower(&game.getP1());//place tower in col7

    outFile << "\nCOLUMN AFTER COL7 TOWER START" << endl;
    game.getCol7().print(outFile);

    outFile << "\nCOLUMN AFTER COL2 TOWER START" << endl;
    game.getCol2().startTower(&game.getP2());
    game.getCol2().print(outFile);

    outFile << "\nCOLUMN DURING MOVES" << endl;
    game.getCol2().move();
    game.getCol2().print(outFile);
    game.getCol2().move();
    game.getCol2().print(outFile);//should print pending

    outFile << "\nCOLUMN AFTER P2 STOPS" << endl;
    game.getCol2().stop(&game.getP2()); //actual capturing of column
    game.getCol2().print(outFile); //should print captured

    outFile << "\nEND OF GAME TEST" << endl;
    outFile << "-------------------------------\n" << endl;
}

void unitBoard(){
    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    fbanner(outFile);

    outFile << "\nSTART OF BOARD TEST" << endl;
    outFile << "-------------------------------" << endl;

    Board board;
    Game game;

    outFile << "ROLLING 4 DICE" << endl;
    game.getDice()->roll();
    outFile << "Die results: " << endl;
    game.getDice()->print(outFile);
    outFile << endl;

    outFile << "\nPLAYER DETAILS\n" << endl;
    outFile << game.getP1() << endl;
    outFile << game.getP2() << endl;

    board.print(outFile);

    outFile << "\nEND OF BOARD TEST" << endl;
    outFile << "-------------------------------\n" << endl;
}