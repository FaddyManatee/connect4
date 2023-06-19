#include <iostream>
#include <string>
#include "game.hpp"

Game::Game() {
    grid = Grid();
    curPlayer = 1;
}

void Game::start() {
    while (true) {
        grid.drawGrid();
        nextTurn();
    }
}

void Game::nextTurn() {
    std::string col;

    switch (curPlayer) {
        case 1:
            std::cout << "Enter column: ";

            while (!(std::getline(std::cin, col)) ||
                    col.length() != 1             || 
                    !isdigit(col[0])              ||
                    col[0] < intToCode(1)         ||
                    col[0] > intToCode(7))
            {
                std::cout << "Enter column: ";
            }

            grid.dropChequer(codeToInt(col[0]) - 1, curPlayer);  // What if column overflows?
            curPlayer = 2;
            std::cout << "\n";
            break;
        
        case 2:
            std::cout << "\nComputer is thinking...\n";
            grid.dropChequer(0, curPlayer);  // Use fixed column for now.
            curPlayer = 1;
            break;
    }
}

char Game::intToCode(int i) {
    return i + 48;
}

int Game::codeToInt(char code) {
    return code - 48;
}
