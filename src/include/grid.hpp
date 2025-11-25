#ifndef GRID_H
#define GRID_H

enum class Player { NONE, RED, YELLOW };
enum class Result { PENDING, RED, YELLOW, DRAW };

class Grid {
  public:
    Grid();

    Player  chequer_at(int row, int column) const;
    Player  get_current_player()            const;
    Result  get_result()                    const;
    void    print()                         const;
    bool    find_win(Player player)         const;
    bool    will_overflow(int column)       const;
    bool    is_full()                       const;
    int     get_width()                     const;
    int     get_height()                    const;
    int     count_horizontal(Player player) const;
    int     count_vertical(Player player)   const;
    int     count_diagonal_l(Player player) const;
    int     count_diagonal_r(Player player) const;

    bool    drop_chequer(int column);

  private:
    Player grid[6][7];
    Player player;
    int    last_row;
    int    last_column;
    int    width;
    int    height;
    int    n_placed;

    void switch_player();
};

#endif  // GRID_H

