#ifndef MINIMAX_H
#define MINIMAX_H

#include "statetree.hpp"

class Minimax {
  public:
    Minimax() {};
    Minimax(Grid g, int ply);

    int minimize();

  private:
    StateTree root;

    void prune();
};

#endif
