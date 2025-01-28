//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
#include "tools.hpp"
//----------------------------------------

int main(int argc , char* argv[]) {
    banner();

    bye();
    return 0;
}

void unitDice(){
    ofstream unitTests("UnitTests" , ios::app);

    if (unitTests.is_open()){

        unitTests.close();
    }else{
        cerr << "Unable to open file" << endl;
    }
}