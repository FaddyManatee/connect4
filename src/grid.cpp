#include <iostream>

#include "include/grid.hpp"

Grid::Grid() {
  this->height      =  6;
  this->width       =  7;
  this->n_placed    =  0;
  this->last_row    = -1;
  this->last_column = -1;
  this->player      = Player::RED;

  for (int x = 0; x < this->height; ++x) {
    for (int y = 0; y < this->width; ++y)
       this->grid[x][y] = Player::NONE;
  }
}

void Grid::switch_player() {
  if (this->player == Player::RED)
    this->player = Player::YELLOW;
  else
    this->player = Player::RED;
}

Player Grid::chequer_at(int row, int column) const {
  return this->grid[row][column];
}

Player Grid::get_current_player() const {
  return this->player;
}

Result Grid::get_result() const {
  if (this->n_placed == this->height * this->width)
    return Result::DRAW;
 
  if (this->find_win(Player::RED))
    return Result::RED;
  else if (this->find_win(Player::YELLOW))
    return Result::YELLOW;
  else
    return Result::PENDING;
}

void Grid::print() const {
  std::cout << "   1   2   3   4   5   6   7\n";
  for (int x = 0; x < this->height; ++x) {
    std::cout << "\x1b[44m";
    std::cout << "                              \n";

    for (int y = 0; y < this->width; ++y) {
      switch (this->grid[x][y]) {
        case Player::RED:
          std::cout << "\x1b[44m  \x1b[41m  ";  // Red.
          break;
                
        case Player::YELLOW:
          std::cout << "\x1b[44m  \x1b[43m  ";  // Yellow.
          break;
                
        default:
          std::cout << "\x1b[44m  \x1b[0m  ";   // Empty.
          break;
      }
    }
    std::cout << "\x1b[44m  \x1b[0m\n";
  }
  std::cout << "\x1b[44m";
  std::cout << "                              ";
  std::cout << "\x1b[0m\n";
}

bool Grid::find_win(Player player) const {
  int h  = this->count_horizontal(player);
  int v  = this->count_vertical(player);
  int d1 = this->count_diagonal_l(player);
  int d2 = this->count_diagonal_r(player);

  if (h >= 4 || v >= 4 || d1 >= 4 || d2 >= 4)
    return true;
  return false;
}

bool Grid::will_overflow(int column) const {
  if (this->grid[0][column] != Player::NONE)
    return true;
  return false;
}

bool Grid::is_full() const {
  if (this->n_placed == this->width * this->height)
    return true;
  return false;
}

bool Grid::drop_chequer(int column) {    
  if (this->will_overflow(column))
    return true;

  // Drop chequer to last free row.
  for (int x = this->height - 1; x >= 0; --x) {
    if (this->grid[x][column] == Player::NONE) {
      this->grid[x][column] = this->player;
      this->last_row = x;
      this->last_column = column;
      this->n_placed++;
      break;
    }
  }
  
  this->switch_player();

  return false;
}

int Grid::get_width() const {
  return this->width;
}

int Grid::get_height() const {
  return this->height;
}

int Grid::count_horizontal(Player player) const {
  int row   = this->last_row;
  int col   = this->last_column;
  int count = 0;

  bool left  = true;
  bool right = true;

  for (int x = 0; x < this->width; ++x) {
    if (col - x < 0)            left  = false;
    if (col + x >= this->width) right = false;

    if (!left && !right)
      break;

    if (x == 0 && this->chequer_at(row, col) == player) {
      count++;
      continue;
    }

    if (left && this->chequer_at(row, col - x) == player)
      count++;
    else
      left = false;

    if (right && this->chequer_at(row, col + x) == player)
      count++;
    else
      right = false;
  }

  return count;
}

int Grid::count_vertical(Player player) const {
  int row   = this->last_row;
  int col   = this->last_column;
  int count = 0;

  for (int x = row; x < this->height; ++x) {
    if (this->chequer_at(x, col) == player)
      count++;
    else
      break;
  }

  return count;
}

int Grid::count_diagonal_l(Player player) const {
  int row   = this->last_row;
  int col   = this->last_column;
  int count = 0;

  bool left  = true;
  bool right = true;

  for (int x = 0; x < this->height; ++x) {
    if (row + x >= this->height || col - x < 0) left  = false;
    if (col + x >= this->width  || row - x < 0) right = false;

    if (!left && !right)
      break;

    if (x == 0 && this->chequer_at(row, col) == player) {
      count++;
      continue;
    }

    if (left && this->chequer_at(row + x, col - x) == player)
      count++;
    else
      left = false;

    if (right && this->chequer_at(row - x, col + x) == player)
      count++;
    else
      right = false;
  }

  return count;
}

int Grid::count_diagonal_r(Player player) const {
  int row   = this->last_row;
  int col   = this->last_column;
  int count = 0;

  bool left  = true;
  bool right = true;

  for (int x = 0; x < this->height; ++x) {
    if (row - x < 0 || col - x < 0)                        left  = false;
    if (row + x >= this->height || col + x >= this->width) right = false;

    if (!left && !right)
      break;

    if (x == 0 && this->chequer_at(row, col) == player) {
      count++;
      continue;
    }

    if (left && this->chequer_at(row - x, col - x) == player)
      count++;
    else
      left = false;

    if (right && this->chequer_at(row + x, col + x) == player)
      count++;
    else
      right = false;
  }

  return count;
}

