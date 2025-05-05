//----------------------------------------
//File: Game.cpp
//Authors: Braeden & Mateusz
//----------------------------------------
#include "Game.hpp"
#include "exceptions.hpp"
//----------------------------------------

Game::Game() : gameState(EGameStatus::Begun) {
    cout << "Select game mode:\n1. Manual Gameplay\n2. Automated Testing\n";
    int choice;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin >> choice;
    }

    if (choice == 1) {
        dice = new CSDice();  // Manual gameplay
        cout << "=== MANUAL GAMEPLAY MODE ===\n";
    } else {
        dice = new FakeDice();  // Automated testing
        cout << "=== TEST MODE: USING FAKE DICE ===\n";
    }
    setupPlayers(2, 4);
}

void Game::checkPlayerData(const string& newName, char newColor) {
    bool nameExists = false;
    bool colorExists = false;
    int count = players.getCount();
    ECcolor color;
    switch(toupper(newColor)) {
        case 'O': color = ECcolor::Orange; break;
        case 'Y': color = ECcolor::Yellow; break;
        case 'G': color = ECcolor::Green; break;
        case 'B': color = ECcolor::Blue; break;
        default: color = ECcolor::Blue; // default case
    }
    Player newPlayer(newName, color);
    for (int k = 0; k < count; k++) {
        Player* p = players.getCurrent();
        if (*p == newPlayer) {
            throw BadPlayer(newName.c_str(), string(1, newColor).c_str());}
        if (p->getName() == newName) nameExists = true;
        if (p->getColor() == color) colorExists = true;
        players.next();
    }
    if (nameExists) {
        throw BadName(newName.c_str(), string(1, newColor).c_str());}
    else if (colorExists) {
        throw BadColor(newName.c_str(), string(1, newColor).c_str());}
}

string getPlayerName() {
    string name;
    cout << "\nEnter player's name: ";
    cin >> name;
    return name;
}

// Helper function to get and validate color choice
char getColorChoice(const string& playerName) {
    char colorChoice;
    cout << "Choose color for " << playerName << ":\n"
              << "(O)range, (Y)ellow, (G)reen, (B)lue: ";
    cin >> colorChoice;
    colorChoice = toupper(colorChoice);

    // Validate input
    while (colorChoice != 'O' && colorChoice != 'Y' &&
           colorChoice != 'G' && colorChoice != 'B') {
        cout << "Invalid color. Please choose O, Y, G, or B: ";
        cin >> colorChoice;
        colorChoice = toupper(colorChoice);
    }
    return colorChoice;
}

// Converts char color choice to ECcolor enum
ECcolor convertColorChoice(char choice) {
    switch(choice) {
        case 'O': return ECcolor::Orange;
        case 'Y': return ECcolor::Yellow;
        case 'G': return ECcolor::Green;
        case 'B': return ECcolor::Blue;
        default: throw invalid_argument("Invalid color choice");
    }
}

Player Game::getNewPlayer() {
    while (true) {
        try {
            string name = getPlayerName();
            char colorChoice = getColorChoice(name);
            ECcolor color = convertColorChoice(colorChoice);
            checkPlayerData(name, colorChoice); // Validation (assuming this throws BadPlayer)
            return Player(name, color);
        }
        catch (const BadPlayer& e) {
            e.print();
            cout << "Please try again.\n";
        }
    }
}

int Game::printTurnMenu(Player* pp) {
    if (auto* fd = dynamic_cast<FakeDice*>(dice)) {// Automated testing mode
        string action = fd->lastAction;
        cout << "\n(Test) Auto-action from file: " << action << "\n\n";
        fd->lastAction.clear(); // Clear the action after reading

        if (action == ROLL_ACTION) return 1;
        if (action == STOP_ACTION) return 2;
        if (action == QUIT_ACTION) return 3;
        return 1;  // Default to roll
    }

    // Manual gameplay mode
    cout << "It is " << pp->getName() << "'s turn\n";
    cout << "Enter a Menu Option From Below:\n";
    cout << "\t1. Roll Dice\n\t2. Stop Turn\n\t3. Resign\n";
    int choice;
    cout << "Enter Choice: ";
    cin >> choice;
    while (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> choice;
    }
    return choice;
}

