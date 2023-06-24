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
    int codeToInt(char code);
    char intToCode(int i);
};

#endif
