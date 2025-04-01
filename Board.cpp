// //----------------------------------------
// //File: Board.cpp
// //Authors: Braeden
// //----------------------------------------
// #include "Board.hpp"
// //----------------------------------------

// Board::Board() : currentPlayer(nullptr) {
//     towerCounter = 0;
//     for (k = 0; k < 3; ++k) {towerColumns[k] = -1;}
//     backBone[0] = backBone[1] = nullptr;

//     for (int k = 2; k < 13;  ++k ) {backBone[k] = new Column(k);} //create each column
// }

// Board::~Board() {
//     for (int k = 2; k < 13;  ++k ) { delete backBone[k]; } //delocate each column
// }

// Column* Board::getColumn(int colNum) {
//     if (colNum < 2 || colNum > 12) return nullptr; //check validity
//     return backBone[colNum];
// }

// void Board::startTurn(Player* player) {
//     currentPlayer = player;
//     towerCounter = 0;
//     for (int k = 0; k < 3;  ++k ) {towerColumns[k] = 0;}
// }

// bool Board::move(int column) {
//     if (column < 2 || column > 12) {cerr << "Invalid Column Number"; return false;}

//     Column* targetColumn = backBone[column];

//     if (targetColumn == nullptr) {cerr << "Column " + to_string(column) + " is not initialized."; return false;}

//     if (!targetColumn->startTower(currentPlayer)) { //start tower or move markers
//         if (!targetColumn->move()) {cout << "No valid moves in column " << column << ".\n";return false;}
//     }

//     if (targetColumn->getState() == EColStatus::pending) {cout << "Column " << column << " is now pending capture!\n";} //is column pending

//     targetColumn->print(cout); //print the updated column state
//     return true;
// }

// void Board::stop() {
//     if (currentPlayer == nullptr) {cout << "No current player to stop.\n";return;}

//     //attempt to capture pending cols
//     for (int k= 2; k <= 12; ++k) {
//         Column* column = backBone[k];
//         if (column != nullptr && column->getState() == EColStatus::pending) {
//             column->stop(currentPlayer);
//             if (column->getState() == EColStatus::captured) {
//                 cout << currentPlayer->getName() << " has captured column " << k << "!\n";
//             }
//         }
//     }
//     currentPlayer = nullptr; //end turn
// }

// void Board::bust() {
//     if (currentPlayer == nullptr) {cout << "No current player to bust.\n";return;}
//     cout << currentPlayer->getName() << " has busted!\n";

//     for (int k = 2; k <= 12;  ++k ) {//reset columns where markers were
//         if (backBone[k] != nullptr && backBone[k]->getState() != EColStatus::captured) {backBone[k]->bust();}
//     }
//     currentPlayer = nullptr; //end player turn
// }

// ostream& Board::print(std::ostream& os) const {
//     for (int k = 2; k < 13;  ++k ) {
//         Column* column = backBone[k];
//         if (column != nullptr) {
//             column->print(os); //use Column's print function
//         }
//     }
//     return os;
// }




//----------------------------------------
// File: Board.cpp
// Authors: Braeden, Mateusz
//----------------------------------------

#include "Board.hpp"
#include <iostream>
#include <string>

//defining DEBUG_PRINT 
#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

Board::Board() : currentPlayer(nullptr), towerCounter(0) {
    //only defniing 3 towers manually
    towerColumns[0] = -1;
    towerColumns[1] = -1;
    towerColumns[2] = -1;

    // The first two positions of backBone are not used.
    backBone[0] = backBone[1] = nullptr;
    
    // Create each column for column numbers 2 through 12.
    for (int k = 2; k < 13; ++k) {backBone[k] = new Column(k);}
}

Board::~Board() {
    //deallocate each column
    for (int k = 2; k < 13; ++k) {
        delete backBone[k];
    }
}

Column* Board::getColumn(int colNum) {
    if (colNum < 2 || colNum > 12)
        return nullptr;
    return backBone[colNum];
}

void Board::startTurn(Player* player) {
    currentPlayer = player;
    towerCounter = 0;
    //reset the towerColumns
    towerColumns[0] = -1;
    towerColumns[1] = -1;
    towerColumns[2] = -1;
}

bool Board::move(int column) {
    //assume this is passed column
    Column* targetColumn = backBone[column];

    if (!targetColumn->startTower(currentPlayer)) {
        if (!targetColumn->move()) {
            DEBUG_PRINT("No valid moves in column " + std::to_string(column) + ".");
            return false;
        }
    }

    if (targetColumn->getState() == EColStatus::pending) {
        DEBUG_PRINT("Column " + std::to_string(column) + " is now pending capture!");
    }

    targetColumn->print(std::cout);
    return true;
}

void Board::stop() {
    if (currentPlayer == nullptr) {
        DEBUG_PRINT("No current player to stop.");
        return;
    }
    
    for (int k = 2; k < 13; ++k) {
        Column* column = backBone[k];
        if (column != nullptr && column->getState() == EColStatus::pending) {
            column->stop(currentPlayer);
            
            if (column->getState() == EColStatus::captured) {
                DEBUG_PRINT(currentPlayer->getName() + " has captured column " + std::to_string(k) + "!");
            }
        }
    }
    
    //end the turn
    currentPlayer = nullptr;
}

void Board::bust() {
    if (currentPlayer == nullptr) {
        DEBUG_PRINT("No current player to bust.");
        return;
    }
    
    DEBUG_PRINT(currentPlayer->getName() + " has busted!");
    
    //reset the columns when they are not captured
    for (int k = 2; k < 13; ++k) {
        if (backBone[k] != nullptr && backBone[k]->getState() != EColStatus::captured)
            backBone[k]->bust();
    }
    
    //end the player turn
    currentPlayer = nullptr;
}

std::ostream& Board::print(std::ostream& os) const {
    for (int k = 2; k < 13; ++k) {
        if (backBone[k] != nullptr)
            backBone[k]->print(os);
    }
    return os;
}
