#include <iostream>
#include <limits>

#include "include/minimax.hpp"

Minimax::Minimax(const Grid& grid, int depth) {
  // Build state tree.
  this->root  = new State(grid);
  this->root->expand(depth);

  this->state = this->root;
  this->depth = depth;
}

Minimax::~Minimax() {
  // TODO: Delete this state and all descendants.
}

void Minimax::update(int column) {
  if (this->state->get_n_children() == 0)
    this->state->expand(this->depth);

  for (int x = 0; x < this->state->get_n_children(); ++x) {
    auto child = this->state->child_at(x);

    if (child->get_column() == column) {
      this->state = child;
      // TODO: This is now the root. Delete all non-descendant states.
      break;
    }
  }

  std::cout << "Score: " << this->state->get_score() << std::endl;
}

int Minimax::minimise() {
  if (this->state->get_n_children() == 0)
    this->state->expand(this->depth);

  // Select the minimising state and return its column number.
  int  min       = std::numeric_limits<int>::max();
  auto min_state = this->state;

  for (int x = 0; x < this->state->get_n_children(); ++x) {
    auto child = this->state->child_at(x);

    if (child->get_score() < min) {
      min = child->get_score();
      min_state = child;
    }
  }

  this->state = min_state;

  // TODO: This is now the root. Delete all non-descendant states.
  
  std::cout << "Computer: \"MINIMISING the score to " << this->state->get_score();
  std::cout << " (column=" << this->state->get_column() + 1 << ")\"" << std::endl;

  return this->state->get_column();
}

int Minimax::maximise() {
  if (this->state->get_n_children() == 0)
    this->state->expand(this->depth);

  // Select the maximising state and return its column number.
  int  max       = std::numeric_limits<int>::min();
  auto max_state = this->state;

  for (int x = 0; x < this->state->get_n_children(); ++x) {
    auto child = this->state->child_at(x);

    if (child->get_score() > max) {
      max = child->get_score();
      max_state = child;
    }
  }

  this->state = max_state;

  // TODO: This is now the root. Delete all non-descendant states.

  std::cout << "Computer: \"MAXIMISING the score to " << this->state->get_score();
  std::cout << " (column=" << this->state->get_column() + 1 << ")\"" << std::endl;

  return this->state->get_column();
}

