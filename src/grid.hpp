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
    int countHoriz(int row, int col, int player);
    int countVert(int row, int col, int player);
    int countDiag(int row, int col, int player);
};

#endif
