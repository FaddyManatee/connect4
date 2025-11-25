#ifndef STATE_H
#define STATE_H

#include <vector>
#include "grid.hpp"

class State {
  public:
    State();
    State(const Grid& grid);
    ~State();

    State  *child_at(int x)  const;
    Player  get_player()     const;
    Result  get_result()     const;
    void    print()          const;
    int     get_n_children() const;
    int     get_column()     const;
    int     get_score()      const;

    int    expand(int n_ply);

  private:
    std::vector<State*> children;
    Grid grid;
    int  ply;
    int  score;
    int  column;

    void compute_score();
};

#endif  // STATE_H

