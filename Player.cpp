//----------------------------------------
//File: Player.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Player.hpp"
#include "enums.hpp"
#include "tools.hpp"
#include <ostream>
//----------------------------------------


Player::Player(const string& playerName, ECcolor color) 
    //initializer list
    : name(playerName), playerColor(color), score(0), columnCount(0) {
        for(int j = 0; j < 3; j++){
            //reason for -1 is to make sure no columns captured
            scoreboard[j] = -1; 
        }
    }

Player::~Player(){

}

ECcolor Player::color() const {
    return playerColor;
}

int Player::score() const {
    return score;
}

bool Player::wonColumn(int colNum){
    if (columnCount < 3) {
        scoreboard[columnCount++] = colNum;
        score++;
        
        //check fi player has won 3 columns
        return columnCount == 3;
    }
    return false;
}

void Player::print() const {
    cout << "Player: " << name << endl;
    cout << "Color: " << colorNames[(int)playerColor] << endl;
    cout << "Score: " << score << endl;
}


//overload
ostream& operator << (ostream& os, const Player& player){
    os << "Player: " << player.name << "\n" 
    << "Color: " << colorNames[(int)player.playerColor] << "\n"
    << "Score: " << player.score << "\n";
    return os;

}



