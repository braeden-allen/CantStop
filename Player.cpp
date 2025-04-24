//----------------------------------------
//File: Player.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Player.hpp"
//----------------------------------------

Player::Player(const string Name, ECcolor color)
        : playerName(Name), playerColor(color), scoreboard(), score(0) {}

ECcolor Player::getColor() const {return playerColor;}
int Player::getScore() const {return score;}
string Player::getName() const {return playerName;}

bool Player::wonColumn(int colNum){
    if (score < 3) {
        scoreboard[score] = colNum;
        ++score;
        return score == 3; //check if player has 3 columns
    }
    return false;
}

ostream& Player::print(ostream& os) const {
    os << "\n=== SCORECARD ===" << endl;
    os << "Player: " << playerName << endl;
    os << "Color: " << colorNames[(int)playerColor] << endl;
    os << "Score: " << score <<endl;
    os << "===================\n" << endl;
    for (int k = 0; k < score; ++k) {
        os << scoreboard[k] << " ";
    }
    return os;
}

//overload
ostream& operator << (ostream& os, const Player& player){return player.print(os);}