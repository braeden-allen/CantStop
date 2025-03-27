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
    Dice* dice;
    CList players;

public:
        Game(int numPlayers = 2); //make it a 2 person game by default
        ~Game() = default;
        Player getNewPlayer();
        void oneTurn(Player* pp);
};
