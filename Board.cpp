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
    for (int & towerColumn : towerColumns) {towerColumn = 0;}
}

bool Board::move(int column) {
    if (column < 2 || column > 12) {cerr << "Invalid Column Number"; return false;}

    Column* targetColumn = backBone[column];

    if (targetColumn == nullptr) {cerr << "Column " + to_string(column) + " is not initialized."; return false;}

    if (!targetColumn->startTower(currentPlayer)) { //start tower or move markers
        if (!targetColumn->move()) {cout << "No valid moves in column " << column << ".\n";return false;}
    }

    return true;
}

void Board::stop() {
    if (currentPlayer == nullptr) {cout << "No current player to stop.\n";return;}

    //attempt to capture pending cols
    for (int k= 2; k <= 12; ++k) {
        Column* column = backBone[k];
        if (column != nullptr && column->getState() == EColStatus::pending) {
            column->stop(currentPlayer);
            if (column->getState() == EColStatus::captured) {
                cout << currentPlayer->getName() << " has captured column " << k << "!\n";
            }
        }
    }
    currentPlayer = nullptr; //end turn
}

void Board::bust() {
    if (currentPlayer == nullptr) {cout << "No current player to bust.\n";return;}

    for (int k = 2; k <= 12;  ++k ) {//reset columns where markers were
        if (backBone[k] != nullptr && backBone[k]->getState() != EColStatus::captured) {backBone[k]->bust();}
    }
    currentPlayer = nullptr; //end player turn
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
