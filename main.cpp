//----------------------------------------
//Project: Can't Stop Board Game
//File: Main.cpp
//Authors: Braeden and Mateusz
//----------------------------------------
#include "Dice.h"
#include "UnitTest.h"
#include "tools.hpp"
//----------------------------------------

int main(int argc , char* argv[]) {
    banner();

    UnitTest test;

    test.unitDice();

    bye();
    return 0;
}