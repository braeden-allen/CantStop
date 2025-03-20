//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden
//----------------------------------------
#include "Game.hpp"
//----------------------------------------

void unitDice();
void unitPlayer();
void unitColumn();
void unitGame();
void unitBoard();

int main(int argc , char* argv[]) {
    srand(time(nullptr)); //initialized random number generator
    Game game;

    banner();
    game.oneTurn(&game.players[0]);
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
    outFile << "\nInitial state of column 4: " << column.colStateToString(column.getState());
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
    if (column.getState() == EColStatus::captured) {outFile << "Column captured (expected behavior).";}
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
    game.dice->roll();
    outFile << "Die results: " << endl;
    game.dice->print(outFile);
    outFile << endl;

    outFile << "\nPLAYER DETAILS\n" << endl;
    outFile << game.players[0] << endl;
    outFile << game.players[1] << endl;

    outFile << "COLUMN DETAILS" << endl; //print out the column status

    game.board.getColumn(2)->print(outFile);
    game.board.getColumn(7)->print(outFile);

    outFile << "\nCOLUMN AFTER COL7 TOWER START" << endl;
    game.board.getColumn(7)->startTower(&game.players[0]);
    game.board.getColumn(7)->print(outFile);

    outFile << "\nCOLUMN AFTER COL2 TOWER START" << endl;
    game.board.getColumn(2)->startTower(&game.players[1]);
    game.board.getColumn(2)->print(outFile);

    outFile << "\nCOLUMN DURING MOVES" << endl;
    game.board.getColumn(2)->move();
    game.board.getColumn(2)->print(outFile);
    game.board.getColumn(2)->move();
    game.board.getColumn(2)->print(outFile);//should print pending

    outFile << "\nCOLUMN AFTER P2 STOPS" << endl;
    game.board.getColumn(2)->stop(&game.players[1]); //actual capturing of column
    game.board.getColumn(2)->print(outFile); //should print captured

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
    game.dice->roll();
    outFile << "Die results: " << endl;
    game.dice->print(outFile);
    outFile << endl;

    outFile << "\nPLAYER DETAILS\n" << endl;
    outFile << game.players[0] << endl;
    outFile << game.players[1] << endl;

    board.print(outFile);

    outFile << "\nSTARTING TOWERS ON COLUMNS 7,2" << endl;
    outFile << "-------------------------------" << endl;

    board.startTurn(&game.players[0]);
    board.getColumn(7)->startTower(&game.players[0]);
    board.getColumn(2)->startTower(&game.players[0]);

    outFile << "\nBOARD AFTER COL7 AND COL2 TOWER START" << endl;
    outFile << "-------------------------------" << endl;
    board.print(outFile);

    outFile << "\nCOLUMN AFTER CAPTURE (PENDING)" << endl;
    outFile << "-------------------------------" << endl;
    board.getColumn(2)->move();
    board.getColumn(2)->move();
    for (int k = 0; k < 12; ++k) {
        board.getColumn(7)->move();
    }
    board.print(outFile);

    outFile << "\nCOLUMN AFTER P1 STOPS" << endl;
    outFile << "-------------------------------" << endl;
    board.stop();
    board.print(outFile);

    outFile << "\nP2 STARTS AND MOVES (COL3 PENDING)" << endl; //look at col3 (pending)
    outFile << "-------------------------------" << endl;
    board.startTurn(&game.players[1]);
    board.getColumn(7)->startTower(&game.players[1]); //this will print an error message on the console
    board.getColumn(2)->startTower(&game.players[1]);
    board.getColumn(3)->startTower(&game.players[1]);
    for (int k = 0; k < 5; ++k) {
        board.getColumn(3)->move(); //move to end and set pending
    }
    board.print(outFile);

    outFile << "\nP2 BUSTS" << endl;
    outFile << "-------------------------------" << endl;
    board.bust();
    board.print(outFile);

    outFile << "\nPLAYER SCORES" << endl;
    outFile << "-------------------------------\n" << endl;

    outFile << "PLAYER 1 SCORE: "<< game.players[0].getScore() << endl;
    outFile << "PLAYER 2 SCORE: "<< game.players[1].getScore() << endl;

    outFile << "\nEND OF BOARD TEST" << endl;
    outFile << "-------------------------------\n" << endl;
}