#ifndef GRID_H
#define GRID_H

class Grid {
public:
    Grid();
    void drawGrid();
    void dropChequer(int col, int player);

private:
    int grid[6][7];
};

#endif
