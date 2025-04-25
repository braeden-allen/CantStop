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
        int score;

    public:
        //constructor
        Player(string Name, ECcolor color);

        //better spot for defaulting for player
        ~Player() = default;

        //special functions
        [[nodiscard]] ECcolor getColor() const;
        [[nodiscard]] int getScore() const;
        [[nodiscard]] string getName() const;

        //store column num in next available spot
        bool wonColumn(int colNum);
        ostream& print(ostream& os) const;
};
ostream& operator << (ostream&, const Player&);