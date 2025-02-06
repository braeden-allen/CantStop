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
        string playerName;
        ECcolor playerColor;
        int score;
        int scoreboard[3];
        int columnCount;

    public:
        //constructor
        explicit Player(const string Name, ECcolor color);
        ~Player();

        //accessors
        ECcolor getColor() const;
        int getScore() const;

        //store colmn num in next available spot
        bool wonColumn(int colNum);
        ostream& print(ostream& os) const;
};
ostream& operator << (ostream&, const Player&);