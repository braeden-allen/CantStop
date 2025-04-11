//----------------------------------------
//File: Game.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
//need to add the new exceptions
#include "exceptions.hpp"
//----------------------------------------

Game::Game(){
    dice = new CSDice();
}

//for testing for fake_dice.txt
//Game::Game(){
//     dice = new FakeDice();
//}

void Game::checkPlayerData(const string& newName, char newColor) {
    bool nameExists = false;
    bool colorExists = false;
    int count = players.getCount();

    // Convert color choice to ECcolor for proper comparison
    ECcolor color;
    switch(toupper(newColor)) {
        case 'O': color = ECcolor::Orange; break;
        case 'Y': color = ECcolor::Yellow; break;
        case 'G': color = ECcolor::Green; break;
        case 'B': color = ECcolor::Blue; break;
        default: color = ECcolor::Blue; // default case
    }

    for (int k = 0; k < count; k++) {
        Player* p = players.getCurrent();
        if (p->getName() == newName) nameExists = true;
        if (p->getColor() == color) colorExists = true; // Compare ECcolor directly
        players.next();
    }

    if (nameExists && colorExists) {
        throw BadPlayer(newName.c_str(), string(1, newColor).c_str());
    }
    else if (nameExists) {
        throw BadName(newName.c_str(), string(1, newColor).c_str());
    }
    else if (colorExists) {
        throw BadColor(newName.c_str(), string(1, newColor).c_str());
    }
}

Player Game::getNewPlayer() {
    while (true) {
        string name;
        char colorChoice;
        ECcolor color;

        cout << "\nEnter player's name: ";
        cin >> name;

        cout << "Choose color for " << name << ":\n"
             << "(O)range, (Y)ellow, (G)reen, (B)lue: ";
        cin >> colorChoice;
        colorChoice = toupper(colorChoice);

        // Validate color input
        while (colorChoice != 'O' && colorChoice != 'Y' &&
               colorChoice != 'G' && colorChoice != 'B') {
            cout << "Invalid color. Please choose O, Y, G, or B: ";
            cin >> colorChoice;
            colorChoice = toupper(colorChoice);
        }

        try {
            checkPlayerData(name, colorChoice);
            switch(colorChoice) {// Convert to ECcolor
                case 'O': color = ECcolor::Orange; break;
                case 'Y': color = ECcolor::Yellow; break;
                case 'G': color = ECcolor::Green; break;
                case 'B': color = ECcolor::Blue; break;
            }
            return Player(name, color);
        }
        catch (const BadPlayer& e) {
            e.print();
            cout << "Please try again.\n";
        }
    }
}

void Game::oneTurn(Player* pp) {

    board.startTurn(pp);
    int usedTowers = 0;

    while (true) {

        int choice;
        cout << "It is " << players.getCurrent()->getName() << "'s turn" << std::endl;
        cout << "Enter a Menu Option From Below:" << std::endl;
        cout << "\t1. Roll Dice\n\t2. Stop Turn\n\t3. Resign" << std::endl;
        cout << "Enter Choice: ";
        cin >> choice;

        while (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
            cin >> choice;
        }

        if (choice == 1) {
            if (usedTowers >= 3) {
                cout << "You cannot use more than 3 towers per turn. Resign or Stop turn" << std::endl;
                continue;
            }

            const int* pairs = dice->roll();
            int pair1 = pairs[0];
            int pair2 = pairs[1];

            bool move1Success = false;
            bool move2Success = false;
            Column* col1 = board.getColumn(pair1);
            Column* col2 = (pair1 != pair2) ? board.getColumn(pair2) : nullptr;

            //checking existing towers
            bool hadTower1 = col1 && col1->getState() == EColStatus::pending;
            bool hadTower2 = col2 && col2->getState() == EColStatus::pending;

            if (pair1 == pair2) {
                if (hadTower1) {
                    move1Success = col1->move();
                    move2Success = move1Success && col1->move();
                } else {
                    move1Success = col1->startTower(pp);
                    if (move1Success) {
                        usedTowers++;
                        move2Success = col1->move();
                    }
                }
            } else {
                move1Success = board.move(pair1);
                move2Success = board.move(pair2);
            }

            if (move1Success && !hadTower1) usedTowers++;
            if (move2Success && !hadTower2 && pair1 != pair2) usedTowers++;

            board.print(std::cout);

            if (!move1Success && !move2Success) {
                cout << "Both moves failed! You busted." << std::endl;
                board.bust();
                //end turn
                break;
            }

            if (move1Success && board.getColumn(pair1)->getState() == EColStatus::captured) {
                cout << "Column " << pair1 << " captured!" << std::endl;
                pp->wonColumn(pair1);
            }

            if (move2Success && board.getColumn(pair2)->getState() == EColStatus::captured) {
                cout << "Column " << pair2 << " captured!" << std::endl;
                pp->wonColumn(pair2);
            }

            if (pp->getScore() >= 3) {
                cout << "Player " << pp->getName() << " has won the game!" << std::endl;
                return;
            }
        }
        else if (choice == 2) {
            board.stop();
            players.next();
            break;
        }
        else if (choice == 3) {
            cout << "\n" << pp->getName() << " resigns." << std::endl;
            std::string resignName = pp->getName();
            board.bust();
            players.init();
            players.remove();

            cout << "Number of players left: " << players.getCount() << "\n\n";

            if (players.getCount() == 1) {
                Player* winner = players.next();
                cout << "Default win for " << winner->getName() << std::endl;
                bye();
                exit(0);
            }

            if (players.getCount() >= 2) {
                Player* nextPlayer = players.next();
                if (nextPlayer) {
                    oneTurn(nextPlayer);
                }
            }
            return;
        }
    }
    players.next();
}

bool Game::addPlayer() {
    if (players.getCount() >= 4) {
        cout << "Maximum players reached (4)" << std::endl;
        return false;
    }

    try {
        Player p = getNewPlayer();
        players.add(std::make_unique<Player>(p));
    }
    catch (const BadPlayer& bp) {
        bp.print();
        cout << "Error creating player. Please re-enter your details.\n";
        return addPlayer();
    }
    if (players.getCount() == 1) {
        players.init();
    }
    return true;
}

void Game::playGame() {
    if (players.getCount() < 2) {
        cout << "Need at least 2 players to start!" << std::endl;
        return;
    }

    cout << "\n=== GAME START ===\n";
    while (players.getCount() >= 2) {
        Player* current = players.getCurrent();
        oneTurn(current);
        players.next();
    }
}