//----------------------------------------
//File: Game.hpp
//Authors: Braeden & Mateusz
//----------------------------------------
#pragma once
#include "Board.hpp"
#include "Dice.hpp"
#include "CList.hpp"
#include <memory> //for unique_ptr
#include "exceptions.hpp"
//----------------------------------------

class Game {

private:
    Board board;
    CList players;
    CSDice* dice;
    
    //check the new players name and color against the existing players that were confirmed before
    void checkPlayerData(const string& newName, char newColor);

public:
        Game();
        ~Game() {delete [] dice;};
        Player getNewPlayer();
        void oneTurn(Player* pp);
        bool addPlayer();
        void playGame();
};
