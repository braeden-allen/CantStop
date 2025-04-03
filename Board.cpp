//----------------------------------------
//File: Board.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Board.hpp"
//----------------------------------------

Board::Board() : currentPlayer(nullptr) {
    towerCounter = 0;
    for (int & towerColumn : towerColumns) {towerColumn = -1;}
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
    for (int i = 0; i < towerCounter; i++) {
        if (towerColumns[i] == column) {
            bool moved = col->move();
            if (!moved) {

                bust(); //if move failed, treat it as a bust
            }
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
    for (int i = 0; i < towerCounter; i++) {
        backBone[towerColumns[i]]->stop(currentPlayer);  // Convert towers to permanent
    }
    towerCounter = 0;  // Reset counter
}

void Board::bust() {
    for (int i = 0; i < towerCounter; i++) {
        backBone[towerColumns[i]]->bust();  // Clear each active tower
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
