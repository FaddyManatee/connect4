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
    bool overflow = false;

    switch (curPlayer) {
        case 1:
            overflow = grid.dropChequer(prompt(), curPlayer);
            while (overflow) {
                std::cout << "That column is full...\n";
                overflow = grid.dropChequer(prompt(), curPlayer);
            }

            curPlayer = 2;
            std::cout << "\n";
            break;
        
        case 2:
            std::cout << "\nComputer is thinking...\n";
            grid.dropChequer(1, curPlayer);  // Use fixed column for now.
            curPlayer = 1;
            break;
    }
}

int Game::prompt() {
    std::string col;

    std::cout << "Enter column: ";
    while (!(std::getline(std::cin, col)) ||
            col.length() != 1             || 
            !isdigit(col[0])              ||
            col[0] < intToCode(1)         ||
            col[0] > intToCode(7))
    {
        std::cout << "Enter column: ";
    }

    return codeToInt(col[0]);
}

char Game::intToCode(int i) {
    return i + 48;
}

int Game::codeToInt(char code) {
    return code - 48;
}
