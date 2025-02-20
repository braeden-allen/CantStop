//----------------------------------------
//File: Game.hpp
//Authors: Braeden and Mateusz
//----------------------------------------

#pragma once
#include "Player.hpp"
#include "Dice.hpp"
#include "Column.hpp"
#include "tools.hpp"

class Game {
    private:
        Dice* dice;
        Player player1 , player2;
        Column column2 , column7;

    public:
        Game();
        ~Game();
        void getNewPlayer(Player& player , const string& defaultColor);
};