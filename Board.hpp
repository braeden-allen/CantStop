//----------------------------------------
// File: Board.hpp
// Authors: Braeden & Mateusz
//----------------------------------------
#pragma once
#include "Column.hpp" //only include necessary dependencies
#include "Player.hpp" //needed for Player pointer
//----------------------------------------

class Board {
private:
    int towerCounter; //counter for towers
    int towerColumns[3]; //array to track tower columns
    Column* backBone[13]; //array of Column pointers
    Player* currentPlayer; //pointer to current player

public:

    Board();
    ~Board();

    Column* getColumn(int column);
    ostream& print(ostream& os) const;

    //gameplay methods
    void startTurn(Player* player);
    bool move(int column);
    void stop();
    void bust();
};
ostream& operator << (std::ostream& os, const Board& board);
