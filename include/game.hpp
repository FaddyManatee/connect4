#ifndef GAME_H
#define GAME_H

#include "grid.hpp"
#include "minimax.hpp"

class Game {
  public:
    Game();
    void start();

  private:
    Grid grid;
    Minimax m;

    int nextTurn();
    int prompt();
    int codeToInt(char code);
    char intToCode(int i);
};

#endif
