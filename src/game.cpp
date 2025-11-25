#include <iostream>
#include <string>

#include "include/game.hpp"
#include "include/minimax.hpp"

Game::Game() {
  this->grid    = new Grid();
  this->minimax = new Minimax(*this->grid, 8);
}

Game::~Game() {
  delete this->grid;
  delete this->minimax;
}

Result Game::play_turn() {
  bool overflow = false;
  int  column   = -1;

  switch (this->grid->get_current_player()) {
    case Player::RED:
      column = prompt();
      overflow = this->grid->drop_chequer(column);
      while (overflow) {
        std::cout << "That column is full...\n";
        column = prompt();
        overflow = this->grid->drop_chequer(column);
      }

      this->minimax->update(column);
      std::cout << "\n";
      break;
        
      case Player::YELLOW:
        std::cout << "\nComputer is thinking...\n";
        this->grid->drop_chequer(this->minimax->minimise());
        break;

      default:
        break;
  }

  return this->grid->get_result();
}

char Game::int_to_char(int i) {
  return i + 48;
}

int Game::char_to_int(char code) {
  return code - 48;
}

int Game::prompt() {
  std::string input;

  std::cout << "Enter column (1-7): ";
  while (
    !(std::getline(std::cin, input)) ||
    !isdigit(input[0])               ||
    input.length() != 1              ||
    input[0] < int_to_char(1)        ||
    input[0] > int_to_char(7)
  ) {

    std::cout << "Enter column (1-7): ";
  }

  return char_to_int(input[0]) - 1;
}

void Game::start() {
  Result result;

  do {
    this->grid->print();
    result = this->play_turn();
  } while (result == Result::PENDING);

  this->grid->print();

  switch (result) {
    case Result::RED:
      std::cout << "You won!" << std::endl;
      break;
        
    case Result::YELLOW:
      std::cout << "Computer won!" << std::endl;
      break;

    case Result::DRAW:
      std::cout << "Draw!" << std::endl;
      break;

    default:
      break;
  }
}

