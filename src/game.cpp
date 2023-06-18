#include <iostream>
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
    int col = 0;

    switch (curPlayer) {
        case 1:
            std::cout << "Enter column: ";
            while (!(std::cin >> col) || col < 1 || col > 7)
                std::cout << "Enter column: ";

            grid.dropChequer(col - 1, curPlayer);  // What if column overflows?
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
