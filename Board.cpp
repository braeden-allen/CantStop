//----------------------------------------
//File: Board.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Board.hpp"
//----------------------------------------

Board::Board() : currentPlayer(nullptr) {
    towerCounter = 0;
    towerColumns[0] = -1;
    towerColumns[1] = -1;
    towerColumns[2] = -1;
    backBone[0] = backBone[1] = nullptr;

    for (int k = 2; k < 13;  ++k ) {backBone[k] = new Column(k);} //create each column
}

Board::~Board() {
    for (int k = 2; k < 13;  ++k ) { delete backBone[k]; } //delocate each column
}

Column* Board::getColumn(int colNum) {
    if (colNum < 2 || colNum > 12) return nullptr; //check validity
    return backBone[colNum];
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    towerCounter = 0;
}

bool Board::move(int column) {
    Column* col = getColumn(column);
    if (!col) return false;

    // First check if this column already has a tower
    for (int k = 0; k < towerCounter; k++) {
        if (towerColumns[k] == column) {
            bool moved = col->move();
            if (!moved) bust(); //if the move fails, treat it as a bust
            return moved;
        }
    }

    if (towerCounter >= 3) return false; //new tower case

    if (col->startTower(currentPlayer)) {
        towerColumns[towerCounter++] = column;
        return true;
    }
    return false;
}

void Board::stop() {
    for (int k = 0; k < towerCounter; ++k) {
        backBone[towerColumns[k]]->stop(currentPlayer);  //towers->tiles
    }
    towerCounter = 0;  // Reset counter
}

void Board::bust() {
    for (int k = 0; k < towerCounter; ++k) {
        backBone[towerColumns[k]]->bust();  //clear towers
    }
    towerCounter = 0;  // Reset counter
}

ostream& Board::print(std::ostream& os) const {
    for (int k = 2; k < 13;  ++k ) {
        Column* column = backBone[k];
        if (column != nullptr) {
            column->print(os); //use Column's print function
        }
    }
    return os;
}