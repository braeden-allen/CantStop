//----------------------------------------
//File: Player.hpp
//Authors: Braeden and Mateusz
//----------------------------------------
#pragma once
#include "tools.hpp"
#include "enums.hpp"
//----------------------------------------

class Player{

    private:
        string playerName;
        ECcolor playerColor;
        int scoreboard[3];
        int columnCount;
        int score = 0;

    public:
        //constructor
        explicit Player(const string Name, ECcolor color);
        ~Player();

        // Special functions
        ECcolor getColor() const;
        int getScore() const;

        //store column num in next available spot
        bool wonColumn(int colNum);
        ostream& print(ostream& os) const;
};
ostream& operator << (ostream&, const Player&);
