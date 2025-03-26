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

    //Game game(3);

    unitCList();

    banner();
    bye();

    return 0;
}

void unitCList() {

    ofstream out("output.txt");
    out << "----------------------------------------------" << endl;
    out << "CLIST UNIT TEST" << endl;
    out << "----------------------------------------------" << endl;
    bool allTestsPassed = true;

    // Test 1: Empty list
    {
        CList list;
        out << "Test 1: Empty List\n";
        out << "Expected: size = 0, empty = true, output = 'No players'\n";
        out << "Actual:   size = " << list.size();
        out << ", empty=";
        
        if (list.empty()) out << "true";
        else out << "false";
        out << ", output:\n" << list << "\n";

        if (!list.empty()) {out << "-----> FAILED\n"; allTestsPassed = false;}
        else out << "-----> PASSED\n";
    }
    
    {
        CList list;
        out << "\nTest 2: Add Players\n";

        list.add(make_unique<Player>("Alice", ECcolor::Blue));
        list.add(make_unique<Player>("Bob", ECcolor::Yellow));
        list.add(make_unique<Player>("Charlie", ECcolor::Orange));
        list.add(make_unique<Player>("Dana", ECcolor::Green));

        out << "Added 4 players with valid colors (B,Y,O,G)\n";
        out << "Expected: size=4\n";
        out << "Actual:   size=" << list.size() << ", output:\n" << list << "\n";

        if (list.size() != 4) {out << "-----> FAILED (wrong size)\n"; allTestsPassed = false;}
        else out << "-----> PASSED\n";

    }

    {
        CList list;
        list.add(make_unique<Player>("Eve", ECcolor::Blue));
        list.add(make_unique<Player>("Frank", ECcolor::Yellow));

        out << "\nTest 3: Circular Iteration\n";
        list.init();

        Player* first = list.next();
        Player* current = first;
        int count = 0;
        bool circular = true;

        out << "Iteration: ";
        do {
            out << current->getName() << "(" << colorNames[(int)(current->getColor())] << ") ";
            current = list.next();
            count++;
            if (count > 4) {
                circular = false;
                break;
            }
        } while (current != first);

        out << "\nExpected: Eve(Blue) Frank(Yellow) Eve (completes circle in 2 steps)\n";
        out << "Actual:   ";

        if (circular) out << "Completed circle in " << count << " steps\n";
        else out << "Failed to complete circle\n";

        if (!circular || count != 2) {out << "-----> FAILED\n"; allTestsPassed = false;}
        else out << "-----> PASSED\n";

    }

    {
        CList list;
        list.add(make_unique<Player>("Grace", ECcolor::Green));
        list.add(make_unique<Player>("Henry", ECcolor::Orange));

        out << "\nTest 4: Remove Player\n";
        list.init(); // current = Grace
        Player* toRemove = list.getCurrent(); // Grace (no advancement)
        out << "Removing: " << toRemove->getName() << endl; // Grace
        list.remove(); // removes Grace (current)

        out << "Expected: size = 1, remaining player is Henry(Orange)\n";
        out << "Actual:   size = " << list.size() << ", remaining:\n" << list << "\n";

        bool sizeCorrect = (list.size() == 1);
        bool playerCorrect = false;

        if (sizeCorrect) {
            list.init(); // Reset to Henry (new head)
            Player* remaining = list.getCurrent(); // Henry
            playerCorrect = (remaining->getName() == "Henry");
        }

        if (!sizeCorrect || !playerCorrect) {
            out << "-----> FAILED\n";
            allTestsPassed = false;
        } else {
            out << "-----> PASSED\n";
        }
    }


    {
        CList list;
        out << "\nTest 5: Empty and Refill\n";

        list.add(make_unique<Player>("Ivy", ECcolor::Yellow));
        while (!list.empty()) list.remove();

        out << "After clear: size =" << list.size() << "\n";
        list.add(make_unique<Player>("Jack", ECcolor::Blue));
        out << "After refill: size =" << list.size()
            << ", player: " << list.next()->getName()
            << "(" << colorNames[(int)(list.next()->getColor())] << ")\n";

        if (list.size() != 1 || list.next()->getName() != "Jack") {out << "-----> FAILED\n"; allTestsPassed = false;}
        else out << "-----> PASSED\n";
    }

    out << "----------------------------------------------" << endl;

    out << "FINAL RESULTS" << endl;
    out << "All tests ";
    if (allTestsPassed) out << "PASSED\n";
    else out << "FAILED\n";
    out << "----------------------------------------------" << endl;


    out.close();
}