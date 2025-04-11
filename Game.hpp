//----------------------------------------
//File: Game.hpp
//Authors: Braeden & Mateusz
//----------------------------------------
#pragma once
#include "Board.hpp"
#include "Dice.hpp"
#include "CList.hpp"
#include <memory> //for unique_ptr
//----------------------------------------

class Game {

private:
    Board board;
    CList players;
    CSDice* dice;

public:
        Game();
        ~Game() {delete [] dice;};
        Player getNewPlayer();
        void oneTurn(Player* pp);
        bool addPlayer();
        void playGame();

    void checkPlayerData(const string &newName, char newColor);
};
