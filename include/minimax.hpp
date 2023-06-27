#ifndef MINIMAX_H
#define MINIMAX_H

#include "statetree.hpp"

class Minimax {
  public:
    Minimax(Grid g, int ply);

  private:
    StateTree root;
};

#endif