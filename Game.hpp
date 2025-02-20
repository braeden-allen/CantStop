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
        [[nodiscard]] Dice* getDice() const {return dice;}
        Player& getP1(){return player1;}
        Player& getP2(){return player2;}
        Column& getCol2(){return column2;}
        Column& getCol7(){return column7;}
};