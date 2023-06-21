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
    int prompt();
    inline char intToCode(int i);
    inline int codeToInt(char code);
};

#endif
