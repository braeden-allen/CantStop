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

int main() {
    srand((time(nullptr)));
    banner();

    //FakeDice* fd = new FakeDice();   // reads from file
    Game game;                   // uses test constructor
    game.playGame();                 // auto-runs based on file

    //delete fd;

    bye();  
    return 0;
}