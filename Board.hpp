//----------------------------------------
//File: Board.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "Player.hpp"
#include "enums.hpp"
#include "Dice.hpp"
#include "Game.hpp"
//----------------------------------------

class Board {
    private:
        int towerCounter;                         
        int towerColumns[3];
        Column* backBone[13];
        Player* currentPlayer;                    

    public:
        Board();                                  
        ~Board();                                
        void print(std::ostream& os) const;      
        void startTurn(Player* player);           
        bool move(int column);                  
        void stop();                             
        void bust();                           
};

ostream& operator<<(std::ostream& os, const Board& board);