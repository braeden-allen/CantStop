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

    srand(static_cast<unsigned>(time(nullptr)));
    banner();  // assume banner() is defined elsewhere

    Game game; // starts with 0 players

    // add mandatory 2 players
    cout << "=== PLAYER SETUP ===\n";
    for (int i = 0; i < 2; i++) {
        cout << "Player " << i+1 << ":\n";
        game.addPlayer();
    }

    // optional additional players
    char choice;
    do {
        cout << "\nAdd another player? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'Y') {
            if (!game.addPlayer()) { break; } // stop if max players reached
        }
        else if (choice != 'N') {
            cout << "Invalid choice. Please enter Y or N.\n";
        }
    } while (choice != 'N');

    game.playGame();

    bye(); // assume bye() is defined elsewhere
    return 0;
}
