#include <iostream>

#include "../include/grid.hpp"

Grid::Grid() {
    height = 6;
    width = 7;

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++)
            grid[x][y] = 0;
    }
    numPlaced = 0;
}

void Grid::drawGrid() {
    for (int x = 0; x < height; x++) {
        std::cout << "\x1b[44m";
        std::cout << "                              \n";

        for (int y = 0; y < width; y++) {
            switch (grid[x][y]) {
                case 1:
                    std::cout << "\x1b[44m  \x1b[41m  ";  // Red.
                    break;
                
                case 2:
                    std::cout << "\x1b[44m  \x1b[43m  ";  // Yellow.
                    break;
                
                default:
                    std::cout << "\x1b[44m  \x1b[0m  ";  // Empty.
                    break;
            }
        }
        std::cout << "\x1b[44m  \x1b[0m\n";
    }
    std::cout << "\x1b[44m";
    std::cout << "                              ";
    std::cout << "\x1b[0m\n";
}

int Grid::outcome() {
    // Result pending:     0
    // Game won by red:    1
    // Game won by yellow: 2
    // Game draw:          3
    
    int player = grid[lastPos.row][lastPos.col];
    
    // Count horizontal.
    if (winHoriz(player) ||
        winVert(player)  ||
        winDiag(player))
    {
        return player;
    }

    if (numPlaced == height * width)
        return 3;
    
    return 0;
}

int Grid::lastColumn() {
    return lastPos.col + 1;
}

bool Grid::winHoriz(int player) {
    int found = 0;
    int row = lastPos.row;
    int col = lastPos.col;

    for (int x = col; x < width; x++) {
        if (grid[row][x] == player)
            found++;
        else
            break;
    }

    for (int x = col; x >= 0; x--) {
        if (grid[row][x] == player)
            found++;
        else
            break;
    }

    return found - 1 == 4;  // -1 since last dropped chequer was counted twice.
}

bool Grid::winVert(int player) {
    int found = 0;
    int row = lastPos.row;
    int col = lastPos.col;

    for (int x = row; x < height; x++) {
        if (grid[x][col] == player)
            found++;
        else
            break;
    }

    for (int x = row; x >= 0; x--) {
        if (grid[x][col] == player)
            found++;
        else
            break;
    }

    return found - 1 == 4;  // -1 since last dropped chequer was counted twice.
}

bool Grid::winDiag(int player) {
    int found = 0;
    int row = lastPos.row;
    int col = lastPos.col;

    for (int x = row, y = col; x < height && y < width; x++, y++) {
        if (grid[x][y] == player)
            found++;
        else
            break;
    }

    for (int x = row, y = col; x < height && y >= 0; x++, y--) {
        if (grid[x][y] == player)
            found++;
        else
            break;
    }

    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--) {
        if (grid[x][y] == player)
            found++;
        else
            break;
    }

    for (int x = row, y = col; x >= 0 && y < width; x--, y++) {
        if (grid[x][y] == player)
            found++;
        else
            break;
    }

    return found - 3 == 4;  // -3 since last dropped chequer was counted four times.
}

bool Grid::dropChequer(int col, int player) {
    if (col > 0)
        col--;
    
    if (overflow(col))
        return true;

    // Drop chequer to last free row.
    for (int y = height - 1; y >= 0; y--) {
        if (grid[y][col] == 0) {
            grid[y][col] = player;
            lastPos.row = y;
            lastPos.col = col;
            numPlaced++;
            break;
        }
    }
    return false;
}

bool Grid::overflow(int col) {
    if (grid[0][col] != 0)
        return true;
    return false;
}
