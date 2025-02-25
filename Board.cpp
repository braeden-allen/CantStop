//----------------------------------------
//File: Board.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Board.hpp"
#include "Player.hpp


Board::Board() : towerCounter(0), currentPlayer(nullptr) {
    backBone[0] = backBone[1] = nullptr;

    //column
    for (int i = 2; i < 13; ++i) {
        backBone[i] = new Column(i); 
    }
}

Board::~Board() {
    for (int i = 2; i < 13; ++i) {
        //this delocates each column
        delete backBone[i];  
}

void Board::print(std::ostream& os) const {
    for (int i = 2; i < 13; ++i) {
        os << *backBone[i];  
    }
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    towerCounter = 0;  
    for (int i = 0; i < 3; ++i) {
        towerColumns[i] = 0;  /
}

// bool Board::move(int column) {
// }

// void Board::stop() {

// }

// void Board::bust() {

// }

std::ostream& operator<<(std::ostream& os, const Board& board) {
    board.print(os);  
    return os;
}
