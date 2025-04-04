//----------------------------------------
//File: Game.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
//----------------------------------------

Game::Game(){
    dice = new CSDice();
}

//for testing for fake_dice.txt
// Game::Game(){
//     dice = new FakeDice();
// }


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

void Game::oneTurn(Player* pp) {

    board.startTurn(pp);
    int usedTowers = 0;

    while (true) {

        int choice;
        cout << "It is " << players.getCurrent()->getName() << "'s turn" << endl;
        cout << "Enter a Menu Option From Below:" << endl;
        cout << "\t1. Roll Dice\n\t2. Stop Turn\n\t3. Resign" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        while (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
            cin >> choice;
        }//validate input

        if (choice == 1) {
            if (usedTowers >= 3) {
                cout << "You cannot use more than 3 towers per turn. Resign or Stop turn" << endl;
                continue;
            }

            // Use polymorphic dice roll - returns pair totals directly
            const int* pairs = dice->roll();  // This calls CSDice::roll() or FakeDice::roll()
            int pair1 = pairs[0];
            int pair2 = pairs[1];

            bool move1Success = false;
            bool move2Success = false;
            Column* col1 = board.getColumn(pair1);
            Column* col2 = (pair1 != pair2) ? board.getColumn(pair2) : nullptr;

            // Check existing towers
            bool hadTower1 = col1 && col1->getState() == EColStatus::pending;
            bool hadTower2 = col2 && col2->getState() == EColStatus::pending;

            if (pair1 == pair2) {
                // Identical pairs - special handling
                if (hadTower1) {
                    // Existing tower - move twice if possible
                    move1Success = col1->move();
                    move2Success = move1Success && col1->move();
                } else if (usedTowers < 3) {
                    // New tower - place and move once
                    move1Success = col1->startTower(pp);
                    if (move1Success) {
                        usedTowers++;
                        move2Success = col1->move();
                    }
                }
            } else {
                // Different pairs - normal handling
                move1Success = board.move(pair1);
                move2Success = board.move(pair2);
            }

            // Update tower count (only for new towers)
            if (move1Success && !hadTower1) usedTowers++;
            if (move2Success && !hadTower2 && pair1 != pair2) usedTowers++;

            board.print(cout);

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
        }
        else if (choice == 2) {board.stop(); players.next(); break;} //player chooses to stop
        else if (choice == 3) { // Resign
            cout << "\n" << pp->getName() << " resigns.\n";

            string resignName = pp->getName();
            board.bust(); //clean up state
            players.init();
            players.remove();

            cout << "Number of players left: " << players.getCount() << "\n\n";

            if (players.getCount() == 1) {
                Player* winner = players.next();
                cout << "Default win for " << winner->getName() << endl;
                bye();
                exit(0);
            }

            if (players.getCount() >= 2) { //ensure game is still playable
                Player* nextPlayer = players.next();
                if (nextPlayer) {
                    oneTurn(nextPlayer); //start new turn
                }
            }
            return; //always exit current turn
        }
    }
    players.next();
}

bool Game::addPlayer() {
    if (players.getCount() >= 4) { // Max 4 players
        cout << "Maximum players reached (4)\n";
        return false;
    }

    players.add(make_unique<Player>(getNewPlayer()));
    if (players.getCount() == 1) {
        players.init(); //initialize iteration for first player
    }
    return true;
}

void Game::playGame() {
    if (players.getCount() < 2) {
        cout << "Need at least 2 players to start!\n";
        return;
    }

    cout << "\n=== GAME START ===\n";
    while (players.getCount() >= 2) {
        Player* current = players.getCurrent();
        oneTurn(current);
        players.next(); // Critical addition
    }
}