#ifndef STATETREE_H
#define STATETREE_H

#include "grid.hpp"

class StateTree {
  public:
    StateTree(const Grid& g);
    StateTree(StateTree& t);

  private:
    Grid state;
    StateTree* child[7];

    void growTree();
};

#endif
