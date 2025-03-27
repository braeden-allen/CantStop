//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden
//----------------------------------------
#include "Game.hpp"
//----------------------------------------

void unitCList();

int main(int argc , char* argv[]) {
    srand(time(nullptr)); //initialized random number generator

    unitCList();

    banner();
    bye();

    return 0;
}

void unitCList() {
    ofstream out("output.txt");

    fbanner(out);

    out << "\n\n----------------------------------------------" << endl;
    out << "                CLIST UNIT TEST              " << endl;
    out << "----------------------------------------------" << endl;
    CList list;

    out << "\n********** Test 1: Adding Players **********" << endl; //tests the add function
    list.add(make_unique<Player>("Player1", ECcolor::Blue));
    list.add(make_unique<Player>("Player2", ECcolor::Green));
    list.add(make_unique<Player>("Player3", ECcolor::Orange));
    list.add(make_unique<Player>("Player4", ECcolor::Yellow));
    out << list;
    out << "Number of players: " << list.getCount() << endl;
    out << "----------------------------------------------" << endl;

    out << "\n********** Test 2: Removing a Player **********" << endl;
    list.init(); //set current to head
    list.next(); //move to the first player (Alice)
    list.remove(); //remove Alice
    out << list;
    out << "Number of players: " << list.getCount() << endl;
    out << "----------------------------------------------" << endl;

    out << "\n********** Test 3: Removing All Players **********" << endl;
    while (!list.empty()) {
        list.remove();
    }
    out << "Number of players: " << list.getCount() << endl;
    out << "----------------------------------------------" << endl;

    out << "\n********** Test 4: Adding Players Again **********" << endl;
    list.add(make_unique<Player>("New Player A", ECcolor::Blue));
    list.add(make_unique<Player>("New Player B", ECcolor::Orange));
    out << list; // Print the list after adding players
    out << "Number of players: " << list.getCount() << endl;
    out << "----------------------------------------------" << endl;

    out << "\n********** Test 5: Traverse the List **********" << endl; //tests the CList.next() function
    list.init(); //set current to head
    for (int y = 0; y < list.getCount(); ++y) {
        Player* currentPlayer = list.next(); //get Player from the list
        if (currentPlayer) {
            out << "Current Player: " << currentPlayer->getName() << endl; //use Player methods
        }
    }
    out << "----------------------------------------------" << endl;

    out << "\n********** Test 6: Print an Empty List **********" << endl; //tests remove
    while (!list.empty()) {
        list.remove();
    }
    list.print(out);
    out << "Number of players: " << list.getCount() << endl;
    out << "----------------------------------------------" << endl;

    out.close();
}