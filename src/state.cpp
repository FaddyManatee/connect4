#include <limits>
#include <unistd.h>

#include "include/state.hpp"
#include "include/grid.hpp"

State::State() {
  this->ply    = 0;
  this->score  = 0;
  this->column = 0;
}

State::State(const Grid& grid) {
  this->grid   = grid;
  this->ply    = 0;
  this->score  = 0;
  this->column = 0;
}

State::~State() {
  for (int x = 0; x < this->get_n_children(); ++x) {
    auto child = this->children.at(x);
    if (child != NULL)
      delete child; 
  }
}

void State::compute_score() {
  if (this->grid.find_win(Player::RED)) {
    this->score = std::numeric_limits<int>::max();
    return;
  }

  if (this->grid.find_win(Player::YELLOW)) {
    this->score = std::numeric_limits<int>::min();
    return;
  }

  if (this->grid.is_grid_full()) {
    this->score = 0;
    return;
  }

  int weights[6][7] = {{ 3, 4, 5,  7,  5,  4, 3 },
                       { 4, 6, 8,  10, 8,  6, 4 },
                       { 5, 7, 11, 13, 11, 7, 5 },
                       { 5, 7, 11, 13, 11, 7, 5 },
                       { 4, 6, 8,  10, 8,  6, 4 },
                       { 3, 4, 5,  7,  5,  4, 3 }};

  for (int x = 0; x < this->grid.get_height(); ++x) {
    for (int y = 0; y < this->grid.get_width(); ++y) {
      if (this->grid.chequer_at(x, y) == Player::RED)
        this->score += weights[x][y];
      else if (this->grid.chequer_at(x, y) == Player::YELLOW)
        this->score -= weights[x][y];
    }
  }
}

State *State::child_at(int x) const {
  return this->children.at(x);
}

Player State::get_player() const {
  return this->grid.get_player();
}

Result State::get_result() const {
  return this->grid.get_result();
}

void State::print() const {
  this->grid.print();
}

int State::get_n_children() const {
  return this->children.size();
}

int State::get_column() const {
  return this->column;
}

int State::get_score() const {
  return this->score;
}

int State::expand(int n_ply) {
  // Do not expand the state if it is a leaf or exceeds ply depth.
  if (this->grid.get_result() != Result::PENDING || n_ply == 0) {
    this->compute_score();
    return this->get_score();
  }

  // Are we maximising?
  bool maximising = (this->ply % 2 == 0);

  int best_score = maximising ? std::numeric_limits<int>::min()
                              : std::numeric_limits<int>::max();

  // Expand the state recursively.
  for (int x = 0; x < 7; ++x) {
    // Prevent adding chequers to full columns.
    if (this->grid.is_column_full(x))
      continue;

    auto new_state = new State(this->grid);
    this->children.push_back(new_state);

    new_state->ply = this->ply + 1;
    new_state->grid.drop_chequer(x);
    new_state->column = x;

    // State inherits the minimal/maximal score of its children.
    int child_score = new_state->expand(n_ply - 1);

    // Maximising.
    if (maximising) {
      if (child_score > best_score) best_score = child_score;
    }
    // Minimising.
    else {
      if (child_score < best_score) best_score = child_score;
    }
  }

  this->score = best_score;
  return best_score;
}

