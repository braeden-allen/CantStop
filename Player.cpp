//----------------------------------------
//File: Player.cpp
//Authors: Braeden and Mateusz
//----------------------------------------

// need to keep Player.hpp since it is calling the Player class within it
#include "Player.hpp"
#include "enums.hpp"
//----------------------------------------

Player::Player(const string Name, ECcolor color)
        : playerName(Name), playerColor(color), /*score(0),*/ scoreboard() {}

Player::~Player() = default;

ECcolor Player::getColor() const {return playerColor;}
int Player::getScore() const {return score;}

bool Player::wonColumn(int colNum){
    if (score < 3) {
        scoreboard[score] = colNum;
        ++score;
        return score == 3;//check if player has 3 columns
    }
    return false;
}

ostream& Player::print(ostream& os) const {
    os << "Player: " << playerName << "\n";
    os << "Color: " << colorNames[(int)playerColor] << "\n";
    os << "Score: " << score << endl;

    for (int k = 0; k < score; ++k) {
        os << scoreboard[k] << " ";
    }
    return os;
}

//overload
ostream& operator << (ostream& os, const Player& player){return player.print(os);}
