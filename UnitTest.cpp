//----------------------------------------
//File: UnitTest.h
//Authors: Braeden and Mateusz
//----------------------------------------

#include "UnitTest.h"
#include "Dice.h"

void UnitTest::unitDice() {
    ofstream outFile("output.txt" , ios::app);
    if (!outFile){cerr << "Error Opening Output.txt File"; return;}

    //initial message
    outFile << "START OF DICE TEST" << endl;
    Dice d1(6); //roll different numbers of dice each time

    //test the roll function
    outFile << "TEST FOR ACCURATE ROLL" << endl;
    const int* dieValues = d1.roll();
    outFile << "Values from roll: ";

    for (int k = 0; k < d1.getnDice(); k++) {
        outFile << dieValues[k] << " ";

        if (dieValues[k] < 1 || dieValues[k] > 6){outFile << "n\nValues are out of range(1-6)" << endl;}
    }

    //test the print function
    outFile << "\nTest for accurate PRINTING of Dice values" << endl;
    outFile << "Die Values: ";
    d1.print(outFile);
    outFile << endl;

    //test the destructor for memory leaks
    outFile << "DESTRUCTOR TEST" << endl;
    Dice d2(4);
    outFile << "Class destructed without error or memory leak\n" << endl;
    outFile.close();
}

void UnitTest::unitPlayer(){

}