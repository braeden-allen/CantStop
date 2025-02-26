//----------------------------------------
//File: Game.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "Player.hpp"
#include "Dice.hpp"
#include "Column.hpp"
#include "tools.hpp"
//----------------------------------------

class Game {
    private:

        Dice* dice;
        Player player1 , player2;
        Column column2 , column7;

    public:
        Game();
        ~Game();
        Player getNewPlayer();
        [[nodiscard]] Dice* getDice() const {return dice;}
        Player& getP1(){return player1;}
        Player& getP2(){return player2;}
        Column& getCol2(){return column2;} //these are not used in unitBoard(), kept for the unitGame function
        Column& getCol7(){return column7;}
};