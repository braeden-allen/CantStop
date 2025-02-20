//----------------------------------------
//File: Game.hpp
//Authors: Braeden and Mateusz
//----------------------------------------

#include "Player.hpp"
#include "Dice.hpp"
#include "Column.hpp"
#include "tools.hpp"

class Game {
private:
    Dice* dice;
    Player player1;
    Player player2;

    Column column1;
    Column column2;

public:
    Game();
    ~Game();

    void getNewPlayer();

}
