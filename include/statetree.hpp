#ifndef STATETREE_H
#define STATETREE_H

#include "grid.hpp"

class StateTree {
  public:
    StateTree() {};
    StateTree(const Grid& g, int ply);
    ~StateTree();

  private:
    int score;
    int ply;
    Grid state;
    StateTree* child[7];

    void expand(int maxPly);
    void evaluate();
};

#endif
