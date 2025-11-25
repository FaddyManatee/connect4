#ifndef GAME_H
#define GAME_H

#include "grid.hpp"
#include "minimax.hpp"

class Game {
  public:
    Game();
    ~Game();

    void start();

  private:
    Grid    *grid;
    Minimax *minimax;

    Result play_turn();
    char   int_to_char(int i);
    int    char_to_int(char code);
    int    prompt();
};

#endif  // GAME_H

