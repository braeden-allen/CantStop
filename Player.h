//----------------------------------------
//File: Player.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "enums.hpp"
#include <ostream>
//----------------------------------------

using namespace std;


class Player{
    private:
        string name;
        ECcolor color;
        int score;
        int scoreboard[3];
    public:
    //consturctor
        Player(string playerName, ECcolor playerColor);
        ~Player();
        ECcolor getColor() const;

        int score() const;
        int getScore() const;

        //store colmn num in next available spot
        bool wonColumn( int colNum);

        void print() const;
        
        friend ostream& operator << (ostream& os, const Player& player);

};
