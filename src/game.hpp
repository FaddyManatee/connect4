#ifndef GAME_H
#define GAME_H

#include "grid.hpp"

class Game {
public:
    Game();
    void start();

private:
    Grid grid;
    int curPlayer;

    void nextTurn();
    char intToCode(int i);
    int codeToInt(char code);
    int prompt();
};

#endif
