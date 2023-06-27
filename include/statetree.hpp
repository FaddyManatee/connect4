#ifndef STATETREE_H
#define STATETREE_H

#include <queue>

#include "grid.hpp"

class StateTree {
  public:
    StateTree() {};
    StateTree(const Grid& g, int ply);
    ~StateTree();

  private:
    int value;
    int ply;
    Grid state;
    StateTree* child[7];

    void expand(std::queue<StateTree*>& q, int maxPly);
};

#endif
