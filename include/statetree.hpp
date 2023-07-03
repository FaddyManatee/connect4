#ifndef STATETREE_H
#define STATETREE_H

#include "grid.hpp"

typedef struct {
    int local;
    int minimax;
    int col;
} Score;

class StateTree {
  public:
    StateTree() {};
    StateTree(const Grid& g, int ply);
    ~StateTree();

  private:
    int ply;
    bool isLeaf;
    Score score;
    Grid state;
    StateTree* child[7];

    void expand(int maxPly);
    void calcScore();
    void evaluate();
};

#endif
