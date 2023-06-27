#include <iostream>

#include "../include/grid.hpp"

Grid::Grid() {
    height = 6;
    width = 7;
    numPlaced = 0;
    lastPos.row = 0;
    lastPos.col = 0;
    player = Player::RED;

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++)
            grid[x][y] = Player::NONE;
    }
}

void Grid::drawGrid() {
    for (int x = 0; x < height; x++) {
        std::cout << "\x1b[44m";
        std::cout << "                              \n";

        for (int y = 0; y < width; y++) {
            switch (grid[x][y]) {
                case Player::RED:
                    std::cout << "\x1b[44m  \x1b[41m  ";  // Red.
                    break;
                
                case Player::YELLOW:
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
    
    // Count horizontal.
    if (countHoriz() == 4 ||
        countVert() == 4  ||
        countDiag() == 4)
    {
        return player;
    }

    if (numPlaced == height * width)
        return 3;
    
    return 0;
}

void Grid::nextPlayer() {
    if (player == Player::RED)
        player = Player::YELLOW;
    else
        player = Player::RED;
}

int Grid::curPlayer() {
    return player;
}

int Grid::countHoriz() {
    int found = 0;

    for (int x = lastPos.col; x < width; x++) {
        if (grid[lastPos.row][x] == player)
            found++;
        else
            break;
    }

    for (int x = lastPos.col; x >= 0; x--) {
        if (grid[lastPos.row][x] == player)
            found++;
        else
            break;
    }

    return found - 1;  // -1 since last dropped chequer was counted twice.
}

int Grid::countVert() {
    int found = 0;

    for (int x = lastPos.row; x < height; x++) {
        if (grid[x][lastPos.col] == player)
            found++;
        else
            break;
    }

    for (int x = lastPos.row; x >= 0; x--) {
        if (grid[x][lastPos.col] == player)
            found++;
        else
            break;
    }

    return found - 1;  // -1 since last dropped chequer was counted twice.
}

int Grid::countDiag() {
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

    return found - 3;  // -3 since last dropped chequer was counted four times.
}

bool Grid::dropChequer(int col) {    
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
