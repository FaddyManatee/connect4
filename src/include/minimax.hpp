#ifndef MINIMAX_H
#define MINIMAX_H

#include "state.hpp"

class Minimax {
  public:
    Minimax(int depth);
    ~Minimax();

    Player get_current_player() const;
    Result get_current_result() const;
    void   print_state()        const;

    void minimise();
    void maximise();
    bool update(int column);

  private:
    Minimax() = delete;

    State *root;
    State *state;
    int    depth;
};

#endif  // MINIMAX_H

