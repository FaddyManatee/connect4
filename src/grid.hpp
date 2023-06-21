#ifndef GRID_H
#define GRID_H

class Grid {
public:
    Grid();
    void drawGrid();
    bool dropChequer(int col, int player);
    int outcome();

private:
    int height;
    int width;
    int grid[6][7];
    int lastPos[2];
    int numPlaced;

    bool overflow(int col);
    int countHoriz(int row, int col, int player);
    int countVert(int row, int col, int player);
};

#endif
