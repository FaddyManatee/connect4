#ifndef GRID_H
#define GRID_H

class Grid {
public:
    Grid();
    void drawGrid();
    bool dropChequer(int col, int player);

private:
    int grid[6][7];

    bool overflow(int col);
};

#endif
