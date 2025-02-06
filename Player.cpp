//----------------------------------------
//File: Player.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Player.h"
#include "enums.hpp"
#include "tools.hpp"
#include <ostream>
//----------------------------------------

Player::Player(string& playerName, ECcolor color)
    //initializer list
    : name(playerName), color(color), score(0), columnCount(0) {}

Player::~Player(){}

ECcolor Player::getColor() const {return color;}

int Player::getScore() const {return score;}

bool Player::wonColumn(int colNum){
    if (columnCount < 3) {
        scoreboard[columnCount++] = colNum;
        score++;
        return columnCount == 3;//check if player has won 3 columns
    }
    return false;
}

void Player::print() const {
    cout << "Player: " << name << endl;
    cout << "Color: " << colorNames[(int)color] << endl;
    cout << "Score: " << score << endl;
}

//overload
ostream& operator << (ostream& os, const Player& player){
    os << "Player: " << player.name << "\n" 
    << "Color: " << colorNames[(int)player.color] << "\n"
    << "Score: " << player.score << "\n";
    return os;
}