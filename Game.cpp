//----------------------------------------
//File: Game.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
//----------------------------------------

Game::Game(int numPlayers)
        : dice(new Dice(4)) { //initialize 4 dice
    for (int i = 0; i < numPlayers; ++i) {
        players.add(std::make_unique<Player>(getNewPlayer()));
    }
    players.init(); //initialize circular iteration
}

Player Game::getNewPlayer() {
    string name;
    char colorChoice;
    ECcolor color;

    cout << "\nEnter player's name: ";
    cin >> name;

    cout << "Choose " << name << "'s color (O=Orange, Y=Yellow, G=Green, B=Blue): ";
    cin >> colorChoice;
    colorChoice = toupper(colorChoice); //convert to uppercase for consistency

    switch (colorChoice) {//translate color choice to enum
        case 'O': color = ECcolor::Orange; break;
        case 'Y': color = ECcolor::Yellow; break;
        case 'G': color = ECcolor::Green; break;
        case 'B': color = ECcolor::Blue; break;
        default:
            cout << "Invalid color. Defaulting to Blue.\n";
            color = ECcolor::Blue;
            break;
    }
    cout << endl;
    return {name, color}; //initialize and return the player
}

void Game::oneTurn(Player* pp){

    board.startTurn(pp);
    int usedTowers = 0;

    while (true) {

        int choice;
        cout << "Enter a Menu Option From Below:" << endl;
        cout << "\t1. Roll Dice\n\t2. Stop Turn\n\t3. Resign" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        while (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
            cin >> choice;
        }//validate input

        //handle player's choice
        if (choice == 1) {
            if (usedTowers >= 3){
                cout << "You cannot use more than 3 towers per turn. Resign or Stop turn" << endl;
                continue;
            }

            const int* diceValues = dice->roll();
            cout << "Dice rolled: ";
            for (int k = 0; k < 4; ++k) {
                cout << diceValues[k] << " ";
            }
            cout << endl;

            char die1, die2;
            cout << "Choose two dice (enter their letters, e.g., AB or bc): ";
            cin >> die1 >> die2;

            //validate die input
            while (toupper(die1) < 'A' || toupper(die1) > 'D' ||
                   toupper(die2) < 'A' || toupper(die2) > 'D') {
                cout << "Invalid dice selection. Please choose two letters between A and D: ";
                cin >> die1 >> die2;
            }

            int index1 = toupper(die1) - 'A'; //convert input -> index
            int index2 = toupper(die2) - 'A';

            int pair1 = diceValues[index1] + diceValues[index2]; //calculate die pairs
            int pair2 = 0;
            for (int k = 0; k < 4; ++k) {
                if (k != index1 && k != index2) {pair2 += diceValues[k];}
            }

            cout << "Pair 1: " << pair1 << " (Dice " << die1 << " and " << die2 << ")\n";
            cout << "Pair 2: " << pair2 << " (Remaining dice)\n";

            //attempt to move on column using the pairs
            bool move1Success = board.move(pair1);
            bool move2Success = board.move(pair2);

            if (move1Success) {usedTowers++;}
            if (move2Success) {usedTowers++;}

            board.print(cout); //display the board after the moves

            if (!move1Success && !move2Success) {
                cout << "Both moves failed! You busted.\n";
                board.bust();
                break; //end the turn
            }

            if (move1Success && board.getColumn(pair1)->getState() == EColStatus::captured) {
                cout << "Column " << pair1 << " captured!" << endl;
                pp->wonColumn(pair1);
            }

            if (move2Success && board.getColumn(pair2)->getState() == EColStatus::captured) {
                cout << "Column " << pair2 << " captured!" << endl;
                pp->wonColumn(pair2);
            }

            if (pp->getScore() >= 3) {
                cout << "Player " << pp->getName() << " has won the game!" << endl;
                return;
            }//check if the player has won

        } else if (choice == 2) {board.stop(); break;} //Player chooses to stop
        else if (choice == 3) {cout << "Resignation is not yet implemented.\n";}//(deferred implementation)
    }
}
