//----------------------------------------
//File: Game.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Game.hpp"
#include "tools.hpp"
//----------------------------------------

using namespace std;

Game::Game()
        : dice(new Dice(4)), //initialize dice
          player1("Default1", ECcolor::Blue),
          player2("Default2", ECcolor::Green),
          column2(2), //col2
          column7(7) //col7
{
    // Get player names and colors
    getNewPlayer(player1, "Player1");
    getNewPlayer(player2, "Player2");
}

Game::~Game() {delete dice;}

void Game::getNewPlayer(Player& player , const string& defaultName) {

    string name, colorInput;
    ECcolor color;

    cout << "\nEnter " << defaultName << "'s name: ";
    getline(cin, name);
    cout << "Enter " << defaultName << "'s color (Orange, Yellow, Green, Blue): ";
    getline(cin, colorInput);

    for (char& c : colorInput) {c = tolower(c);} //used to make string comparable

    if (colorInput == "orange") color = ECcolor::Orange;
    else if (colorInput == "yellow") color = ECcolor::Yellow;
    else if (colorInput == "green") color = ECcolor::Green;
    else if (colorInput == "blue") color = ECcolor::Blue;
    else {cout << "Invalid color. Defaulting to Blue.\n";color = ECcolor::Blue;}

    player = Player(name, color); //init player with input
}