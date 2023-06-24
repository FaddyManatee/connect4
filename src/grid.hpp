#ifndef GRID_H
#define GRID_H

typedef struct {
    int row;
    int col;
} Position;

class Grid {
  public:
    Grid();
    void drawGrid();
    bool dropChequer(int col, int player);
    int outcome();
    int lastColumn();

  private:
    int height;
    int width;
    int grid[6][7];
    int numPlaced;
    Position lastPos;

    bool overflow(int col);
    bool winHoriz(int player);
    bool winVert(int player);
    bool winDiag(int player);
};

#endif
