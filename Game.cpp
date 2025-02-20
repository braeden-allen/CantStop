
//----------------------------------------
//File: Game.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Game.hpp"
#include "tools.hpp"

using namespace std;

Game::Game() {
    //is 4 cause of 4 dice
    dice = new Dice[4];

    getNewPlayer(); 
}


Game::~Game() {

    delete[] dice;
}

void Game::getNewPlayer() {
    string name;
    string color;

    //Player inputs
    cout << "Player 1's name: ";
    getline(std::cin, name);
    cout << "Enter Player 1's color: ";
    getline(std::cin, color);
    player1 = Player(name, color); 

    cout << "Player 2's name: ";
    getline(std::cin, name);
    cout << "Enter Player 2's color: ";
    getline(std::cin, color);
    player2 = Player(name, color);  
}
