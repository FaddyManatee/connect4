#ifndef GAME_H
#define GAME_H

#include "minimax.hpp"

class Game {
  public:
    Game();
    ~Game();

    void start();

  private:
    Minimax *minimax;

    Result play_turn();
    char   int_to_char(int i);
    int    char_to_int(char code);
    int    prompt();
};

#endif  // GAME_H

