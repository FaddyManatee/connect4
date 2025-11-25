#ifndef MINIMAX_H
#define MINIMAX_H

#include "state.hpp"

class Minimax {
  public:
    Minimax(const Grid& grid, int depth);
    ~Minimax();

    void update(int column);
    int  minimise();
    int  maximise();

  private:
    Minimax() = delete;

    State *root;
    State *state;
    int    depth;
};

#endif  // MINIMAX_H

