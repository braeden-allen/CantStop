//----------------------------------------
// Project: Can't Stop Board Game
// File: Main.cpp
// Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand((time(nullptr)));
    banner();

    Game game;
    game.playGame();

    bye();  
    return 0;
}