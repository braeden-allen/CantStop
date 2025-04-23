//----------------------------------------
// Project: Can't Stop Board Game
// File: Main.cpp
// Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>

using std::cout;
using std::cin;
using std::toupper;

int main() {
    srand((time(nullptr)));
    banner();  

    Game game;
    game.playGame();

    bye();  
    return 0;
}