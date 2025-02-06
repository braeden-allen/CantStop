//----------------------------------------
//File: Player.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Player.h"
#include "enums.hpp"
#include "tools.hpp"
#include <ostream>
//----------------------------------------

Player::Player(const string Name, ECcolor color)
        : playerName(Name), playerColor(color), score(0), scoreboard() {}

Player::~Player() = default;

ECcolor Player::getColor() const {return playerColor;}
int Player::getScore() const {return score;}

bool Player::wonColumn(int colNum){
    if (columnCount < 3) {
        scoreboard[columnCount++] = colNum;
        score++;
        return columnCount == 3;//check if player has won 3 columns
    }
    return false;
}

ostream& Player::print(ostream& os) const {
    os << "Player: " << playerName << endl;
    os << "Color: " << colorNames[(int)playerColor] << endl;
    os << "Score: " << score << endl;

    for (int k = 0; k < 3; ++k) {
        os << scoreboard[k] << " ";
    }
    return os;
}

//overload
ostream& operator << (ostream& os, const Player& player){return player.print(os);}