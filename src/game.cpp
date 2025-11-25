#include <iostream>
#include <string>

#include "include/game.hpp"
#include "include/minimax.hpp"

Game::Game() {
  this->minimax = new Minimax(8);
}

Game::~Game() {
  delete this->minimax;
}

Result Game::play_turn() {
  bool success  = true;
  int  column   = -1;

  switch (this->minimax->get_current_player()) {
    case Player::RED:
      column = prompt();
      success = this->minimax->update(column);
      while (!success) {
        std::cout << "That column is full...\n";
        column = prompt();
        success = this->minimax->update(column);
      }

      std::cout << "\n";
      break;
        
      case Player::YELLOW:
        std::cout << "\nComputer is thinking...\n";
        this->minimax->minimise();
        break;

      default:
        break;
  }

  return this->minimax->get_current_result();
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
    this->minimax->print_state();
    result = this->play_turn();
  } while (result == Result::PENDING);

  this->minimax->print_state();

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

