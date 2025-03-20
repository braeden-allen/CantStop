//----------------------------------------
//File: Game.hpp
//Authors: Braeden
//----------------------------------------
#pragma once
#include "Board.hpp"
#include "Dice.hpp"
#include <memory> //for unique_ptr
//----------------------------------------

class Game {

    public:
        Board board;
        Dice* dice;
        vector<Player> players;

        Game(int numPlayers = 2); //make it a 2 person game by default
        ~Game() = default;
        Player getNewPlayer();
        void oneTurn(Player* pp);

};