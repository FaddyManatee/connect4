#include <iostream>
#include <string>

#include "../include/game.hpp"

Game::Game() {
    grid = Grid();
    m = Minimax(grid, 7);
}

void Game::start() {
    int result = 0;

    while (result == 0) {
        grid.drawGrid();
        result = nextTurn();
    }
    grid.drawGrid();

    switch (result) {
        case Player::RED:
            std::cout << "You won!\n";
            break;
        
        case Player::YELLOW:
            std::cout << "Computer won!\n";
            break;

        case 3:
            std::cout << "Draw!\n";
            break;
    }
}

int Game::nextTurn() {
    bool overflow = false;

    switch (grid.curPlayer()) {
        case Player::RED:
            overflow = grid.dropChequer(prompt());
            while (overflow) {
                std::cout << "That column is full...\n";
                overflow = grid.dropChequer(prompt());
            }

            std::cout << "\n";
            break;
        
        case Player::YELLOW:
            std::cout << "\nComputer is thinking...\n";
            grid.dropChequer(m.minimize());
            break;
    }

    int result = grid.outcome();
    grid.nextPlayer();

    return result;
}

int Game::prompt() {
    std::string col;

    std::cout << "Enter column: ";
    while (!(std::getline(std::cin, col)) ||
            !isdigit(col[0])              ||
            col.length() != 1             ||
            col[0] < intToCode(1)         ||
            col[0] > intToCode(7))
    {
        std::cout << "Enter column: ";
    }

    return codeToInt(col[0]) - 1;
}

char Game::intToCode(int i) {
    return i + 48;
}

int Game::codeToInt(char code) {
    return code - 48;
}
