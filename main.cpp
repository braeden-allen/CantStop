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
    banner();  // Ensure banner() is defined elsewhere.

    Game game; 

    cout << "=== PLAYER SETUP ===\n";
    for (int i = 0; i < 2; i++) {
        cout << "Player " << i + 1 << ":\n";
        game.addPlayer();
    }

    char choice;
    do {
        cout << "\nAdd another player? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'Y') {
            if (!game.addPlayer()) { 
                break; 
            }
        } else if (choice != 'N') {
            cout << "Invalid choice. Please enter Y or N.\n";
        }
    } while (choice != 'N');

    game.playGame();

    bye();  // Ensure bye() is defined elsewhere.
    return 0;

}
