#include <iostream>
#include "grid.hpp"

Grid::Grid() {
    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 7; y++)
            grid[x][y] = 0;
    }
}

void Grid::drawGrid() {
    for (int x = 0; x < 6; x++) {
        std::cout << "\x1b[44m";
        std::cout << "                              \n";

        for (int y = 0; y < 7; y++) {
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

void Grid::dropChequer(int col, int player) {
    // Drop chequer to last free row.
    for (int y = 5; y >= 0; y--) {
        if (grid[y][col] == 0) {
            grid[y][col] = player;
            break;
        }
    }
}
