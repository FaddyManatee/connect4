#ifndef GRID_H
#define GRID_H

typedef struct {
    int row;
    int col;
} Position;

enum Player { NONE, RED, YELLOW };

class Grid {
  public:
    Grid();
    void drawGrid();
    void nextPlayer();
    bool dropChequer(int col);
    int outcome();
    int curPlayer();

  private:
    int height;
    int width;
    int grid[6][7];
    int numPlaced;
    int player;
    Position lastPos;

    bool overflow(int col);
    int countHoriz();
    int countVert();
    int countDiag();
};

#endif
