//----------------------------------------
//File: Board.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Board.hpp"
#include "Player.hpp"
//----------------------------------------

Board::Board() : towerCounter(0), currentPlayer(nullptr) {
    backBone[0] = backBone[1] = nullptr;
    for (int i = 2; i < 13; ++i) {backBone[i] = new Column(i);} //create each column
}

Board::~Board() {
    for (int i = 2; i < 13; ++i) { delete backBone[i]; }//delocate each column
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    towerCounter = 0;
    for (int i = 0; i < 3; ++i) { towerColumns[i] = 0; }
}

bool Board::move(int column) {
    if (column < 2 || column > 12) {cerr << "Invalid Column Number";}

    Column* targetColumn = backBone[column];

    if (targetColumn == nullptr) {cerr << "Column " + to_string(column) + " is not initialized.";}

    // Attempt to start a tower or move markers
    if (!targetColumn->startTower(currentPlayer)) {
        if (!targetColumn->move()) {cout << "No valid moves in column " << column << ".\n";return false;}
    }

    if (targetColumn->columnState() == EColStatus::pending) {cout << "Column " << column << " is now pending capture!\n";} //is column pending

    targetColumn->print(cout);// Print the updated column state
    return true;
}

void Board::stop() {

}

void Board::bust() {

}

ostream& Board::print(std::ostream& os) const {
    for (int i = 2; i < 13; ++i) {os << *backBone[i];}
    return os;
}

ostream& operator << (ostream& os, Board& board){return board.print(os);}