bool Game::handleRoll(Player* pp, int& usedTowers) {

    const int* pairs = dice->roll();
    int pair1 = pairs[0], pair2 = pairs[1];
    Column* col1 = board.getColumn(pair1);
    Column* col2 = (pair1 != pair2) ? board.getColumn(pair2) : nullptr;

    bool hadTower1 = col1 && col1->getState() == EColStatus::pending;
    bool hadTower2 = col2 && col2->getState() == EColStatus::pending;

    bool move1 = (pair1 == pair2) ? handleDoubleRoll(col1, pp, usedTowers, hadTower1) :
                 board.move(pair1);
    bool move2 = (pair1 == pair2) ? move1 && col1->move() :
                 board.move(pair2);

    if (move1 && !hadTower1) usedTowers++;
    if (move2 && !hadTower2 && pair1 != pair2) usedTowers++;
    board.print(cout);
    return handlePostRoll(pair1, pair2, move1, move2, pp);
}

bool Game::handleDoubleRoll(Column* col, Player* pp, int& usedTowers, bool hadTower) {
    if (hadTower) return true;  // Tower exists, allow moves
    bool started = col->startTower(pp);  // Start tower at position 1
    if (started) usedTowers++;
    return started;
}

bool Game::handlePostRoll(int pair1, int pair2, bool move1, bool move2, Player* pp) {
    if (!move1 && !move2) {
        cout << "Both moves failed! You busted.\n";
        board.bust();
        return false;
    }

    if (move1 && board.getColumn(pair1)->getState() == EColStatus::captured) {
        cout << "Column " << pair1 << " captured!\n";
        pp->wonColumn(pair1);
    }

    if (move2 && pair1 != pair2 && board.getColumn(pair2)->getState() == EColStatus::captured) {
        cout << "Column " << pair2 << " captured!\n";
        pp->wonColumn(pair2);
    }

    if (pp->getScore() >= 3) {
        cout << "Player " << pp->getName() << " has won the game!\n";
        gameState = EGameStatus::Done;
        return false; //end the turn
    }
    return true;
}

void Game::handleStop(Player* pp) {
    for (int col = 2; col <= 12; ++col) {
        Column* c = board.getColumn(col);
        if (c->hasTower(pp)) {
            c->commitTower(pp);  // This calls Column::stop internally
        }
    }
}

void Game::handleResign(Player* pp) {
    cout << "\n" << pp->getName() << " resigns.\n";
    board.bust();

    string resignedName = pp->getName();
    players.remove();  //delete resigning player

    cout << "Number of players left: " << players.getCount() << "\n\n";

    if (players.getCount() == 1) {
        players.init(); //now only one player, safe to reset
        Player* winner = players.getCurrent();
        cout << "Default win for " << winner->getName() << "\n";
        gameState = EGameStatus::Done;
        return;
    }

    if (players.getCount() == 0) {
        gameState = EGameStatus::Quit;
        cout << "All players have resigned. Game over.\n";
        return;
    }
    players.init();  // safe reset to next valid player
}

EGameStatus Game::oneTurn(Player* pp) {
    board.startTurn(pp);
    int usedTowers = 0;

    while (true) {
        int choice = printTurnMenu(pp);
        if (choice == 1) {
            if (!handleRoll(pp, usedTowers)) { //check for win condition
                if (gameState == EGameStatus::Done) return EGameStatus::Done;
                return EGameStatus::Begun;
            }
        } else if (choice == 2) {
            handleStop(pp);
            board.print(cout);
            return EGameStatus::Begun;
        } else if (choice == 3) {
            handleResign(pp);
            return gameState;  //Quit or Done, dependent on # players
        }
    }
}

bool Game::addPlayer() {
    if (players.getCount() >= 4) {
        cout << "Maximum players reached (4)" << endl;
        return false;
    }
    try {
        Player p = getNewPlayer();
        players.add(make_unique<Player>(std::move(p)));
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
        cout << "Insufficient players to start.\n";
        return;
    }

    cout << "\n=== GAME START ===\n";
    while (players.getCount() >= 2 && gameState == EGameStatus::Begun) {
        Player* current = players.getCurrent();
        current->print(cout);
        oneTurn(current);
        if (current->getScore() >= 3) {
            cout << current->getName() << " wins!\n";
            return;
        }
        players.next();
    }
    if (gameState == EGameStatus::Done) cout << "Game over — a player has won.\n";
    else if (gameState == EGameStatus::Quit) cout << "Game over — all players resigned.\n";
    else cout << "Game ended — not enough players remaining.\n";
}

void Game::setupPlayers(int minPlayers , int maxPlayers) {
    cout << "=== PLAYER SETUP ===\n";
    char choice = 'Y';
    while (players.getCount() < maxPlayers &&
           (players.getCount() < 2 || ((cout << "Add more? (Y/N): ") &&
                                        cin >> choice && (choice = toupper(choice)) == 'Y'))) {
        try { addPlayer(); }
        catch (...) { if (players.getCount() < 2) continue; else break; }
    }
    players.init();
}