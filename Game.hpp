//----------------------------------------
//File: Game.hpp
//Authors: Braeden & Mateusz
//----------------------------------------
#pragma once
#include "Board.hpp"
#include "Dice.hpp"
#include "CList.hpp"
#include <memory>
//----------------------------------------

class Game {

private:
        Board board;
        CList players;
        CSDice* dice;
        Dice* FakeDice;
        EGameStatus gameState;
        const int* currentPairs; //last rolled dice pairs
        bool alreadyRolled = false; //determining if Bust
        void setupPlayers(int minPlayers = 2, int maxPlayers = 4);

public:
        Game();
        ~Game() {delete [] dice;};
        Player getNewPlayer();
        void oneTurn(Player* pp);
        bool addPlayer();
        void playGame();

        static int printTurnMenu(Player* pp);
        bool handleRoll(Player* pp, int& usedTowers);
        static bool handleDoubleRoll(Column* col, Player* pp, int& usedTowers, bool hadTower);
        bool handlePostRoll(int pair1, int pair2, bool move1, bool move2, Player* pp);
        void handleResign(Player* pp);
        void checkPlayerData(const string &newName, char newColor);
};