//----------------------------------------
//File: Game.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Game.hpp"
#include "tools.hpp"
//----------------------------------------

Game::Game()
        : dice(new Dice(4)), //initialize dice
          player1(getNewPlayer()),
          player2(getNewPlayer()),//col2 (not used in most recent test)
          column2(2), //col7 (not used in most recent test)
          column7(7)
{}

Game::~Game() {delete dice;}

Player Game::getNewPlayer() {

    string name, colorInput;
    ECcolor color;

    cout << "\nEnter player's name: ";
    getline(cin, name);
    cout << "Enter " << name << "'s color (Orange, Yellow, Green, Blue): ";
    getline(cin, colorInput);
    cout << "\n" << endl;

    for (char& c : colorInput) {c = tolower(c);} //used to make string comparable

    if (colorInput == "orange") color = ECcolor::Orange;
    else if (colorInput == "yellow") color = ECcolor::Yellow;
    else if (colorInput == "green") color = ECcolor::Green;
    else if (colorInput == "blue") color = ECcolor::Blue;
    else {cout << "Invalid color. Defaulting to Blue.\n";color = ECcolor::Blue;}

    return Player(name, color); //init player with input
}